#include "stdafx.h"
#include "../Scene/MainGameScene.h"
#include "EngineHelper.h"
#include "Brick.h"

USING_NS_CC;

Brick::Brick() {
}

Brick::~Brick() {
}

Brick* Brick::create(float width, float height, int color) {
	Brick *block = new (std::nothrow) Brick();
	if (block && block->initWithColor(C4B(color)))
    {
        block->autorelease();
		block->initOpt(width, height);
        return block;
    }
    CC_SAFE_DELETE(block);
    return nullptr;
}

void Brick::initOpt(float width, float height){
	setContentSize(Size(width, height));
	this->setTag(TAG_PHY_BLOCK);
}

/**
Make sure to setScale before initBody.
*/
void Brick::initBody(){
	auto body = PhysicsBody::createBox(getContentSize(), SMOOTH_MATERIAL);
	body->setDynamic(false);
	body->setCategoryBitmask(0xFFFFFFF0);
	body->setCollisionBitmask(0x000000F0);
	body->setContactTestBitmask(0x0000000F);
	body->setPositionOffset(Vec2(getContentSize().width * 0.5 * E::scale, getContentSize().height * 0.5 * E::scale));
	setPhysicsBody(body);
}
