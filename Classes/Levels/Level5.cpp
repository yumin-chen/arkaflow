#include "stdafx.h"
#include "Level5.h"
#include "../Element/Ring.h"
#include "../Element/Target.h"
#include "../Element/Triangle.h"
#include "../Element/Brick.h"
#include "../Element/Diamond.h"

USING_NS_CC;

bool Level5::init()
{
	if ( !BaseLevel::init() )
	{
		return false;
	}

	restart();

	return true;
}

void Level5::restart(){
	BaseLevel::restart();
#define MOVE_X_____ 64
	auto t1 = Target::create();
	t1->setPosition(E::originX + DESIGNED_WIDTH / 2 - 96, E::originY + 480);
	t1->setRotation(180);
	t1->initBody();
	t1->playAnim(1);
	this->addChild(t1);
	t1->runAction(RepeatForever::create(Sequence::create(MoveBy::create(0.5f, Vec2(MOVE_X_____, 0)), MoveBy::create(0.5f, Vec2(-MOVE_X_____, 0)), nullptr)));

	auto t2 = Target::create();
	t2->setPosition(E::originX + DESIGNED_WIDTH / 2 + 96, E::originY + 480);
	t2->setRotation(180);
	t2->initBody();
	t2->playAnim(1);
	this->addChild(t2);
	t2->runAction(RepeatForever::create(Sequence::create(MoveBy::create(0.5f, Vec2(-MOVE_X_____, 0)), MoveBy::create(0.5f, Vec2(MOVE_X_____, 0)), nullptr)));

	auto ring0 = Ring::create();
	ring0->setScale(0.15f);
	ring0->setPosition(E::originX + DESIGNED_WIDTH / 2, E::originY + 256);
	ring0->initBody();
	addChild(ring0);
	ring0->runAction(RepeatForever::create(Sequence::create(ScaleTo::create(0.5f, 0.15f), ScaleTo::create(0.5f, 0.0f), nullptr)));

	ring1 = Ring::create();
	ring1->setScale(0.15f);
	ring1->setPosition(E::originX + DESIGNED_WIDTH / 2, E::originY + 256);
	ring1->initBody();
	addChild(ring1);
	ring1->runAction(RepeatForever::create(Sequence::create(ScaleTo::create(0.5f, 0.15f), ScaleTo::create(0.5f, 0.0f), nullptr)));

	ring2 = Ring::create();
	ring2->setScale(0.15f);
	ring2->setPosition(E::originX + DESIGNED_WIDTH / 2, E::originY + 256);
	ring2->initBody();
	addChild(ring2);
	ring2->runAction(RepeatForever::create(Sequence::create(ScaleTo::create(0.5f, 0.15f), ScaleTo::create(0.5f, 0.0f), nullptr)));

	ring3 = Ring::create();
	ring3->setScale(0.15f);
	ring3->setPosition(E::originX + DESIGNED_WIDTH / 2, E::originY + 256);
	ring3->initBody();
	addChild(ring3);
	ring3->runAction(RepeatForever::create(Sequence::create(ScaleTo::create(0.5f, 0.15f), ScaleTo::create(0.5f, 0.0f), nullptr)));

	ring4 = Ring::create();
	ring4->setScale(0.15f);
	ring4->setPosition(E::originX + DESIGNED_WIDTH / 2, E::originY + 256);
	ring4->initBody();
	addChild(ring4);
	ring4->runAction(RepeatForever::create(Sequence::create(ScaleTo::create(0.5f, 0.15f), ScaleTo::create(0.5f, 0.0f), nullptr)));

	auto diamond1 = Diamond::create();
	diamond1->setScale(0.9f);
	diamond1->setRotation(-45);
	diamond1->setPosition(E::originX - 128, E::originY + 256 + 64);
	diamond1->initBody();
	this->addChild(diamond1);

	auto diamond2 = Diamond::create();
	diamond2->setScale(0.9f);
	diamond2->setRotation(45);
	diamond2->setPosition(E::originX + DESIGNED_WIDTH + 128, E::originY + 256 + 64);
	diamond2->initBody();
	this->addChild(diamond2);
}

void Level5::update(float dt){
	static float tick = 0;
	static bool isReturning = false;
	int originX = E::originX + DESIGNED_WIDTH / 2;
	int originY = E::originY + 256;
	tick += dt * - (int(isReturning) * 2 - 1);
	if(tick > 0.5){
		isReturning = true;
	}
	else if(tick < 0){
		isReturning = false;
	}
	float angle = PI * tick;
	int offset = 256 * tick;
	ring1->setPosition(originX + offset * cos(angle), originY - offset * sin(angle));
	ring2->setPosition(originX + offset * cos(angle), originY + offset * sin(angle));
	ring3->setPosition(originX - offset * cos(angle), originY - offset * sin(angle));
	ring4->setPosition(originX - offset * cos(angle), originY + offset * sin(angle));
}