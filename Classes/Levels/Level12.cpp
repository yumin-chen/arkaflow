#include "stdafx.h"
#include "Level12.h"
#include "Element/Ring.h"
#include "Element/Target.h"
#include "Element/Triangle.h"

USING_NS_CC;

bool Level12::init()
{
	if ( !BaseLevel::init() )
	{
		return false;
	}

	restart();

	return true;
}

void Level12::restart(){
	BaseLevel::restart();

	auto r1 = Ring::create();
	r1->setPosition(E::originX + DESIGNED_WIDTH / 2, E::originY + 400);
	r1->setScale(0.2);
	r1->initBody();
	this->addChild(r1);
	r1->runAction(RepeatForever::create(Sequence::create(ScaleBy::create(0.4f, 2.0f), ScaleBy::create(0.4f, 0.5f), nullptr)));
	
	
#define ___MOVE_BY_X 96

	auto t2 = Target::create();
	t2->setPosition(E::originX + DESIGNED_WIDTH / 2 - 96, E::originY + 128);
	t2->setRotation(30);
	t2->initBody();
	t2->playAnim(1);
	this->addChild(t2);
	t2->initProtector();
	t2->runAction(RepeatForever::create(Sequence::create(MoveBy::create(1.0f, Vec2(-___MOVE_BY_X, 0)), MoveBy::create(1.0f, Vec2(___MOVE_BY_X, 0)), nullptr)));


	auto t3 = Target::create();
	t3->setPosition(E::originX + DESIGNED_WIDTH / 2 + 96, E::originY + 128);
	t3->setRotation(-30);
	t3->initBody();
	t3->playAnim(1);
	this->addChild(t3);
	t3->initProtector();
	t3->runAction(RepeatForever::create(Sequence::create(MoveBy::create(1.0f, Vec2(___MOVE_BY_X, 0)), MoveBy::create(1.0f, Vec2(-___MOVE_BY_X, 0)), nullptr)));


	
	auto triangle = Triangle::create();
	triangle->setScale(0.5f);
	triangle->setRotation(-45);
	triangle->setPosition(E::originX - 96, E::originY + 320);
	triangle->initBody();
	this->addChild(triangle);

	auto triangle2 = Triangle::create();
	triangle2->setScale(0.5f);
	triangle2->setRotation(45);
	triangle2->setPosition(E::originX + DESIGNED_WIDTH + 96, E::originY + 320);
	triangle2->initBody();
	this->addChild(triangle2);


}

void Level12::update(float dt){
}