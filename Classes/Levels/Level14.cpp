#include "stdafx.h"
#include "Level14.h"
#include "Element/Ring.h"
#include "Element/Triangle.h"
#include "Element/Target.h"
#include "Element/Block.h"

USING_NS_CC;

bool Level14::init()
{
	if ( !BaseLevel::init() )
	{
		return false;
	}

	restart();

	return true;
}

void Level14::restart(){
	BaseLevel::restart();

#define MOVE_BY_X 256

	auto t = Target::create();
	t->setPosition(E::originX + DESIGNED_WIDTH / 2 - MOVE_BY_X/2 - 128, E::originY + 440);
	t->initBody();
	this->addChild(t);
	t->setRotation(-45);
	t->playAnim(0);
	t->runAction(RepeatForever::create(Sequence::create(MoveBy::create(1.6f, Vec2(MOVE_BY_X, 0)), MoveBy::create(1.6f, Vec2(-MOVE_BY_X, 0)), nullptr)));
	t->initProtector(192);
#define MOVE_BY_X 64
	auto b1 = Block::create(E::originX + DESIGNED_WIDTH - 128, 24);
	b1->setPosition(0, E::originY + 320);
	b1->initBody();
	this->addChild(b1);
	auto b12 = Block::create(E::originX + DESIGNED_WIDTH - 128, 16, E::P.C800);
	b12->setPosition(0, E::originY + 320 - 16);
	b12->initBody();
	b12->runAction(RepeatForever::create(Sequence::create(MoveBy::create(1.0f, Vec2(MOVE_BY_X, 0)), MoveBy::create(1.0f, Vec2(-MOVE_BY_X, 0)), nullptr)));
	b12->runAction(RepeatForever::create(Sequence::create(TintTo::create(1.0f, C3B(E::P.C400)), TintTo::create(1.0f, C3B(E::P.C800)), nullptr)));
	this->addChild(b12);

	auto ring0 = Ring::create();
	ring0->setScale(0.15f);
	ring0->setPosition(E::originX + DESIGNED_WIDTH / 2, E::originY + 192);
	ring0->initBody();
	addChild(ring0);
	ring0->runAction(RepeatForever::create(Sequence::create(ScaleTo::create(0.5f, 0.15f), ScaleTo::create(0.5f, 0.0f), nullptr)));

	ring1 = Ring::create();
	ring1->setScale(0.15f);
	ring1->setPosition(E::originX + DESIGNED_WIDTH / 2, E::originY + 192);
	ring1->initBody();
	addChild(ring1);
	ring1->runAction(RepeatForever::create(Sequence::create(ScaleTo::create(0.5f, 0.15f), ScaleTo::create(0.5f, 0.0f), nullptr)));

	ring2 = Ring::create();
	ring2->setScale(0.15f);
	ring2->setPosition(E::originX + DESIGNED_WIDTH / 2, E::originY + 192);
	ring2->initBody();
	addChild(ring2);
	ring2->runAction(RepeatForever::create(Sequence::create(ScaleTo::create(0.5f, 0.15f), ScaleTo::create(0.5f, 0.0f), nullptr)));

	ring3 = Ring::create();
	ring3->setScale(0.15f);
	ring3->setPosition(E::originX + DESIGNED_WIDTH / 2, E::originY + 192);
	ring3->initBody();
	addChild(ring3);
	ring3->runAction(RepeatForever::create(Sequence::create(ScaleTo::create(0.5f, 0.15f), ScaleTo::create(0.5f, 0.0f), nullptr)));

	ring4 = Ring::create();
	ring4->setScale(0.15f);
	ring4->setPosition(E::originX + DESIGNED_WIDTH / 2, E::originY + 256);
	ring4->initBody();
	addChild(ring4);
	ring4->runAction(RepeatForever::create(Sequence::create(ScaleTo::create(0.5f, 0.15f), ScaleTo::create(0.5f, 0.0f), nullptr)));


	auto triangle2 = Triangle::create();
	triangle2->setScale(0.6f);
	triangle2->setRotation(30);
	triangle2->setPosition(E::originX + DESIGNED_WIDTH + 96, E::originY + 256);
	triangle2->initBody();
	this->addChild(triangle2);


}

void Level14::update(float dt){
	static float tick = 0;
	static bool isReturning = false;
	int originX = E::originX + DESIGNED_WIDTH / 2;
	int originY = E::originY + 192;
	tick += dt / 2 * - (int(isReturning) * 2 - 1);
	if(tick > 0.5){
		isReturning = true;
	}
	else if(tick < 0){
		isReturning = false;
	}
	float angle = PI * tick;
	int offset = 256 * tick;
	ring1->setPosition(originX + offset * sin(angle), originY + offset * cos(angle));
	angle += PI/2;
	ring2->setPosition(originX + offset * sin(angle), originY + offset * cos(angle));
	angle += PI/2;
	ring3->setPosition(originX + offset * sin(angle), originY + offset * cos(angle));
	angle += PI/2;
	ring4->setPosition(originX + offset * sin(angle), originY + offset * cos(angle));
}