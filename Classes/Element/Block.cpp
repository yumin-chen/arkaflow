#include "stdafx.h"
#include "EngineHelper.h"
#include "Block.h"

USING_NS_CC;

Block::Block() {
}

Block::~Block() {
}

Block* Block::create(float width, float height, int color) {
	Block *block = new (std::nothrow) Block();
	if (block && block->initWithColor(C4B(color)))
    {
        block->autorelease();
		block->initOpt(width, height);
        return block;
    }
    CC_SAFE_DELETE(block);
    return nullptr;
}

void Block::initOpt(float width, float height){
	setContentSize(Size(width, height));
}

/**
Make sure to setScale before initBody.
*/
void Block::initBody(){
	auto body = PhysicsBody::createBox(getContentSize(), SMOOTH_MATERIAL);
	body->setDynamic(false);
	body->setCategoryBitmask(0xFFFFFFF0);
	body->setCollisionBitmask(0x000000F0);
	body->setPositionOffset(Vec2(getContentSize().width * 0.5 * E::scale, getContentSize().height * 0.5 * E::scale));
	setPhysicsBody(body);
}
