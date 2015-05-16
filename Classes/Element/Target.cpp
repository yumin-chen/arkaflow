#include "stdafx.h"
#include "../Scene/MainGameScene.h"
#include "EngineHelper.h"
#include "Target.h"
#include "Brick.h"

USING_NS_CC;

int Target::targetNum = 0;

Target::Target() {
	bAlreadyHit = false;
	block1 = nullptr;
}

Target::~Target() {
}

Target* Target::create() {
	Target *sprite = new (std::nothrow) Target();
    if (sprite && sprite->initWithTexture(Director::getInstance()->getTextureCache()->addImage("target.png")))
    {
		sprite->block1 = nullptr;
        sprite->autorelease();
		sprite->initOpt();
		targetNum++;
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

void Target::initOpt() {
	this->setScale(0.2);
	this->setAnchorPoint(Vec2(0.5, 0.5));
	this->setColor(C3B(E::P.C400));
	auto i = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->addImage("target.png"));
	i->setColor(C3B(E::P.C800));
	i->setAnchorPoint(Vec2(0.5, 0.5));
	i->setScale(0.4);
	i->setPosition(Vec2(this->getContentSize().width/2, this->getContentSize().height/2 - 64));
	auto a = Spawn::createWithTwoActions(ScaleTo::create(1.0, 1.0), FadeTo::create(1.0, 0));
	i->runAction(RepeatForever::create(Sequence::create(a, ScaleTo::create(0, 0.2), FadeTo::create(0, 255), nullptr)));
	i->runAction(RotateBy::create(1E35, 360E35));
	this->setTag(TAG_PHY_TARGET);
	this->addChild(i);
	}

void Target::playAnim(int index){
	switch(index){
	case 0:
		this->runAction(RotateBy::create(1E35, 180E35));
		break;
	case 1:
		this->runAction(RepeatForever::create(Sequence::create(MoveBy::create(0.5, Vec2(0, 8)), MoveBy::create(1.0, Vec2(0, -16)), MoveBy::create(0.5, Vec2(0, 8)), nullptr)));
		break;
	}
}

void Target::enableArtificialIntelligence(){
	auto func = CallFunc::create([this](){_updateAI();});
	runAction(RepeatForever::create(Sequence::create(func, nullptr)));
}

void Target::_updateAI(){
#define MOVING_TAG 10000
	if(bAlreadyHit)
		return;
	S_MainGame *scene = ((S_MainGame *)S_MainGame::getCurrentScene());
	if(scene == nullptr || scene->getMainBall() == nullptr)
		return;
	Vec2 pos = scene->getMainBall()->getPosition();
			auto pos2 = getParent()->convertToWorldSpace(getPosition()) / E::scale;
			//CCLog("pos: %f, %f; pos2: %f, %f;", pos.x, pos.y, pos2.x, pos2.y);
		if(pos.getDistance(pos2) < 128)
		{
			stopActionByTag(MOVING_TAG);
			MoveBy* mb;
			if(pos2.y < 320)
			{
				mb = MoveBy::create(0.5f, Vec2(0, +320));
			}
			else{
				mb = MoveBy::create(0.5f, Vec2(0, -320));
			}
			mb->setTag(MOVING_TAG);
			runAction(mb);
		}
}

/**
Make sure to setScale before initBody.
*/
void Target::initBody(){
	Vec2 points[3] = {Vec2(-32, -32), Vec2(0, 32), Vec2(32, -32)};
	auto body = PhysicsBody::createEdgePolygon(points, 3, SMOOTH_MATERIAL);
	body->setDynamic(false);
	body->setContactTestBitmask(0x0000000F);
	body->setCategoryBitmask(0xFFFFFFF0);
	body->setCollisionBitmask(0x000000F0);
	setPhysicsBody(body);
}

void Target::beHit(){
	if(bAlreadyHit)
		return;
	bAlreadyHit = true;
	getPhysicsBody()->removeFromWorld();
	Vec2 pos = getPosition() + getParent()->getPosition();
	BaseScene::getCurrentScene()->putEmitter2(Vec2(pos.x, pos.y));
	auto cbRemove = CallFunc::create([this](){removeFromParentAndCleanup(true);});
	stopAllActions();
	runAction(Sequence::create(FadeOut::create(0.6), cbRemove, nullptr));
	targetNum --;
	if(targetNum <= 0){
		((S_MainGame*)BaseScene::getCurrentScene())->nextLevelDialog();
	}
	E::playEffect("ba");

}

void Target::setPosition(float x, float y){
	Sprite::setPosition(x, y);
	_updateProtectorPosition();
}

void Target::initProtector(float width){
	block1 = Brick::create(width, width / 8);
	block2 = Brick::create(width / 8, width * 0.75);
	block3 = Brick::create(width / 8, width * 0.75);
	this->getParent()->addChild(block1);
	this->getParent()->addChild(block2);
	this->getParent()->addChild(block3);
	block1->initBody();
	block2->initBody();
	block3->initBody();
	block1->setRotation(getRotation());
	block2->setRotation(getRotation());
	block3->setRotation(getRotation());
	_updateProtectorPosition();
}

void Target::_updateProtectorPosition(){
	if(block1 == nullptr)
		return;
	float width = block1->getContentSize().width;
	float x_offset = width/2;
	block1->setPosition(getPositionX() -x_offset, getPositionY()-x_offset);
	block2->setPosition(getPositionX() -x_offset, getPositionY()-x_offset);
	block3->setPosition(getPositionX() -x_offset + width - width / 8, getPositionY()-x_offset);
}
