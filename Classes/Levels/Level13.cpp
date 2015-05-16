#include "stdafx.h"
#include "Level13.h"
#include "../Element/Ring.h"
#include "../Element/Target.h"
#include "../Element/Diamond.h"
#include "../Element/Brick.h"

USING_NS_CC;

bool Level13::init()
{
	if ( !BaseLevel::init() )
	{
		return false;
	}

	restart();

	return true;
}

void Level13::restart(){
	BaseLevel::restart();

	#define MOVE_BY_X 192

	auto r1 = Ring::create();
	r1->setPosition(E::originX, E::originY + 128);
	r1->setScale(0.2);
	r1->initBody();
	this->addChild(r1);
	r1->runAction(RepeatForever::create(Sequence::create(MoveBy::create(0.5f, Vec2(MOVE_BY_X, 0)), DelayTime::create(1.0f), MoveBy::create(0.5f, Vec2(-MOVE_BY_X, 0)), nullptr)));

	auto r2 = Ring::create();
	r2->setPosition(E::originX + DESIGNED_WIDTH, E::originY + 128);
	r2->setScale(0.2);
	r2->initBody();
	this->addChild(r2);
	r2->runAction(RepeatForever::create(Sequence::create(MoveBy::create(0.5f, Vec2(-MOVE_BY_X, 0)), DelayTime::create(1.0f),MoveBy::create(0.5f, Vec2(MOVE_BY_X, 0)), nullptr)));


	auto t1 = Target::create();
	t1->setPosition(E::originX + DESIGNED_WIDTH / 2, E::originY + 400);
	t1->initBody();
	t1->playAnim(1);
	this->addChild(t1);
	t1->initProtector();

	/*
	auto b_l = Brick::create(E::originX + 96, 32);
	b_l->setPosition(0, E::originY + 32);
	b_l->setRotation(30);
	b_l->initBody();
	this->addChild(b_l);

	auto b_r = Brick::create(E::originX + 96, 32);
	b_r->setPosition(E::originX + DESIGNED_WIDTH - 96, E::originY + 32);
	b_r->setRotation(-30);
	b_r->initBody();
	this->addChild(b_r);
	*/

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

	angle = 0;

}

void Level13::update(float dt){
	angle += dt * 2;
	
	ring1->setPosition(E::originX + DESIGNED_WIDTH / 2 - 128 * cos(angle), E::originY + 400 + 128 * sin(angle) - 8);
	ring2->setPosition(E::originX + DESIGNED_WIDTH / 2 + 128 * cos(angle), E::originY + 400 - 128 * sin(angle) - 8);
}