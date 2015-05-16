#include "stdafx.h"
#include "Level7.h"
#include "../Element/Ring.h"
#include "../Element/Target.h"
#include "../Element/Diamond.h"
#include "../Element/Brick.h"

USING_NS_CC;

bool Level7::init()
{
	if ( !BaseLevel::init() )
	{
		return false;
	}

	restart();

	return true;
}

void Level7::restart(){
	BaseLevel::restart();

	#define MOVE_BY_Y (128+32)

	auto t = Target::create();
	t->setPosition(E::originX + DESIGNED_WIDTH / 2, E::originY + 320);
	t->setRotation(180);
	t->initBody();
	this->addChild(t);
	t->runAction(RepeatForever::create(Sequence::create(MoveBy::create(1.2f, Vec2(0, -MOVE_BY_Y)), MoveBy::create(1.2f, Vec2(0, MOVE_BY_Y)), nullptr)));

	auto ring1 = Ring::create();
	ring1->setPosition(E::originX + DESIGNED_WIDTH / 2 - 96, E::originY + 320 + 64);
	ring1->setScale(0.12);
	ring1->initBody();
	this->addChild(ring1);
	ring1->runAction(RepeatForever::create(Sequence::create(MoveBy::create(1.2f, Vec2(0, -MOVE_BY_Y)), MoveBy::create(1.2f, Vec2(0, MOVE_BY_Y)), nullptr)));

	auto ring2 = Ring::create();
	ring2->setPosition(E::originX + DESIGNED_WIDTH / 2 + 96, E::originY + 320 + 64);
	ring2->setScale(0.12);
	ring2->initBody();
	this->addChild(ring2);
	ring2->runAction(RepeatForever::create(Sequence::create(MoveBy::create(1.2f, Vec2(0, -MOVE_BY_Y)), MoveBy::create(1.2f, Vec2(0, MOVE_BY_Y)), nullptr)));

	auto b1 = Brick::create(192, 24);
	b1->setRotation(45);
	b1->setPosition(E::originX + DESIGNED_WIDTH / 2 - 192 + 32, E::originY + 96 + 192);
	b1->initBody();
	this->addChild(b1);
	auto b12 = Brick::create(192, 16, E::P.C800);
	b12->setRotation(45);
	b12->setPosition(E::originX + DESIGNED_WIDTH / 2 - 192 + 32 + 16, E::originY + 96 + 192 + 8);
	b12->initBody();
	this->addChild(b12);
	b1->runAction(RepeatForever::create(Sequence::create(MoveBy::create(1.2f, Vec2(0, -MOVE_BY_Y)), MoveBy::create(1.2f, Vec2(0, MOVE_BY_Y)), nullptr)));
	b12->runAction(RepeatForever::create(Sequence::create(MoveBy::create(1.2f, Vec2(0, -MOVE_BY_Y)), MoveBy::create(1.2f, Vec2(0, MOVE_BY_Y)), nullptr)));

	auto b2 = Brick::create(192, 24);
	b2->setRotation(-45);
	b2->setPosition(E::originX + DESIGNED_WIDTH / 2 - 192 + 32 + 128, E::originY + 96 + 192);
	b2->initBody();
	this->addChild(b2);
	auto b22 = Brick::create(192, 16, E::P.C800);
	b22->setRotation(-45);
	b22->setPosition(E::originX + DESIGNED_WIDTH / 2 - 192 + 32 - 16 + 128, E::originY + 96 + 192 + 8);
	b22->initBody();
	this->addChild(b22);
	b2->runAction(RepeatForever::create(Sequence::create(MoveBy::create(1.2f, Vec2(0, -MOVE_BY_Y)), MoveBy::create(1.2f, Vec2(0, MOVE_BY_Y)), nullptr)));
	b22->runAction(RepeatForever::create(Sequence::create(MoveBy::create(1.2f, Vec2(0, -MOVE_BY_Y)), MoveBy::create(1.2f, Vec2(0, MOVE_BY_Y)), nullptr)));

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

void Level7::update(float dt){
}