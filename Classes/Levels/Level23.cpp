#include "stdafx.h"
#include "Level23.h"
#include "../Element/Ring.h"
#include "../Element/Target.h"
#include "../Element/Triangle.h"
#include "../Element/Brick.h"
#include "../Element/Diamond.h"

#include "../Scene/MainGameScene.h"

USING_NS_CC;

bool Level23::init()
{
	if ( !BaseLevel::init() )
	{
		return false;
	}

	restart();

	return true;
}

void Level23::restart(){
	BaseLevel::restart();
	auto t = Target::create();
	t->setPosition(E::originX + DESIGNED_WIDTH / 2 , E::originY + 440);
	t->setRotation(180);
	t->initBody();
	t->playAnim(1);
	t->enableArtificialIntelligence();
	this->addChild(t);

	auto t2 = Target::create();
	t2->setPosition(E::originX + DESIGNED_WIDTH / 2 - 64 , E::originY + 380);
	t2->setRotation(180);
	t2->initBody();
	t2->playAnim(1);
	t2->enableArtificialIntelligence();
	this->addChild(t2);

	auto t3 = Target::create();
	t3->setPosition(E::originX + DESIGNED_WIDTH / 2 + 64 , E::originY + 380);
	t3->setRotation(180);
	t3->initBody();
	t3->playAnim(1);
	t3->enableArtificialIntelligence();
	this->addChild(t3);

	auto d = Diamond::create();
	d->setScale(0.3f);
	d->setRotation(90);
	d->setPosition(E::originX + DESIGNED_WIDTH / 2 , E::originY + 256);
	d->initBody();
	this->addChild(d);

	auto d1 = Diamond::create();
	d1->setScale(0.35f);
	d1->setRotation(-90);
	d1->setPosition(E::originX + DESIGNED_WIDTH / 2 - 192, E::originY + 96);
	d1->initBody();
	this->addChild(d1);

	auto d2 = Diamond::create();
	d2->setScale(0.35f);
	d2->setRotation(-90);
	d2->setPosition(E::originX + DESIGNED_WIDTH / 2 + 192, E::originY + 96);
	d2->initBody();
	this->addChild(d2);

auto triangle = Triangle::create();
	triangle->setScale(0.5f);
	triangle->setRotation(-90);
	triangle->setPosition(E::originX - 128, E::originY + 320);
	triangle->initBody();
	this->addChild(triangle);

	auto triangle2 = Triangle::create();
	triangle2->setScale(0.5f);
	triangle2->setRotation(90);
	triangle2->setPosition(E::originX + DESIGNED_WIDTH + 128, E::originY + 320);
	triangle2->initBody();
	this->addChild(triangle2);

}

void Level23::update(float dt){
	
}