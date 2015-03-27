#include "stdafx.h"
#include "Scene/MainGameScene.h"
#include "EngineHelper.h"
#include "Diamond.h"

USING_NS_CC;

Diamond::Diamond() {
}

Diamond::~Diamond() {
}

Diamond* Diamond::create() {
	Diamond *sprite = new (std::nothrow) Diamond();
    if (sprite && sprite->initWithTexture(Director::getInstance()->getTextureCache()->addImage("diamond_o.png")))
    {
        sprite->autorelease();
		sprite->initOpt();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

void Diamond::initOpt() {
	this->setColor(C3B(E::P.C400));
	this->setTag(TAG_PHY_BLOCK);
	auto i = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->addImage("diamond_i.png"));
	i->setColor(C3B(E::P.C800));
	i->setPosition(this->getContentSize()/2);
	//i->runAction(RotateBy::create(1E35, 360E35));
	this->addChild(i);
}

/**
Make sure to setScale before initBody.
*/
void Diamond::initBody(){
	float w = getContentSize().width / 2 * getScale() - 8;
	Vec2 points[4] = {Vec2(-w/2, 0), Vec2(0, -w), Vec2(w/2, 0), Vec2(0, w)};
	auto body = PhysicsBody::createEdgePolygon(points, 4, SMOOTH_MATERIAL, 8);
	body->setDynamic(false);
	body->setContactTestBitmask(0x0000000F);
	body->setCategoryBitmask(0xFFFFFFF0);
	body->setCollisionBitmask(0x000000F0);
	setPhysicsBody(body);
}
