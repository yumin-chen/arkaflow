#include "stdafx.h"
#include "Scene/MainGameScene.h"
#include "EngineHelper.h"
#include "Target.h"

USING_NS_CC;

int Target::targetNum = 0;

Target::Target() {
	bAlreadyHit = false;
}

Target::~Target() {
}

Target* Target::create() {
	Target *sprite = new (std::nothrow) Target();
    if (sprite && sprite->initWithFile("target.png"))
    {
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
	auto i = Sprite::create("target.png");
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
	getPhysicsBody()->removeFromWorld();
	Vec2 pos = getPosition() + getParent()->getPosition();
	BaseScene::getCurrentScene()->putEmitter2(Vec2(pos.x, pos.y));
	auto cbRemove = CallFunc::create([this](){removeFromParentAndCleanup(true);});
	runAction(Sequence::create(FadeOut::create(0.6), cbRemove, nullptr));
	bAlreadyHit = true;
	targetNum --;
	if(targetNum <= 0){
		((S_MainGame*)BaseScene::getCurrentScene())->nextLevelDialog();
	}
	E::playEffect("ba");

}
