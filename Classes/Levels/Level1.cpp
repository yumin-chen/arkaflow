#include "stdafx.h"
#include "Level1.h"
#include "Element/Ring.h"
#include "Element/Target.h"

USING_NS_CC;

bool Level1::init()
{
	if ( !BaseLevel::init() )
	{
		return false;
	}

#define MOVE_BY_X 192

	auto r1 = Ring::create();
	r1->setPosition(E::originX - 128, E::originY + 192 + 12);
	r1->setScale(0.5);
	r1->initBody();
	this->addChild(r1);
	r1->runAction(RepeatForever::create(Sequence::create(MoveBy::create(0.5f, Vec2(MOVE_BY_X, 0)), DelayTime::create(1.0f), MoveBy::create(0.5f, Vec2(-MOVE_BY_X, 0)), nullptr)));

	auto r2 = Ring::create();
	r2->setPosition(E::originX + DESIGNED_WIDTH + 128, E::originY + 192 + 12);
	r2->setScale(0.5);
	r2->initBody();
	this->addChild(r2);
	r2->runAction(RepeatForever::create(Sequence::create(MoveBy::create(0.5f, Vec2(-MOVE_BY_X, 0)), DelayTime::create(1.0f),MoveBy::create(0.5f, Vec2(MOVE_BY_X, 0)), nullptr)));

	auto t = Target::create();
	t->setPosition(E::originX + DESIGNED_WIDTH / 2, E::originY + 480);
	t->initBody();
	this->addChild(t);
	return true;
}

void Level1::update(float dt){
}