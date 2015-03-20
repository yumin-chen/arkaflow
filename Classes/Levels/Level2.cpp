#include "stdafx.h"
#include "Level2.h"
#include "Element/Ring.h"
#include "Element/Target.h"
#include "Element/Block.h"

USING_NS_CC;

bool Level2::init()
{
	if ( !BaseLevel::init() )
	{
		return false;
	}

	restart();

	return true;
}

void Level2::restart(){
	BaseLevel::restart();

#define MOVE_BY_X 128

	auto ring = Ring::create();
	ring->setPosition(E::originX, E::originY + 96);
	ring->setScale(0.2);
	ring->initBody();
	this->addChild(ring);
	ring->runAction(RepeatForever::create(Sequence::create(MoveBy::create(0.25f, Vec2(MOVE_BY_X, 0)), MoveBy::create(0.25f, Vec2(-MOVE_BY_X, 0)), DelayTime::create(1.0f), nullptr)));
	
#define MOVE_BY_X 256

	auto t = Target::create();
	t->setPosition(E::originX + DESIGNED_WIDTH / 2 - MOVE_BY_X/2 - 128, E::originY + 480);
	t->initBody();
	this->addChild(t);
	t->playAnim(0);
	t->runAction(RepeatForever::create(Sequence::create(MoveBy::create(1.6f, Vec2(MOVE_BY_X, 0)), MoveBy::create(1.6f, Vec2(-MOVE_BY_X, 0)), nullptr)));

	auto t2 = Target::create();
	t2->setPosition(E::originX + DESIGNED_WIDTH / 2 - MOVE_BY_X/2 + 128, E::originY + 160);
	t2->initBody();
	this->addChild(t2);
	t2->playAnim(0);
	t2->runAction(RepeatForever::create(Sequence::create(MoveBy::create(1.6f, Vec2(MOVE_BY_X, 0)), MoveBy::create(1.6f, Vec2(-MOVE_BY_X, 0)), nullptr)));

	auto t3 = Target::create();
	t3->setPosition(E::originX + DESIGNED_WIDTH / 2 - MOVE_BY_X/2 + 128, E::originY + 320);
	t3->initBody();
	this->addChild(t3);
	t3->playAnim(0);
	t3->runAction(RepeatForever::create(Sequence::create(MoveBy::create(1.6f, Vec2(MOVE_BY_X, 0)), MoveBy::create(1.6f, Vec2(-MOVE_BY_X, 0)), nullptr)));

#define MOVE_BY_X 64
	auto b1 = Block::create(E::originX + DESIGNED_WIDTH - 128, 24);
	b1->setPosition(0, E::originY + 400);
	b1->initBody();
	this->addChild(b1);
	auto b12 = Block::create(E::originX + DESIGNED_WIDTH - 128, 16, E::P.C800);
	b12->setPosition(0, E::originY + 400 - 16);
	b12->initBody();
	b12->runAction(RepeatForever::create(Sequence::create(MoveBy::create(1.0f, Vec2(MOVE_BY_X, 0)), MoveBy::create(1.0f, Vec2(-MOVE_BY_X, 0)), nullptr)));
	b12->runAction(RepeatForever::create(Sequence::create(TintTo::create(1.0f, C3B(E::P.C400)), TintTo::create(1.0f, C3B(E::P.C800)), nullptr)));
	this->addChild(b12);

#define MOVE_BY_X -64
	auto b2 = Block::create(E::originX + DESIGNED_WIDTH - 128, 24);
	b2->setPosition(E::originX + 128, E::originY + 240);
	b2->initBody();
	this->addChild(b2);
	auto b22 = Block::create(E::originX + DESIGNED_WIDTH - 128, 16, E::P.C800);
	b22->setPosition(E::originX + 128, E::originY + 240 - 16);
	b22->initBody();
	b22->runAction(RepeatForever::create(Sequence::create(MoveBy::create(1.0f, Vec2(MOVE_BY_X, 0)), MoveBy::create(1.0f, Vec2(-MOVE_BY_X, 0)), nullptr)));
	b22->runAction(RepeatForever::create(Sequence::create(TintTo::create(1.0f, C3B(E::P.C400)), TintTo::create(1.0f, C3B(E::P.C800)), nullptr)));
	this->addChild(b22);

	auto b3 = Block::create(24, 192);
	b3->setAnchorPoint(Vec2(0, 0));
	b3->setPosition(E::originX, E::originY + 400 - 24 - 192);
	b3->initBody();
	this->addChild(b3);


}

void Level2::update(float dt){
}