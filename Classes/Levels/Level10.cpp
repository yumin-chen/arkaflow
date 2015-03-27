#include "stdafx.h"
#include "Level10.h"
#include "Element/Ring.h"
#include "Element/Target.h"
#include "Element/Triangle.h"

USING_NS_CC;

bool Level10::init()
{
	if ( !BaseLevel::init() )
	{
		return false;
	}

	restart();

	return true;
}

void Level10::restart(){
	BaseLevel::restart();

#define ___MOVE_BY_X 128

	auto t1 = Target::create();
	t1->setPosition(E::originX + DESIGNED_WIDTH / 2, E::originY + 440);
	t1->initBody();
	t1->playAnim(1);
	this->addChild(t1);
	t1->initProtector();
	t1->runAction(RepeatForever::create(Sequence::create(MoveBy::create(0.5f, Vec2(___MOVE_BY_X, 0)), MoveBy::create(1.0f, Vec2(-___MOVE_BY_X*2, 0)), MoveBy::create(0.5f, Vec2(___MOVE_BY_X, 0)), nullptr)));


	auto t2 = Target::create();
	t2->setPosition(E::originX + DESIGNED_WIDTH / 2, E::originY + 440 - 180);
	t2->initBody();
	t2->playAnim(1);
	this->addChild(t2);
	t2->initProtector();
	t2->runAction(RepeatForever::create(Sequence::create(MoveBy::create(0.5f, Vec2(-___MOVE_BY_X, 0)), MoveBy::create(1.0f, Vec2(+___MOVE_BY_X*2, 0)), MoveBy::create(0.5f, Vec2(-___MOVE_BY_X, 0)), nullptr)));

	auto t3 = Target::create();
	t3->setPosition(E::originX + DESIGNED_WIDTH / 2, E::originY + 440 - 180 * 2);
	t3->initBody();
	t3->playAnim(1);
	this->addChild(t3);
	t3->initProtector();
	t3->runAction(RepeatForever::create(Sequence::create(MoveBy::create(0.5f, Vec2(___MOVE_BY_X, 0)), MoveBy::create(1.0f, Vec2(-___MOVE_BY_X*2, 0)), MoveBy::create(0.5f, Vec2(___MOVE_BY_X, 0)), nullptr)));
	
	auto triangle = Triangle::create();
	triangle->setScale(0.5f);
	triangle->setRotation(-30);
	triangle->setPosition(E::originX - 128, E::originY + 320);
	triangle->initBody();
	this->addChild(triangle);

	auto triangle2 = Triangle::create();
	triangle2->setScale(0.5f);
	triangle2->setRotation(30);
	triangle2->setPosition(E::originX + DESIGNED_WIDTH + 128, E::originY + 320);
	triangle2->initBody();
	this->addChild(triangle2);


}

void Level10::update(float dt){
}
