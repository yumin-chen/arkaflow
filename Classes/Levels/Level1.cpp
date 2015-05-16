#include "stdafx.h"
#include "Level1.h"
#include "../Element/Ring.h"
#include "../Element/Target.h"
#include "../Element/Triangle.h"
#include "../Scene/MainGameScene.h"

USING_NS_CC;

bool Level1::init()
{
	if ( !BaseLevel::init() )
	{
		return false;
	}

	restart();
	S_MainGame::printString(S("Draw a line down here to fly the ball", "滑动手指画条直线来弹飞圈圈吧~"));
	return true;
}

void Level1::restart(){
	BaseLevel::restart();

	#define MOVE_BY_X (192 + 32 - 16)

	auto r1 = Ring::create();
	r1->setPosition(E::originX - 128, E::originY + 192 + 12);
	r1->setScale(0.4);
	r1->initBody();
	this->addChild(r1);
	r1->runAction(RepeatForever::create(Sequence::create(MoveBy::create(0.5f, Vec2(MOVE_BY_X, 0)), DelayTime::create(1.0f), MoveBy::create(0.5f, Vec2(-MOVE_BY_X, 0)), nullptr)));

	auto r2 = Ring::create();
	r2->setPosition(E::originX + DESIGNED_WIDTH + 128, E::originY + 192 + 12);
	r2->setScale(0.4);
	r2->initBody();
	this->addChild(r2);
	r2->runAction(RepeatForever::create(Sequence::create(MoveBy::create(0.5f, Vec2(-MOVE_BY_X, 0)), DelayTime::create(1.0f),MoveBy::create(0.5f, Vec2(MOVE_BY_X, 0)), nullptr)));

	auto t1 = Target::create();
	t1->setPosition(E::originX + DESIGNED_WIDTH / 2, E::originY + 480);
	t1->initBody();
	t1->playAnim(1);
	this->addChild(t1);

	auto t2 = Target::create();
	t2->setPosition(E::originX + DESIGNED_WIDTH / 2 - 128, E::originY + 480 - 16);
	t2->setRotation(30);
	t2->initBody();
	t2->playAnim(1);
	this->addChild(t2);

	auto t3 = Target::create();
	t3->setPosition(E::originX + DESIGNED_WIDTH / 2 + 128, E::originY + 480 - 16);
	t3->setRotation(-30);
	t3->initBody();
	t3->playAnim(1);
	this->addChild(t3);

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

void Level1::update(float dt){
}