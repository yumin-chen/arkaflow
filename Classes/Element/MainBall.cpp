#include "stdafx.h"
#include "MainBall.h"

MainBall::MainBall() {
}

MainBall::~MainBall() {
}

void MainBall::setPosition(float x, float y) {
	position.x = x;
	position.y = y;
	if(isReal)
		sprite->setPosition(x, y);
}

void MainBall::setPositionX(float x) {
	position.x = x;
	if(isReal)
		sprite->setPositionX(x);
}

void MainBall::setPositionY(float y) {
	position.y = y;
	if(isReal)
		sprite->setPositionY(y);
}

float MainBall::getRadius(){
	return sprite->getContentSize().width * sprite->getScale() /2;
}