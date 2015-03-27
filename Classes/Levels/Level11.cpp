#include "stdafx.h"
#include "Level11.h"
#include "Element/Ring.h"
#include "Element/Target.h"
#include "Element/Triangle.h"
#include "Element/Block.h"
#include "Element/Diamond.h"

USING_NS_CC;

bool Level11::init()
{
	if ( !BaseLevel::init() )
	{
		return false;
	}

	restart();

	return true;
}

void Level11::restart(){
	BaseLevel::restart();

	auto t1 = Target::create();
	t1->setPosition(E::originX + DESIGNED_WIDTH / 2 - 96, E::originY + 480);
	t1->setRotation(180);
	t1->initBody();
	t1->playAnim(1);
	this->addChild(t1);

	auto t2 = Target::create();
	t2->setPosition(E::originX + DESIGNED_WIDTH / 2 + 96, E::originY + 480);
	t2->setRotation(180);
	t2->initBody();
	t2->playAnim(1);
	this->addChild(t2);

	diamond = Diamond::create();
	diamond->setScale(0.45);
	diamond->setPosition(E::originX + DESIGNED_WIDTH / 2, E::originY + 128 + 48);
	diamond->initBody();
	this->addChild(diamond);

	auto triangle = Triangle::create();
	triangle->setScale(0.2f);
	triangle->setRotation(180);
	triangle->setPosition(E::originX + DESIGNED_WIDTH / 2, E::originY + 440);
	triangle->initBody();
	this->addChild(triangle);

	auto triangle1 = Triangle::create();
	triangle1->setScale(0.5f);
	triangle1->setRotation(45);
	triangle1->setPosition(E::originX - 256 - 32, E::originY + 256);
	triangle1->initBody();
	this->addChild(triangle1);

	auto triangle2 = Triangle::create();
	triangle2->setScale(0.5f);
	triangle2->setRotation(-45);
	triangle2->setPosition(E::originX + DESIGNED_WIDTH + 256 + 32, E::originY + 256);
	triangle2->initBody();
	this->addChild(triangle2);
	
	angle = 0;
}

void Level11::update(float dt){
	angle += dt * 100;
	diamond->setRotation(angle);
	//diamond->updateBody();
}