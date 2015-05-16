#include "stdafx.h"
#include "Level24.h"
#include "../Element/Ring.h"
#include "../Element/Target.h"
#include "../Element/Diamond.h"
#include "../Element/Block.h"

USING_NS_CC;

bool Level24::init()
{
	if ( !BaseLevel::init() )
	{
		return false;
	}

	restart();

	return true;
}

void Level24::restart(){
	BaseLevel::restart();

	#define Y__OFFSET -64

	auto t = Target::create();
	t->setPosition(E::originX + DESIGNED_WIDTH / 2, E::originY + 320 + Y__OFFSET);
	t->setRotation(180);
	t->initBody();
	this->addChild(t);
	t->playAnim(1);

	auto t2 = Target::create();
	t2->setPosition(E::originX + DESIGNED_WIDTH / 2 - 128 - 32, E::originY + 320 + 160 + 48 + Y__OFFSET);
	t2->initBody();
	this->addChild(t2);
	t2->playAnim(1);

	auto t3 = Target::create();
	t3->setPosition(E::originX + DESIGNED_WIDTH / 2 + 128 + 32, E::originY + 320 + 160 + 48 + Y__OFFSET);
	t3->initBody();
	this->addChild(t3);
	t3->playAnim(1);

	auto ring1 = Ring::create();
	ring1->setPosition(E::originX + DESIGNED_WIDTH / 2 - 64, E::originY + 320 - 80 + Y__OFFSET);
	ring1->setScale(0.1);
	ring1->initBody();
	this->addChild(ring1);

	auto ring2 = Ring::create();
	ring2->setPosition(E::originX + DESIGNED_WIDTH / 2 + 64, E::originY + 320 - 80 + Y__OFFSET);
	ring2->setScale(0.1);
	ring2->initBody();
	this->addChild(ring2);

	auto ring3 = Ring::create();
	ring3->setPosition(E::originX + DESIGNED_WIDTH / 2, E::originY + 320 + 160 + 32 + Y__OFFSET);
	ring3->setScale(0.1);
	ring3->initBody();
	this->addChild(ring3);

	auto ring4 = Ring::create();
	ring4->setPosition(E::originX + DESIGNED_WIDTH / 2, E::originY + 320 - 160 + Y__OFFSET);
	ring4->setScale(0.1);
	ring4->initBody();
	this->addChild(ring4);

	auto ring5 = Ring::create();
	ring5->setPosition(E::originX + DESIGNED_WIDTH / 2 - 64, E::originY + 320 + 80 + 64 + Y__OFFSET);
	ring5->setScale(0.1);
	ring5->initBody();
	this->addChild(ring5);

	auto ring6 = Ring::create();
	ring6->setPosition(E::originX + DESIGNED_WIDTH / 2 + 64, E::originY + 320 + 80 + 64 + Y__OFFSET);
	ring6->setScale(0.1);
	ring6->initBody();
	this->addChild(ring6);

	auto ring7 = Ring::create();
	ring7->setPosition(E::originX + DESIGNED_WIDTH / 2 - 128, E::originY + 320 + Y__OFFSET);
	ring7->setScale(0.1);
	ring7->initBody();
	this->addChild(ring7);

	auto ring8 = Ring::create();
	ring8->setPosition(E::originX + DESIGNED_WIDTH / 2 + 128, E::originY + 320 + Y__OFFSET);
	ring8->setScale(0.1);
	ring8->initBody();
	this->addChild(ring8);

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

void Level24::update(float dt){
}