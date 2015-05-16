#include "stdafx.h"
#include "Level3.h"
#include "../Element/Ring.h"
#include "../Element/Target.h"
#include "../Element/Triangle.h"
#include "../Element/Brick.h"

USING_NS_CC;

bool Level3::init()
{
	if ( !BaseLevel::init() )
	{
		return false;
	}

	restart();

	return true;
}

void Level3::restart(){
	BaseLevel::restart();

/*
	#define MOVE_BY_X 192

	auto r1 = Ring::create();
	r1->setPosition(E::originX, E::originY + 128 + 32);
	r1->setScale(0.15);
	r1->initBody();
	this->addChild(r1);
	r1->runAction(RepeatForever::create(Sequence::create(MoveBy::create(0.5f, Vec2(MOVE_BY_X, 0)), DelayTime::create(1.0f), MoveBy::create(0.5f, Vec2(-MOVE_BY_X, 0)), nullptr)));

	auto r2 = Ring::create();
	r2->setPosition(E::originX + DESIGNED_WIDTH, E::originY + 80);
	r2->setScale(0.15);
	r2->initBody();
	this->addChild(r2);
	r2->runAction(RepeatForever::create(Sequence::create(MoveBy::create(0.5f, Vec2(-MOVE_BY_X, 0)), DelayTime::create(1.0f),MoveBy::create(0.5f, Vec2(MOVE_BY_X, 0)), nullptr)));

*/

	auto t1 = Target::create();
	t1->setPosition(E::originX + DESIGNED_WIDTH / 2, E::originY + 400);
	t1->initBody();
	t1->playAnim(1);
	this->addChild(t1);

	auto b = Brick::create(128, 32);
	b->setPosition(E::originX + DESIGNED_WIDTH / 2 -64, E::originY + 128);
	b->initBody();
	this->addChild(b);
	auto b2 = Brick::create(96, 16, E::P.C800);
	b2->setPosition(E::originX + DESIGNED_WIDTH / 2 -48, E::originY + 128 - 8);
	b2->initBody();
	b2->runAction(RepeatForever::create(Sequence::create(MoveBy::create(0.5f, Vec2(48, 0)), MoveBy::create(1.0f, Vec2(-96, 0)), MoveBy::create(0.5f, Vec2(48, 0)), nullptr)));
	b2->runAction(RepeatForever::create(Sequence::create(TintTo::create(1.0f, C3B(E::P.C400)), TintTo::create(1.0f, C3B(E::P.C800)), nullptr)));
	this->addChild(b2);

	ring1 = Ring::create();
	ring1->setPosition(E::originX + DESIGNED_WIDTH / 2 - 80, E::originY + 400);
	ring1->setScale(0.1);
	ring1->initBody();
	this->addChild(ring1);

	ring2 = Ring::create();
	ring2->setPosition(E::originX + DESIGNED_WIDTH / 2 + 80, E::originY + 400);
	ring2->setScale(0.1);
	ring2->initBody();
	this->addChild(ring2);

	auto triangle = Triangle::create();
	triangle->setScale(0.6f);
	triangle->setRotation(30);
	triangle->setPosition(E::originX - 256, E::originY + 256);
	triangle->initBody();
	this->addChild(triangle);

	auto triangle2 = Triangle::create();
	triangle2->setScale(0.6f);
	triangle2->setRotation(-30);
	triangle2->setPosition(E::originX + DESIGNED_WIDTH + 256, E::originY + 256);
	triangle2->initBody();
	this->addChild(triangle2);

	angle = 0;

}

void Level3::update(float dt){
	angle += dt * 2;
	
	ring1->setPosition(E::originX + DESIGNED_WIDTH / 2 - 96 * cos(angle), E::originY + 400 + 96 * sin(angle) - 8);
	ring2->setPosition(E::originX + DESIGNED_WIDTH / 2 + 96 * cos(angle), E::originY + 400 - 96 * sin(angle) - 8);
}