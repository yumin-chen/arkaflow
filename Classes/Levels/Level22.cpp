#include "stdafx.h"
#include "Level22.h"
#include "Element/Ring.h"
#include "Element/Target.h"
#include "Element/Triangle.h"
#include "Element/Block.h"

USING_NS_CC;

bool Level22::init()
{
	if ( !BaseLevel::init() )
	{
		return false;
	}

	restart();

	return true;
}

void Level22::restart(){
	BaseLevel::restart();

	ring = Ring::create();
	ring->setPosition(E::originX, E::originY + 96);
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
	auto b1 = Block::create(E::originX + DESIGNED_WIDTH - 192, 24);
	b1->setPosition(0, E::originY + 360);
	b1->initBody();
	this->addChild(b1);
	auto b12 = Block::create(E::originX + DESIGNED_WIDTH - 192, 16, E::P.C800);
	b12->setPosition(0, E::originY + 360 - 16);
	b12->initBody();
	b12->runAction(RepeatForever::create(Sequence::create(MoveBy::create(1.0f, Vec2(MOVE_BY_X, 0)), MoveBy::create(1.0f, Vec2(-MOVE_BY_X, 0)), nullptr)));
	b12->runAction(RepeatForever::create(Sequence::create(TintTo::create(1.0f, C3B(E::P.C400)), TintTo::create(1.0f, C3B(E::P.C800)), nullptr)));
	this->addChild(b12);

	auto b3 = Block::create(24, 192);
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

void Level22::update(float dt){
	static float tick = 0;
	int originX = E::originX + DESIGNED_WIDTH / 2;
	int originY = E::originY + 192;
	tick += dt;
	float angle = PI * tick;
	int offset = 96;
	ring->setPosition(originX + cos(angle) * offset, originY + sin(angle) * offset);
}