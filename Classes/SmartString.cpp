#include "stdafx.h"
#include "SmartString.h"
#include "MainGameScene.h"
#include "EngineHelper.h"

using namespace cocos2d;

SmartString::SmartString() {
}

SmartString::~SmartString() {
}

SmartString* SmartString::create()
{
	SmartString* pSprite = new SmartString();
	if (pSprite->initWithFile("string_l.png"))
	{
		pSprite->autorelease();
		pSprite->initOpt();
		return pSprite;
	}


	CC_SAFE_DELETE(pSprite);
	return NULL;
}

void SmartString::initOpt(){
	this->setAnchorPoint(Vec2(0, 0.5));
	m_middle = Sprite::create("string_m.png");
	m_middle->setAnchorPoint(Vec2(0, 0));
	m_right = Sprite::create("string_r.png");
	m_right->setAnchorPoint(Vec2(0, 0));
	this->addChild(m_middle);
	this->addChild(m_right);
	this->setScale(0.1f);
	this->setVisible(false);
	setColors(E::C900);
	m_isGoing = false;
}

void SmartString::setColors(int color){
	this->setColor(C3B(color));
	m_middle->setColor(C3B(color));
	m_right->setColor(C3B(color));
}
void SmartString::setOpacity(GLubyte opacity){
	Sprite::setOpacity(opacity);
	m_middle->setOpacity(opacity);
	m_right->setOpacity(opacity);
}
		
void SmartString::setPosition(const Vec2& pos){
	Sprite::setPosition(Vec2(pos.x, pos.y));
	_updatePosition();
}
void SmartString::setPositionY(float y){
	Sprite::setPositionY(y);
	_updatePosition();
}
void SmartString::setStartingPoint(const Vec2& p){
	m_startingPoint = p/ E::scale;
	this->setWidth(0);
	this->setPosition(Vec2(m_startingPoint.x - getRadius(), m_startingPoint.y));
	this->setVisible(true);
	this->setOpacity(255);
	m_isGoing = false;
}
void SmartString::setEndingPoint(const Vec2& p){
	setWidth((p.x/ E::scale - m_startingPoint.x));
}
void SmartString::setWidth(int w){
	m_width = w;
	if(abs(m_width) < getMaxWidth() * 0.2){
		setColors(E::C900);
		m_speed = 5;
	}else if(abs(m_width) < getMaxWidth() * 0.4){
		setColors(E::C800);
		m_speed = 4;
	}else if(abs(m_width) < getMaxWidth() * 0.6){
		setColors(E::C700);
		m_speed = 3;
	}else if(abs(m_width) < getMaxWidth() * 0.7){
		setColors(E::C600);
		m_speed = 2;
	}else{
		setColors(E::C500);
		m_speed = 1;
	}
	if(m_width > getMaxWidth()){
		m_width = getMaxWidth();
	}
	if(m_width < - getMaxWidth()){
		m_width = - getMaxWidth();
	}
	if(m_width < 0){
		m_width = -m_width;
		this->setPositionX(m_startingPoint.x-m_width);
	}
	m_middle->setScaleX(m_width / this->getScale());
	_updatePosition();
}
void SmartString::_updatePosition(){
	m_middle->setPosition(Vec2(getContentSize().width, 0));
	m_right->setPosition(Vec2( (m_width  / this->getScale() + getContentSize().width), 0));
}
void SmartString::go(){
	m_tick = 0;
	m_isGoing = true;
}
#define ANI_MOVING 20.0f
#define ANI_OPACING 10.0f
void SmartString::_update(){
	if(m_isGoing){
		setPositionY(getPositionY() + m_speed * 4);
		m_tick++;
		if(m_tick > ANI_MOVING && m_tick <= ANI_MOVING + ANI_OPACING){
			this->setOpacity(255 - 255 * (m_tick-ANI_MOVING)/ANI_OPACING);
		}
		if(m_tick == ANI_MOVING + ANI_OPACING)
		{
			m_isGoing = false;
			this->setVisible(false);
		}
	}
}
float SmartString::getRadius(){
	return this->getContentSize().width * this->getScale();
}
float SmartString::getMaxWidth(){
	return getRadius() * 12;
}
int SmartString::checkCollision(const Vec2& p, float radius){
	if(!m_isGoing)
		return 0;
	Vec2 posNow = getPosition();
	posNow.x = posNow.x + getRadius();
#define STRING_SC	0.9140625f
#define WHEEL_SC	0.7265625f
radius*=WHEEL_SC;
float stRadius=getRadius()*STRING_SC;
	// left collision
	if(p.getDistance(posNow) <= radius + stRadius && p.x < posNow.x){
		//m_isGoing = false;
		return 1;
	}

	Vec2 endingPoint = Vec2(posNow.x + m_width, posNow.y);
	// right collision
	if(p.getDistance(endingPoint) <= radius + stRadius && p.x > endingPoint.x){
		//m_isGoing = false;
		return 2;
	}

	// up collision
	if(p.x >= posNow.x && p.x <= endingPoint.x && p.y > posNow.y && p.y - posNow.y < radius + stRadius){
		//m_isGoing = false;
		return 3;
	}

	return 0;
}
float SmartString::getSpeed(){
	return m_speed;
}
float SmartString::getWidth(){
	return m_width;
}
