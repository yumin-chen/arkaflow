#include "stdafx.h"
#include "Level2.h"
#include "Element/Ring.h"
#include "Element/Target.h"

USING_NS_CC;

bool Level2::init()
{
	if ( !BaseLevel::init() )
	{
		return false;
	}



	auto ring = Ring::create();
	ring->setPosition(E::originX - 64, E::originY + 192 + 12);
	ring->setScale(0.4);
	ring->initBody();
	this->addChild(ring);
	ring->runAction(RepeatForever::create(Sequence::create(MoveBy::create(0.8f, Vec2((DESIGNED_WIDTH + 64 * 2), 0)), MoveBy::create(0.8f, Vec2(-(DESIGNED_WIDTH + 64 * 2), 0)), nullptr)));

#define MOVE_BY_X 256

	auto t = Target::create();
	t->setPosition(E::originX + DESIGNED_WIDTH / 2 - MOVE_BY_X/2, E::originY + 480);
	t->initBody();
	this->addChild(t);
	t->runAction(RepeatForever::create(Sequence::create(MoveBy::create(1.6f, Vec2(MOVE_BY_X, 0)), MoveBy::create(1.6f, Vec2(-MOVE_BY_X, 0)), nullptr)));
	return true;
}

void Level2::update(float dt){
}