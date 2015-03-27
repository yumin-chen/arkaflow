#include "stdafx.h"
#include "Level6.h"
#include "Element/Triangle.h"
#include "Element/Target.h"
#include "Element/Block.h"
#include "Element/Diamond.h"

USING_NS_CC;

bool Level6::init()
{
	if ( !BaseLevel::init() )
	{
		return false;
	}

	restart();

	return true;
}

void Level6::restart(){
	BaseLevel::restart();

	auto t = Target::create();
	t->setPosition(E::originX + DESIGNED_WIDTH / 2  - 128, E::originY + 440);
	t->initBody();
	this->addChild(t);
	t->playAnim(0);

	auto t2 = Target::create();
	t2->setPosition(E::originX + DESIGNED_WIDTH / 2  + 128, E::originY + 440);
	t2->initBody();
	this->addChild(t2);
	t2->playAnim(0);

#define ___MOVE_BY_X 128
	auto diamond1 = Diamond::create();
	diamond1->setScale(0.2f);
	diamond1->setRotation(90);
	diamond1->setPosition(E::originX + DESIGNED_WIDTH / 2, E::originY + 64);
	diamond1->initBody();
	this->addChild(diamond1);
	diamond1->runAction(RepeatForever::create(Sequence::create(MoveBy::create(0.5f, Vec2(___MOVE_BY_X, 0)), MoveBy::create(1.0f, Vec2(-___MOVE_BY_X*2, 0)), MoveBy::create(0.5f, Vec2(___MOVE_BY_X, 0)), nullptr)));

	auto diamond2 = Diamond::create();
	diamond2->setScale(0.2f);
	diamond2->setRotation(90);
	diamond2->setPosition(E::originX + DESIGNED_WIDTH / 2, E::originY + 64 + 128);
	diamond2->initBody();
	this->addChild(diamond2);
	diamond2->runAction(RepeatForever::create(Sequence::create(MoveBy::create(0.5f, Vec2(-___MOVE_BY_X, 0)), MoveBy::create(1.0f, Vec2(+___MOVE_BY_X*2, 0)), MoveBy::create(0.5f, Vec2(-___MOVE_BY_X, 0)), nullptr)));

	auto diamond3 = Diamond::create();
	diamond3->setScale(0.2f);
	diamond3->setRotation(90);
	diamond3->setPosition(E::originX + DESIGNED_WIDTH / 2, E::originY + 64 + 128 * 2);
	diamond3->initBody();
	this->addChild(diamond3);
	diamond3->runAction(RepeatForever::create(Sequence::create(MoveBy::create(0.5f, Vec2(___MOVE_BY_X, 0)), MoveBy::create(1.0f, Vec2(-___MOVE_BY_X*2, 0)), MoveBy::create(0.5f, Vec2(___MOVE_BY_X, 0)), nullptr)));
	

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

void Level6::update(float dt){
}