#include "stdafx.h"
#include "Level20.h"
#include "../Element/Ring.h"
#include "../Element/Target.h"
#include "../Element/Diamond.h"
#include "../Element/Brick.h"

USING_NS_CC;

bool Level20::init()
{
	if ( !BaseLevel::init() )
	{
		return false;
	}

	restart();

	return true;
}

void Level20::restart(){
	BaseLevel::restart();

	#define MOVE_BY_X 192

	auto r1 = Target::create();
	r1->setPosition(E::originX, E::originY + 420);
	r1->setRotation(45);
	r1->initBody();
	this->addChild(r1);
	r1->initProtector(192 - 32);
	r1->runAction(RepeatForever::create(Sequence::create(MoveBy::create(0.5f, Vec2(MOVE_BY_X, 0)), DelayTime::create(1.0f), MoveBy::create(0.5f, Vec2(-MOVE_BY_X, 0)), nullptr)));

	auto r2 = Target::create();
	r2->setPosition(E::originX + DESIGNED_WIDTH, E::originY + 420);
	r2->setRotation(-45);
	r2->initBody();
	this->addChild(r2);
	r2->initProtector(192 - 32);
	r2->runAction(RepeatForever::create(Sequence::create(MoveBy::create(0.5f, Vec2(-MOVE_BY_X, 0)), DelayTime::create(1.0f), MoveBy::create(0.5f, Vec2(MOVE_BY_X, 0)), nullptr)));

	auto ring1 = Ring::create();
	ring1->setPosition(E::originX + DESIGNED_WIDTH / 2 - 80, E::originY + 128 + 64);
	ring1->setScale(0.15);
	ring1->initBody();
	this->addChild(ring1);

	auto ring2 = Ring::create();
	ring2->setPosition(E::originX + DESIGNED_WIDTH / 2 + 80, E::originY + 128 + 64);
	ring2->setScale(0.15);
	ring2->initBody();
	this->addChild(ring2);

	auto b1 = Brick::create(192, 24);
	b1->setRotation(45);
	b1->setPosition(E::originX + DESIGNED_WIDTH / 2 - 192 + 32, E::originY + 96 );
	b1->initBody();
	this->addChild(b1);
	auto b12 = Brick::create(192, 16, E::P.C800);
	b12->setRotation(45);
	b12->setPosition(E::originX + DESIGNED_WIDTH / 2 - 192 + 32 + 16, E::originY + 96 + 8);
	b12->initBody();
	this->addChild(b12);

	auto b2 = Brick::create(192, 24);
	b2->setRotation(-45);
	b2->setPosition(E::originX + DESIGNED_WIDTH / 2 - 192 + 32 + 128, E::originY + 96 );
	b2->initBody();
	this->addChild(b2);
	auto b22 = Brick::create(192, 16, E::P.C800);
	b22->setRotation(-45);
	b22->setPosition(E::originX + DESIGNED_WIDTH / 2 - 192 + 32 - 16 + 128, E::originY + 96 + 8);
	b22->initBody();
	this->addChild(b22);

	auto diamond1 = Diamond::create();
	diamond1->setScale(0.9f);
	diamond1->setRotation(30);
	diamond1->setPosition(E::originX - 128, E::originY + 256 + 64);
	diamond1->initBody();
	this->addChild(diamond1);

	auto diamond2 = Diamond::create();
	diamond2->setScale(0.9f);
	diamond2->setRotation(-30);
	diamond2->setPosition(E::originX + DESIGNED_WIDTH + 128, E::originY + 256 + 64);
	diamond2->initBody();
	this->addChild(diamond2);

}

void Level20::update(float dt){
}