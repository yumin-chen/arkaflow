#include "stdafx.h"
#include "Level21.h"
#include "Element/Ring.h"
#include "Element/Target.h"
#include "Element/Triangle.h"
#include "Element/Block.h"
#include "Element/Diamond.h"

USING_NS_CC;

bool Level21::init()
{
	if ( !BaseLevel::init() )
	{
		return false;
	}

	restart();

	return true;
}

void Level21::restart(){
	BaseLevel::restart();
#define MOVE_X_____ 64
	auto t = Target::create();
	t->setPosition(E::originX + DESIGNED_WIDTH / 2 , E::originY + 480);
	t->setRotation(180);
	t->initBody();
	t->playAnim(1);
	this->addChild(t);
	
	auto t2 = Target::create();
	t2->setPosition(E::originX + DESIGNED_WIDTH / 2 - 128, E::originY + 192 - 24);
	t2->setRotation(180);
	t2->initBody();
	t2->playAnim(1);
	this->addChild(t2);

	auto t3 = Target::create();
	t3->setPosition(E::originX + DESIGNED_WIDTH / 2 + 128, E::originY + 192 - 24);
	t3->setRotation(180);
	t3->initBody();
	t3->playAnim(1);
	this->addChild(t3);

	#define MOVE_BY_X 64
	auto b1 = Block::create(128, 32);
	b1->setPosition(E::originX + (DESIGNED_WIDTH - 128) / 2, E::originY + 400);
	b1->initBody();
	this->addChild(b1);
	auto b12 = Block::create(128, 24, E::P.C800);
	b12->setPosition(E::originX + (DESIGNED_WIDTH - 128) / 2, E::originY + 400 - 16);
	b12->initBody();
	b12->runAction(RepeatForever::create(Sequence::create(MoveBy::create(0.5f, Vec2(MOVE_BY_X/2, 0)), MoveBy::create(1.0f, Vec2(-MOVE_BY_X, 0)), MoveBy::create(0.5f, Vec2(MOVE_BY_X/2, 0)), nullptr)));
	b12->runAction(RepeatForever::create(Sequence::create(TintTo::create(1.0f, C3B(E::P.C400)), TintTo::create(1.0f, C3B(E::P.C800)), nullptr)));
	this->addChild(b12);

#define ___X__OFFSET (-128)

	auto ring0 = Ring::create();
	ring0->setScale(0.15f);
	ring0->setPosition(E::originX + DESIGNED_WIDTH / 2 + ___X__OFFSET, E::originY + 192 - 16);
	ring0->initBody();
	addChild(ring0);
	ring0->runAction(RepeatForever::create(Sequence::create(ScaleTo::create(0.8f, 0.22f), ScaleTo::create(0.8f, 0.0f), nullptr)));

	ring1 = Ring::create();
	ring1->setScale(0.15f);
	ring1->setPosition(E::originX + DESIGNED_WIDTH / 2 + ___X__OFFSET, E::originY + 192 - 16);
	ring1->initBody();
	addChild(ring1);
	ring1->runAction(RepeatForever::create(Sequence::create(ScaleTo::create(0.8f, 0.15f), ScaleTo::create(0.8f, 0.0f), nullptr)));

	ring2 = Ring::create();
	ring2->setScale(0.15f);
	ring2->setPosition(E::originX + DESIGNED_WIDTH / 2 + ___X__OFFSET, E::originY + 192 - 16);
	ring2->initBody();
	addChild(ring2);
	ring2->runAction(RepeatForever::create(Sequence::create(ScaleTo::create(0.8f, 0.15f), ScaleTo::create(0.8f, 0.0f), nullptr)));

	ring3 = Ring::create();
	ring3->setScale(0.15f);
	ring3->setPosition(E::originX + DESIGNED_WIDTH / 2 + ___X__OFFSET, E::originY + 192 - 16);
	ring3->initBody();
	addChild(ring3);
	ring3->runAction(RepeatForever::create(Sequence::create(ScaleTo::create(0.8f, 0.15f), ScaleTo::create(0.8f, 0.0f), nullptr)));

	ring4 = Ring::create();
	ring4->setScale(0.15f);
	ring4->setPosition(E::originX + DESIGNED_WIDTH / 2 + ___X__OFFSET, E::originY + 256 - 16);
	ring4->initBody();
	addChild(ring4);
	ring4->runAction(RepeatForever::create(Sequence::create(ScaleTo::create(0.8f, 0.15f), ScaleTo::create(0.8f, 0.0f), nullptr)));

	auto ring20 = Ring::create();
	ring20->setScale(0.15f);
	ring20->setPosition(E::originX + DESIGNED_WIDTH / 2 - ___X__OFFSET, E::originY + 192 - 16);
	ring20->initBody();
	addChild(ring20);
	ring20->runAction(RepeatForever::create(Sequence::create(ScaleTo::create(0.8f, 0.22f), ScaleTo::create(0.8f, 0.0f), nullptr)));

	ring21 = Ring::create();
	ring21->setScale(0.15f);
	ring21->setPosition(E::originX + DESIGNED_WIDTH / 2 - ___X__OFFSET, E::originY + 192 - 16);
	ring21->initBody();
	addChild(ring21);
	ring21->runAction(RepeatForever::create(Sequence::create(ScaleTo::create(0.8f, 0.15f), ScaleTo::create(0.8f, 0.0f), nullptr)));

	ring22 = Ring::create();
	ring22->setScale(0.15f);
	ring22->setPosition(E::originX + DESIGNED_WIDTH / 2 - ___X__OFFSET, E::originY + 192 - 16);
	ring22->initBody();
	addChild(ring22);
	ring22->runAction(RepeatForever::create(Sequence::create(ScaleTo::create(0.8f, 0.15f), ScaleTo::create(0.8f, 0.0f), nullptr)));

	ring23 = Ring::create();
	ring23->setScale(0.15f);
	ring23->setPosition(E::originX + DESIGNED_WIDTH / 2 - ___X__OFFSET, E::originY + 192 - 16);
	ring23->initBody();
	addChild(ring23);
	ring23->runAction(RepeatForever::create(Sequence::create(ScaleTo::create(0.8f, 0.15f), ScaleTo::create(0.8f, 0.0f), nullptr)));

	ring24 = Ring::create();
	ring24->setScale(0.15f);
	ring24->setPosition(E::originX + DESIGNED_WIDTH / 2 - ___X__OFFSET, E::originY + 256 - 16);
	ring24->initBody();
	addChild(ring24);
	ring24->runAction(RepeatForever::create(Sequence::create(ScaleTo::create(0.8f, 0.15f), ScaleTo::create(0.8f, 0.0f), nullptr)));

	auto diamond1 = Diamond::create();
	diamond1->setScale(1.0f);
	diamond1->setRotation(33);
	diamond1->setPosition(E::originX - 128, E::originY + 256 + 96);
	diamond1->initBody();
	this->addChild(diamond1);

	auto diamond2 = Diamond::create();
	diamond2->setScale(1.0f);
	diamond2->setRotation(-33);
	diamond2->setPosition(E::originX + DESIGNED_WIDTH + 128, E::originY + 256 + 96);
	diamond2->initBody();
	this->addChild(diamond2);

}

void Level21::update(float dt){
	static float tick = 0;
	static bool isReturning = false;
	tick += dt * - (int(isReturning) * 2 - 1);
	if(tick > 0.8f){
		isReturning = true;
	}
	else if(tick < -0.8f){
		isReturning = false;
	}
	float angle = PI * tick;
	int offset = (128 + 32) * tick;
	float originX = E::originX + DESIGNED_WIDTH / 2 + ___X__OFFSET;
	float originY = E::originY + 192 - 16;
	ring1->setPosition(originX + offset * cos(angle), originY + offset * sin(angle));
	angle += PI/2;
	ring2->setPosition(originX + offset * cos(angle), originY + offset * sin(angle));
	angle += PI/2;
	ring3->setPosition(originX + offset * cos(angle), originY + offset * sin(angle));
	angle += PI/2;
	ring4->setPosition(originX + offset * cos(angle), originY + offset * sin(angle));

	
	originX = E::originX + DESIGNED_WIDTH / 2 - ___X__OFFSET;
	originY = E::originY + 192 - 16;
	ring21->setPosition(originX + offset * sin(angle), originY + offset * cos(angle));
	angle += PI/2;
	ring22->setPosition(originX + offset * sin(angle), originY + offset * cos(angle));
	angle += PI/2;
	ring23->setPosition(originX + offset * sin(angle), originY + offset * cos(angle));
	angle += PI/2;
	ring24->setPosition(originX + offset * sin(angle), originY + offset * cos(angle));
}