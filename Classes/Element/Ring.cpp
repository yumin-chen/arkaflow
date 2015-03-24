#include "stdafx.h"
#include "EngineHelper.h"
#include "Scene/MainGameScene.h"
#include "Ring.h"

USING_NS_CC;

Ring::Ring() {
}

Ring::~Ring() {
}

Ring* Ring::create() {
	Ring *sprite = new (std::nothrow) Ring();
    if (sprite && sprite->initWithFile("ring_o.png"))
    {
        sprite->autorelease();
		sprite->initOpt();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

void Ring::initOpt(){
	this->setColor(C3B(E::P.C400));
	this->setTag(TAG_PHY_BLOCK);
	auto i = Sprite::create("ring_i.png");
	i->setColor(C3B(E::P.C800));
	i->setPosition(this->getContentSize()/2);
	i->runAction(RotateBy::create(1E35, 360E35));
	this->addChild(i);

}

/**
Make sure to setScale before initBody.
*/
void Ring::initBody(){
	auto body = PhysicsBody::createCircle(getContentSize().width*getScale()*0.5f, SMOOTH_MATERIAL);
	body->setDynamic(false);
	body->setCategoryBitmask(0xFFFFFFF0);
	body->setCollisionBitmask(0x000000F0);
	body->setContactTestBitmask(0x0000000F);
	setPhysicsBody(body);
}
