#include "stdafx.h"
#include "Level16.h"
#include "../Element/Ring.h"
#include "../Element/Target.h"
#include "../Element/Triangle.h"

USING_NS_CC;

bool Level16::init()
{
	if ( !BaseLevel::init() )
	{
		return false;
	}

	restart();

	return true;
}

void Level16::restart(){
	BaseLevel::restart();

	#define MOVE_BY_X (192 + 32 - 16)

	t1 = Target::create();
	t1->setPosition(E::originX + DESIGNED_WIDTH / 2, E::originY + 440);
	t1->setRotation(-30);
	t1->initBody();
	t1->playAnim(1);
	this->addChild(t1);
	t1->initProtector();

	t2 = Target::create();
	t2->setPosition(E::originX + DESIGNED_WIDTH / 2, E::originY + 440 - 180 - 64);
	t2->setRotation(30);
	t2->initBody();
	t2->playAnim(1);
	this->addChild(t2);
	t2->initProtector();

	#define MOVE_BY_X 64
	auto b1 = Brick::create(128, 24);
	b1->setPosition(E::originX + DESIGNED_WIDTH / 2 - 64, E::originY + 320 + 16 - 64);
	b1->initBody();
	this->addChild(b1);
	auto b12 = Brick::create(96, 16, E::P.C800);
	b12->setPosition(E::originX + DESIGNED_WIDTH/2 - 48, E::originY + 320 - 64);
	b12->initBody();
	b12->runAction(RepeatForever::create(Sequence::create(MoveBy::create(0.5f, Vec2(MOVE_BY_X/2, 0)), MoveBy::create(1.0f, Vec2(-MOVE_BY_X, 0)), MoveBy::create(0.5f, Vec2(MOVE_BY_X/2, 0)), nullptr)));
	b12->runAction(RepeatForever::create(Sequence::create(TintTo::create(1.0f, C3B(E::P.C400)), TintTo::create(1.0f, C3B(E::P.C800)), nullptr)));
	this->addChild(b12);

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

	angle = 0;

}

void Level16::update(float dt){
	angle += dt * 2;
	if(t1->bAlreadyHit == false)
		t1->setPosition(E::originX + DESIGNED_WIDTH / 2 - 128 * cos(angle), E::originY + 320 + 16  + 128 * sin(angle) - 8);
	if(t2->bAlreadyHit == false)
		t2->setPosition(E::originX + DESIGNED_WIDTH / 2 + 128 * cos(angle), E::originY + 320 + 16  - 128 * sin(angle) - 8);
}