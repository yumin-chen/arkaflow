#include "stdafx.h"
#include "Scene/MainGameScene.h"
#include "EngineHelper.h"
#include "Target.h"

USING_NS_CC;

Target::Target() {
}

Target::~Target() {
}

Target* Target::create() {
	Target *sprite = new (std::nothrow) Target();
    if (sprite && sprite->initWithFile("target.png"))
    {
        sprite->autorelease();
		sprite->initOpt();
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
	i->setPosition(Vec2(this->getContentSize().width/2, this->getContentSize().height/2 - 8));
	auto a = Spawn::createWithTwoActions(ScaleTo::create(1.0, 1.2), FadeTo::create(1.0, 0));
	i->runAction(RepeatForever::create(Sequence::create(a, ScaleTo::create(0, 0.4), FadeTo::create(0, 255), nullptr)));
	i->runAction(RotateBy::create(1E35, 360E35));
	this->setTag(TAG_PHY_TARGET);
	this->addChild(i);
	//this->runAction(RotateBy::create(1E35, 180E35));
}

/**
Make sure to setScale before initBody.
*/
void Target::initBody(){
	Vec2 points[3] = {Vec2(0, 4), Vec2(64, 4), Vec2(32, 64)};
	auto body = PhysicsBody::createEdgePolygon(points, 3, SMOOTH_MATERIAL);
	body->setDynamic(false);
	body->setPositionOffset(Vec2(-26, -24));
	body->setContactTestBitmask(0x0000000F);
	body->setCategoryBitmask(0xFFFFFFF0);
	body->setCollisionBitmask(0x000000F0);
	setPhysicsBody(body);
}

void Target::beHit(){
	getPhysicsBody()->removeFromWorld();
	Vec2 pos = getPosition() + getParent()->getPosition();
	BaseScene::getCurrentScene()->putEmitter2(Vec2(pos.x, pos.y));
	auto cbRemove = CallFunc::create([this](){removeFromParentAndCleanup(true);});
	runAction(Sequence::create(FadeOut::create(0.6), cbRemove, nullptr));

}

void Target::setOpacity(GLubyte o){
	Sprite::setOpacity(o);
	auto children = this->getChildren();
	for (Vector<Node*>::iterator it = children.begin() ; it != children.end(); ++it)
	{
		(*it)->setOpacity(o);
	}
}