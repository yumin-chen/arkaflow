#include "stdafx.h"
#include "Level9.h"
#include "Element/Triangle.h"
#include "Element/Target.h"
#include "Element/Block.h"
#include "Element/Diamond.h"

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

	auto t = Target::create();
	t->setPosition(E::originX + DESIGNED_WIDTH / 2  - 128, E::originY + 400);
	t->initBody();
	this->addChild(t);
	t->playAnim(0);


	auto diamond1 = Diamond::create();
	diamond1->setScale(0.3f);
	diamond1->setRotation(90);
	diamond1->setPosition(E::originX + DESIGNED_WIDTH / 2, E::originY + 32);
	diamond1->initBody();
	this->addChild(diamond1);

	auto diamond2 = Diamond::create();
	diamond2->setScale(0.3f);
	diamond2->setRotation(-90);
	diamond2->setPosition(E::originX + DESIGNED_WIDTH / 2, E::originY + 32 + 192);
	diamond2->initBody();
	this->addChild(diamond2);

	auto diamond3 = Diamond::create();
	diamond3->setScale(0.3f);
	diamond3->setRotation(90);
	diamond3->setPosition(E::originX + DESIGNED_WIDTH / 2, E::originY + 32 + 192 * 2);
	diamond3->initBody();
	this->addChild(diamond3);
	

	auto triangle = Triangle::create();
	triangle->setScale(0.6f);
	triangle->setRotation(30);
	triangle->setPosition(E::originX - 256, E::originY + 256);
	triangle->initBody();
	this->addChild(triangle);

	auto triangle2 = Triangle::create();
	triangle2->setScale(0.6f);
	triangle2->setRotation(-30);
	triangle2->setPosition(E::originX + DESIGNED_WIDTH + 256, E::originY + 256);
	triangle2->initBody();
	this->addChild(triangle2);


}

void Level9::update(float dt){
}