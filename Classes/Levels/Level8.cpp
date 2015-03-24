#include "stdafx.h"
#include "Level8.h"
#include "Element/Ring.h"
#include "Element/Target.h"
#include "Element/Block.h"
#include "Element/Diamond.h"

USING_NS_CC;

bool Level8::init()
{
	if ( !BaseLevel::init() )
	{
		return false;
	}

	restart();

	return true;
}

void Level8::restart(){
	BaseLevel::restart();

	ring = Ring::create();
	ring->setPosition(E::originX, E::originY + 96);
	ring->setScale(0.2);
	ring->initBody();
	this->addChild(ring);

	auto t = Target::create();
	t->setPosition(E::originX + DESIGNED_WIDTH / 2  - 128, E::originY + 400);
	t->initBody();
	this->addChild(t);
	t->playAnim(0);
	
#define MOVE_BY_X 64
	auto b1 = Block::create(256, 24);
	b1->setPosition(E::originX, E::originY + 320);
	b1->initBody();
	this->addChild(b1);
	auto b12 = Block::create(256, 16, E::P.C800);
	b12->setPosition(E::originX, E::originY + 320 - 16);
	b12->initBody();
	b12->runAction(RepeatForever::create(Sequence::create(MoveBy::create(1.0f, Vec2(MOVE_BY_X, 0)), MoveBy::create(1.0f, Vec2(-MOVE_BY_X, 0)), nullptr)));
	b12->runAction(RepeatForever::create(Sequence::create(TintTo::create(1.0f, C3B(E::P.C400)), TintTo::create(1.0f, C3B(E::P.C800)), nullptr)));
	this->addChild(b12);

	auto diamond1 = Diamond::create();
	diamond1->setScale(0.8f);
	diamond1->setRotation(-30);
	diamond1->setPosition(E::originX - 128, E::originY + 256 + 64);
	diamond1->initBody();
	this->addChild(diamond1);

	auto diamond2 = Diamond::create();
	diamond2->setScale(0.8f);
	diamond2->setRotation(30);
	diamond2->setPosition(E::originX + DESIGNED_WIDTH + 128, E::originY + 256 + 64);
	diamond2->initBody();
	this->addChild(diamond2);


}

void Level8::update(float dt){
	static float tick = 0;
	int originX = E::originX + DESIGNED_WIDTH / 2 + 64;
	int originY = E::originY + 192 - 48;
	tick += dt;
	float angle = PI * tick;
	int offset = 64;
	ring->setPosition(originX + cos(angle) * offset, originY + sin(angle) * offset);
}