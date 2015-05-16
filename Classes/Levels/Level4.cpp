#include "stdafx.h"
#include "Level4.h"
#include "../Element/Ring.h"
#include "../Element/Target.h"
#include "../Element/Triangle.h"

USING_NS_CC;

bool Level4::init()
{
	if ( !BaseLevel::init() )
	{
		return false;
	}

	restart();

	return true;
}

void Level4::restart(){
	BaseLevel::restart();

	#define MOVE_BY_X (192 + 32 - 16)

	auto t1 = Target::create();
	t1->setPosition(E::originX + DESIGNED_WIDTH / 2, E::originY + 440);
	t1->initBody();
	t1->playAnim(1);
	this->addChild(t1);

	auto t2 = Target::create();
	t2->setPosition(E::originX + DESIGNED_WIDTH / 2, E::originY + 440 - 180);
	t2->setRotation(30);
	t2->initBody();
	t2->playAnim(1);
	this->addChild(t2);

	auto t3 = Target::create();
	t3->setPosition(E::originX + DESIGNED_WIDTH / 2, E::originY + 440 - 360);
	t3->setRotation(-30);
	t3->initBody();
	t3->playAnim(1);
	this->addChild(t3);

	#define MOVE_BY_X 64
	auto b1 = Brick::create(128, 24);
	b1->setPosition(E::originX + DESIGNED_WIDTH / 2 - 64, E::originY + 320 + 16);
	b1->initBody();
	this->addChild(b1);
	auto b12 = Brick::create(96, 16, E::P.C800);
	b12->setPosition(E::originX + DESIGNED_WIDTH/2 - 48, E::originY + 320);
	b12->initBody();
	b12->runAction(RepeatForever::create(Sequence::create(MoveBy::create(0.5f, Vec2(MOVE_BY_X/2, 0)), MoveBy::create(1.0f, Vec2(-MOVE_BY_X, 0)), MoveBy::create(0.5f, Vec2(MOVE_BY_X/2, 0)), nullptr)));
	b12->runAction(RepeatForever::create(Sequence::create(TintTo::create(1.0f, C3B(E::P.C400)), TintTo::create(1.0f, C3B(E::P.C800)), nullptr)));
	this->addChild(b12);

	auto b2 = Brick::create(128, 24);
	b2->setPosition(E::originX + DESIGNED_WIDTH / 2 - 64, E::originY + 320 + 16 - 180);
	b2->initBody();
	this->addChild(b2);
	auto b22 = Brick::create(96, 16, E::P.C800);
	b22->setPosition(E::originX + DESIGNED_WIDTH/2 - 48, E::originY + 320 - 180);
	b22->initBody();
	b22->runAction(RepeatForever::create(Sequence::create(MoveBy::create(0.5f, Vec2(MOVE_BY_X/2, 0)), MoveBy::create(1.0f, Vec2(-MOVE_BY_X, 0)), MoveBy::create(0.5f, Vec2(MOVE_BY_X/2, 0)), nullptr)));
	b22->runAction(RepeatForever::create(Sequence::create(TintTo::create(1.0f, C3B(E::P.C400)), TintTo::create(1.0f, C3B(E::P.C800)), nullptr)));
	this->addChild(b22);

	auto triangle = Triangle::create();
	triangle->setScale(0.5f);
	triangle->setRotation(-90);
	triangle->setPosition(E::originX - 128, E::originY + 320);
	triangle->initBody();
	this->addChild(triangle);

	auto triangle2 = Triangle::create();
	triangle2->setScale(0.5f);
	triangle2->setRotation(90);
	triangle2->setPosition(E::originX + DESIGNED_WIDTH + 128, E::originY + 320);
	triangle2->initBody();
	this->addChild(triangle2);


}

void Level4::update(float dt){
}