#include "stdafx.h"
#include "Level9.h"
#include "../Element/Ring.h"
#include "../Element/Target.h"
#include "../Element/Triangle.h"
#include "../Element/Brick.h"
#include "../Element/Diamond.h"

USING_NS_CC;

bool Level9::init()
{
	if ( !BaseLevel::init() )
	{
		return false;
	}

	restart();

	return true;
}

void Level9::restart(){
	BaseLevel::restart();
#define MOVE_X_____ 64
	auto t = Target::create();
	t->setPosition(E::originX + DESIGNED_WIDTH / 2 , E::originY + 480);
	t->setRotation(180);
	t->initBody();
	t->playAnim(1);
	this->addChild(t);

	#define MOVE_BY_X 64
	auto b1 = Brick::create(128, 24);
	b1->setPosition(E::originX + (DESIGNED_WIDTH - 128) / 2, E::originY + 400);
	b1->initBody();
	this->addChild(b1);
	auto b12 = Brick::create(128, 16, E::P.C800);
	b12->setPosition(E::originX + (DESIGNED_WIDTH - 128) / 2, E::originY + 400 - 16);
	b12->initBody();
	b12->runAction(RepeatForever::create(Sequence::create(MoveBy::create(0.5f, Vec2(MOVE_BY_X/2, 0)), MoveBy::create(1.0f, Vec2(-MOVE_BY_X, 0)), MoveBy::create(-.5f, Vec2(MOVE_BY_X/2, 0)), nullptr)));
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

void Level9::update(float dt){
	static float tick = 0;
	static bool isReturning = false;
	int originX = E::originX + DESIGNED_WIDTH / 2;
	int originY = E::originY + 192;
	tick += dt * 0.75 * - (int(isReturning) * 2 - 1);
	if(tick > 0.5){
		isReturning = true;
	}
	else if(tick < 0){
		isReturning = false;
	}
	float angle = PI * tick;
	int offset = 256 * tick;
	ring1->setPosition(originX + offset * cos(angle), originY + offset * sin(angle));
	angle += PI/2;
	ring2->setPosition(originX + offset * cos(angle), originY + offset * sin(angle));
	angle += PI/2;
	ring3->setPosition(originX + offset * cos(angle), originY + offset * sin(angle));
	angle += PI/2;
	ring4->setPosition(originX + offset * cos(angle), originY + offset * sin(angle));
}