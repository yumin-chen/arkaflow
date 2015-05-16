#include "stdafx.h"
#include "Level19.h"
#include "../Element/Ring.h"
#include "../Element/Target.h"
#include "../Element/Triangle.h"
#include "../Element/Brick.h"

USING_NS_CC;

bool Level19::init()
{
	if ( !BaseLevel::init() )
	{
		return false;
	}

	restart();

	return true;
}

void Level19::restart(){
	BaseLevel::restart();

	ring = Ring::create();
	ring->setPosition(E::originX, E::originY + 72);
	ring->setScale(0.2);
	ring->initBody();
	this->addChild(ring);
		
#define MOVE_BY_X 256

	auto t = Target::create();
	t->setPosition(E::originX + DESIGNED_WIDTH / 2 - MOVE_BY_X/2 - 128, E::originY + 440);
	t->initBody();
	this->addChild(t);
	t->playAnim(0);
	t->runAction(RepeatForever::create(Sequence::create(MoveBy::create(1.6f, Vec2(MOVE_BY_X, 0)), MoveBy::create(1.6f, Vec2(-MOVE_BY_X, 0)), nullptr)));

#define MOVE_BY_X 64
	auto t2 = Target::create();
	t2->setPosition(E::originX + DESIGNED_WIDTH / 2 - MOVE_BY_X/2 - 128 - 32, E::originY + 440 - 128 - 16);
	t2->initBody();
	this->addChild(t2);
	t2->playAnim(0);
	t2->runAction(RepeatForever::create(Sequence::create(MoveBy::create(1.6f, Vec2(MOVE_BY_X, 0)), MoveBy::create(1.6f, Vec2(-MOVE_BY_X, 0)), nullptr)));

#define MOVE_BY_X 64
	auto b1 = Brick::create(E::originX + DESIGNED_WIDTH - 192, 24);
	b1->setPosition(0, E::originY + 360);
	b1->initBody();
	this->addChild(b1);
	auto b12 = Brick::create(E::originX + DESIGNED_WIDTH - 192, 16, E::P.C800);
	b12->setPosition(0, E::originY + 360 - 16);
	b12->initBody();
	b12->runAction(RepeatForever::create(Sequence::create(MoveBy::create(1.0f, Vec2(MOVE_BY_X, 0)), MoveBy::create(1.0f, Vec2(-MOVE_BY_X, 0)), nullptr)));
	b12->runAction(RepeatForever::create(Sequence::create(TintTo::create(1.0f, C3B(E::P.C400)), TintTo::create(1.0f, C3B(E::P.C800)), nullptr)));
	this->addChild(b12);

	auto b2 = Brick::create(E::originX + 128, 24);
	b2->setPosition(0, E::originY + 360 - 128);
	b2->initBody();
	this->addChild(b2);
	auto b22 = Brick::create(E::originX + 128 - 32, 16, E::P.C800);
	b22->setPosition(0, E::originY + 360 - 128 - 16);
	b22->initBody();
	b22->runAction(RepeatForever::create(Sequence::create(MoveBy::create(1.0f, Vec2(MOVE_BY_X, 0)), MoveBy::create(1.0f, Vec2(-MOVE_BY_X, 0)), nullptr)));
	b22->runAction(RepeatForever::create(Sequence::create(TintTo::create(1.0f, C3B(E::P.C400)), TintTo::create(1.0f, C3B(E::P.C800)), nullptr)));
	this->addChild(b22);

	auto b3 = Brick::create(24, 192);
	b3->setAnchorPoint(Vec2(0, 0));
	b3->setPosition(E::originX + 320, E::originY + 480);
	b3->initBody();
	this->addChild(b3);

	auto triangle2 = Triangle::create();
	triangle2->setScale(0.6f);
	triangle2->setRotation(30);
	triangle2->setPosition(E::originX + DESIGNED_WIDTH + 96, E::originY + 256);
	triangle2->initBody();
	this->addChild(triangle2);


}

void Level19::update(float dt){
	static float tick = 0;
	int originX = E::originX + DESIGNED_WIDTH / 2 + 48;
	int originY = E::originY + 192 - 16;
	tick += dt;
	float angle = PI * tick;
	int offset = 96;
	ring->setPosition(originX + cos(angle) * offset, originY + sin(angle) * offset);
}