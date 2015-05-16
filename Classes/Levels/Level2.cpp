#include "stdafx.h"
#include "Level2.h"
#include "../Element/Triangle.h"
#include "../Element/Target.h"
#include "../Element/Brick.h"

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


#define MOVE_BY_X 256

	auto t = Target::create();
	t->setPosition(E::originX + DESIGNED_WIDTH / 2 - MOVE_BY_X/2 - 128, E::originY + 480);
	t->initBody();
	this->addChild(t);
	t->playAnim(0);
	t->runAction(RepeatForever::create(Sequence::create(MoveBy::create(1.6f, Vec2(MOVE_BY_X, 0)), MoveBy::create(1.6f, Vec2(-MOVE_BY_X, 0)), nullptr)));

	auto t3 = Target::create();
	t3->setPosition(E::originX + DESIGNED_WIDTH / 2 - MOVE_BY_X/2 + 128, E::originY + 256);
	t3->initBody();
	this->addChild(t3);
	t3->playAnim(0);
	t3->runAction(RepeatForever::create(Sequence::create(MoveBy::create(1.6f, Vec2(MOVE_BY_X, 0)), MoveBy::create(1.6f, Vec2(-MOVE_BY_X, 0)), nullptr)));

#define MOVE_BY_X 64
	auto b1 = Brick::create(E::originX + DESIGNED_WIDTH - 256, 24);
	b1->setPosition(0, E::originY + 400);
	b1->initBody();
	this->addChild(b1);
	auto b12 = Brick::create(E::originX + DESIGNED_WIDTH - 256, 16, E::P.C800);
	b12->setPosition(0, E::originY + 400 - 16);
	b12->initBody();
	b12->runAction(RepeatForever::create(Sequence::create(MoveBy::create(1.0f, Vec2(MOVE_BY_X, 0)), MoveBy::create(1.0f, Vec2(-MOVE_BY_X, 0)), nullptr)));
	b12->runAction(RepeatForever::create(Sequence::create(TintTo::create(1.0f, C3B(E::P.C400)), TintTo::create(1.0f, C3B(E::P.C800)), nullptr)));
	this->addChild(b12);

#define MOVE_BY_X -64
	auto b2 = Brick::create(E::originX + DESIGNED_WIDTH - 256, 24);
	b2->setPosition(E::originX + 256, E::originY + 128);
	b2->initBody();
	this->addChild(b2);
	auto b22 = Brick::create(E::originX + DESIGNED_WIDTH - 256, 16, E::P.C800);
	b22->setPosition(E::originX + 256, E::originY + 128 - 16);
	b22->initBody();
	b22->runAction(RepeatForever::create(Sequence::create(MoveBy::create(1.0f, Vec2(MOVE_BY_X, 0)), MoveBy::create(1.0f, Vec2(-MOVE_BY_X, 0)), nullptr)));
	b22->runAction(RepeatForever::create(Sequence::create(TintTo::create(1.0f, C3B(E::P.C400)), TintTo::create(1.0f, C3B(E::P.C800)), nullptr)));
	this->addChild(b22);

	auto triangle = Triangle::create();
	triangle->setScale(0.6f);
	triangle->setRotation(-30);
	triangle->setPosition(E::originX - 128, E::originY + 192);
	triangle->initBody();
	this->addChild(triangle);

	auto triangle2 = Triangle::create();
	triangle2->setScale(0.6f);
	triangle2->setRotation(30);
	triangle2->setPosition(E::originX + DESIGNED_WIDTH + 128, E::originY + 256);
	triangle2->initBody();
	this->addChild(triangle2);
}

void Level2::update(float dt){
}