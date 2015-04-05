#include "stdafx.h"
#include "Level17.h"
#include "Element/Ring.h"
#include "Element/Target.h"
#include "Element/Diamond.h"
#include "Element/Block.h"

USING_NS_CC;

bool Level17::init()
{
	if ( !BaseLevel::init() )
	{
		return false;
	}

	restart();

	return true;
}

void Level17::restart(){
	BaseLevel::restart();

	#define MOVE_BY_Y (128+32)

	auto t = Target::create();
	t->setPosition(E::originX + DESIGNED_WIDTH / 2, E::originY + 440);
	t->setRotation(180);
	t->initBody();
	this->addChild(t);



	auto ring1 = Ring::create();
	ring1->setPosition(E::originX + DESIGNED_WIDTH / 2 - 128, E::originY + 320 - 128);
	ring1->setScale(0.12);
	ring1->initBody();
	this->addChild(ring1);

	auto ring2 = Ring::create();
	ring2->setPosition(E::originX + DESIGNED_WIDTH / 2 + 128, E::originY + 320 - 128);
	ring2->setScale(0.12);
	ring2->initBody();
	this->addChild(ring2);

	auto ring3 = Ring::create();
	ring3->setPosition(E::originX + DESIGNED_WIDTH / 2, E::originY + 320);
	ring3->setScale(0.12);
	ring3->initBody();
	this->addChild(ring3);

	auto ring4 = Ring::create();
	ring4->setPosition(E::originX + DESIGNED_WIDTH / 2, E::originY + 320 - 256);
	ring4->setScale(0.12);
	ring4->initBody();
	this->addChild(ring4);

	auto ring5 = Ring::create();
	ring5->setPosition(E::originX + DESIGNED_WIDTH / 2 - 128, E::originY + 320 + 128);
	ring5->setScale(0.12);
	ring5->initBody();
	this->addChild(ring5);

	auto ring6 = Ring::create();
	ring6->setPosition(E::originX + DESIGNED_WIDTH / 2 + 128, E::originY + 320 + 128);
	ring6->setScale(0.12);
	ring6->initBody();
	this->addChild(ring6);

	auto diamond1 = Diamond::create();
	diamond1->setScale(0.8f);
	diamond1->setRotation(35);
	diamond1->setPosition(E::originX - 128, E::originY + 256 + 96);
	diamond1->initBody();
	this->addChild(diamond1);

	auto diamond2 = Diamond::create();
	diamond2->setScale(0.8f);
	diamond2->setRotation(-35);
	diamond2->setPosition(E::originX + DESIGNED_WIDTH + 128, E::originY + 256 + 96);
	diamond2->initBody();
	this->addChild(diamond2);

}

void Level17::update(float dt){
}