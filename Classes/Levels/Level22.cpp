#include "stdafx.h"
#include "Level22.h"
#include "../Element/Ring.h"
#include "../Element/Target.h"
#include "../Element/Triangle.h"
#include "../Element/Brick.h"
#include "../Element/Diamond.h"

#include "../Scene/MainGameScene.h"

USING_NS_CC;

bool Level22::init()
{
	if ( !BaseLevel::init() )
	{
		return false;
	}

	restart();

	return true;
}

void Level22::restart(){
	BaseLevel::restart();

	auto t = Target::create();
	t->setPosition(E::originX + DESIGNED_WIDTH / 2 , E::originY + 440);
	t->setRotation(180);
	t->initBody();
	t->playAnim(1);
	t->enableArtificialIntelligence();
	this->addChild(t);

	auto d = Diamond::create();
	d->setScale(0.6f);
	d->setRotation(90);
	d->setPosition(E::originX + DESIGNED_WIDTH / 2 + 96, E::originY + 320);
	d->initBody();
	this->addChild(d);

	auto diamond1 = Diamond::create();
	diamond1->setScale(0.88f);
	diamond1->setRotation(25);
	diamond1->setPosition(E::originX - 128 - 32, E::originY + 256 + 64);
	diamond1->initBody();
	this->addChild(diamond1);

	auto diamond2 = Diamond::create();
	diamond2->setScale(0.88f);
	diamond2->setRotation(-25);
	diamond2->setPosition(E::originX + DESIGNED_WIDTH + 128 + 32, E::originY + 256 + 64);
	diamond2->initBody();
	this->addChild(diamond2);

}

void Level22::update(float dt){
	
}