#include "stdafx.h"
#include "Scene/MainGameScene.h"
#include "EngineHelper.h"
#include "Triangle.h"

USING_NS_CC;

Triangle::Triangle() {
}

Triangle::~Triangle() {
}

Triangle* Triangle::create() {
	Triangle *sprite = new (std::nothrow) Triangle();
    if (sprite && sprite->initWithTexture(Director::getInstance()->getTextureCache()->addImage("tri_o.png")))
    {
        sprite->autorelease();
		sprite->initOpt();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

void Triangle::initOpt() {
	this->setColor(C3B(E::P.C400));
	this->setTag(TAG_PHY_BLOCK);
	auto i = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->addImage("tri_i.png"));
	i->setColor(C3B(E::P.C800));
	i->setPosition(this->getContentSize()/2);
	//i->runAction(RotateBy::create(1E35, 360E35));
	this->addChild(i);
}

/**
Make sure to setScale before initBody.
*/
void Triangle::initBody(){
	float w = getContentSize().width / 2 * getScale() - 8;
	Vec2 points[3] = {Vec2(-w, w), Vec2(0, -w), Vec2(w, w)};
	auto body = PhysicsBody::createEdgePolygon(points, 3, SMOOTH_MATERIAL, 6);
	body->setDynamic(false);
	body->setContactTestBitmask(0x0000000F);
	body->setCategoryBitmask(0xFFFFFFF0);
	body->setCollisionBitmask(0x000000F0);
	setPhysicsBody(body);
}
