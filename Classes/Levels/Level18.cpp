#include "stdafx.h"
#include "Level18.h"
#include "../Element/Ring.h"
#include "../Element/Target.h"
#include "../Element/Diamond.h"
#include "../Element/Brick.h"

USING_NS_CC;

bool Level18::init()
{
	if ( !BaseLevel::init() )
	{
		return false;
	}

	restart();

	return true;
}

void Level18::restart(){
	BaseLevel::restart();

	#define MOVE_BY_Y (32)
#define Y_OFFSET 64

	auto t = Target::create();
	t->setPosition(E::originX + DESIGNED_WIDTH / 2, E::originY + 320 + Y_OFFSET);
	t->setRotation(180);
	t->initBody();
	this->addChild(t);
	t->runAction(RepeatForever::create(Sequence::create(MoveBy::create(1.2f, Vec2(0, -MOVE_BY_Y)), MoveBy::create(1.2f, Vec2(0, MOVE_BY_Y)), nullptr)));

	auto t2 = Target::create();
	t2->setPosition(E::originX + DESIGNED_WIDTH / 2 + 128, E::originY + 320 - 96 + 16 + Y_OFFSET);
	t2->initBody();
	this->addChild(t2);
	t2->runAction(RepeatForever::create(Sequence::create(MoveBy::create(1.2f, Vec2(0, -MOVE_BY_Y)), MoveBy::create(1.2f, Vec2(0, MOVE_BY_Y)), nullptr)));

	auto t3 = Target::create();
	t3->setPosition(E::originX + DESIGNED_WIDTH / 2 - 128, E::originY + 320 - 256 + Y_OFFSET);
	t3->setRotation(180);
	t3->initBody();
	this->addChild(t3);
	t3->runAction(RepeatForever::create(Sequence::create(MoveBy::create(1.2f, Vec2(0, -MOVE_BY_Y)), MoveBy::create(1.2f, Vec2(0, MOVE_BY_Y)), nullptr)));


	auto ring1 = Ring::create();
	ring1->setPosition(E::originX + DESIGNED_WIDTH / 2 - 96, E::originY + 320 - 128 + 64 + Y_OFFSET);
	ring1->setScale(0.12);
	ring1->initBody();
	this->addChild(ring1);
	ring1->runAction(RepeatForever::create(Sequence::create(MoveBy::create(1.2f, Vec2(0, -MOVE_BY_Y)), MoveBy::create(1.2f, Vec2(0, MOVE_BY_Y)), nullptr)));

	auto ring2 = Ring::create();
	ring2->setPosition(E::originX + DESIGNED_WIDTH / 2 + 96, E::originY + 320 + 64 + Y_OFFSET);
	ring2->setScale(0.12);
	ring2->initBody();
	this->addChild(ring2);
	ring2->runAction(RepeatForever::create(Sequence::create(MoveBy::create(1.2f, Vec2(0, -MOVE_BY_Y)), MoveBy::create(1.2f, Vec2(0, MOVE_BY_Y)), nullptr)));

	auto ring3 = Ring::create();
	ring3->setPosition(E::originX + DESIGNED_WIDTH / 2 + 96, E::originY + 320 + 64 - 256 + Y_OFFSET);
	ring3->setScale(0.12);
	ring3->initBody();
	this->addChild(ring3);
	ring3->runAction(RepeatForever::create(Sequence::create(MoveBy::create(1.2f, Vec2(0, -MOVE_BY_Y)), MoveBy::create(1.2f, Vec2(0, MOVE_BY_Y)), nullptr)));

	auto b1 = Brick::create(192, 24);
	b1->setRotation(45);
	b1->setPosition(E::originX + DESIGNED_WIDTH / 2 - 192 + 32, E::originY + 96 + 192 - 128 + Y_OFFSET);
	b1->initBody();
	this->addChild(b1);
	auto b12 = Brick::create(192, 16, E::P.C800);
	b12->setRotation(45);
	b12->setPosition(E::originX + DESIGNED_WIDTH / 2 - 192 + 32 + 16, E::originY + 96 + 192 - 128 + 8 + Y_OFFSET);
	b12->initBody();
	this->addChild(b12);
	b1->runAction(RepeatForever::create(Sequence::create(MoveBy::create(1.2f, Vec2(0, -MOVE_BY_Y)), MoveBy::create(1.2f, Vec2(0, MOVE_BY_Y)), nullptr)));
	b12->runAction(RepeatForever::create(Sequence::create(MoveBy::create(1.2f, Vec2(0, -MOVE_BY_Y)), MoveBy::create(1.2f, Vec2(0, MOVE_BY_Y)), nullptr)));

	auto b2 = Brick::create(192, 24);
	b2->setRotation(-45);
	b2->setPosition(E::originX + DESIGNED_WIDTH / 2 - 192 + 32 + 128, E::originY + 96 + 192 + Y_OFFSET);
	b2->initBody();
	this->addChild(b2);
	auto b22 = Brick::create(192, 16, E::P.C800);
	b22->setRotation(-45);
	b22->setPosition(E::originX + DESIGNED_WIDTH / 2 - 192 + 32 - 16 + 128, E::originY + 96 + 192 + 8 + Y_OFFSET);
	b22->initBody();
	this->addChild(b22);
	b2->runAction(RepeatForever::create(Sequence::create(MoveBy::create(1.2f, Vec2(0, -MOVE_BY_Y)), MoveBy::create(1.2f, Vec2(0, MOVE_BY_Y)), nullptr)));
	b22->runAction(RepeatForever::create(Sequence::create(MoveBy::create(1.2f, Vec2(0, -MOVE_BY_Y)), MoveBy::create(1.2f, Vec2(0, MOVE_BY_Y)), nullptr)));

	auto b3 = Brick::create(192, 24);
	b3->setRotation(-45);
	b3->setPosition(E::originX + DESIGNED_WIDTH / 2 - 192 + 32 + 128, E::originY + 96 + 192 - 256 + Y_OFFSET);
	b3->initBody();
	this->addChild(b3);
	auto b32 = Brick::create(192, 16, E::P.C800);
	b32->setRotation(-45);
	b32->setPosition(E::originX + DESIGNED_WIDTH / 2 - 192 + 32 - 16 + 128, E::originY + 96 + 192 - 256 + 8 + Y_OFFSET);
	b32->initBody();
	this->addChild(b32);
	b3->runAction(RepeatForever::create(Sequence::create(MoveBy::create(1.2f, Vec2(0, -MOVE_BY_Y)), MoveBy::create(1.2f, Vec2(0, MOVE_BY_Y)), nullptr)));
	b32->runAction(RepeatForever::create(Sequence::create(MoveBy::create(1.2f, Vec2(0, -MOVE_BY_Y)), MoveBy::create(1.2f, Vec2(0, MOVE_BY_Y)), nullptr)));

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

void Level18::update(float dt){
}