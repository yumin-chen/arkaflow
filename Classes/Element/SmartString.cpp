#include "stdafx.h"
#include "SmartString.h"
#include "Scene/MainGameScene.h"
#include "EngineHelper.h"
#include "math.h"

using namespace cocos2d;

SmartString::SmartString() {
	isEnemy = false;
}

SmartString::~SmartString() {
}

SmartString* SmartString::create()
{
	SmartString* pSprite = new SmartString();
	if (pSprite->initWithFile("ball_outer.png", Rect(0, 0, 128, 256)))
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
	m_middle = Sprite::create("ball_outer.png", Rect(128, 0, 1, 256));
	m_middle->setAnchorPoint(Vec2(0, 0));
	m_right = Sprite::create("ball_outer.png", Rect(128, 0, 128, 256));
	m_right->setAnchorPoint(Vec2(0, 0));
	m_leftInner = Sprite::create("string_inner.png", Rect(0, 0, 128, 256));
	m_middleInner = Sprite::create("string_inner.png", Rect(128, 0, 1, 256));
	m_rightInner = Sprite::create("string_inner.png", Rect(128, 0, 128, 256));
	m_leftInner->setPosition(256/2 - getRadius()/2, 256/2);
	m_middleInner->setAnchorPoint(Vec2(0, 0));
	//m_middleInner->setPosition(256/2 - getRadius()/2, 256/2);
	m_rightInner->setPosition(256/2 - getRadius()/2, 256/2);
	this->addChild(m_middle);
	this->addChild(m_right);
	this->addChild(m_leftInner);
	m_middle->addChild(m_middleInner);
	m_right->addChild(m_rightInner);
	this->setScale(0.1f);
	this->setVisible(false);
	setColors(E::P.C900);
	m_isGoing = false;
}

void SmartString::setColors(int color){
	this->setColor(C3B(E::P.C900));
	m_middle->setColor(C3B(E::P.C900));
	m_right->setColor(C3B(E::P.C900));
	m_leftInner->setColor(C3B(color));
	m_middleInner->setColor(C3B(color));
	m_rightInner->setColor(C3B(color));
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
	m_startingPoint = p;
	this->setWidth(0);
	this->setPosition(Vec2(m_startingPoint.x - getRadius(), m_startingPoint.y));
	this->setVisible(true);
	this->setOpacity(255);
	m_isGoing = false;
}
void SmartString::setEndingPoint(const Vec2& p){
	setWidth((p.x - m_startingPoint.x));
}
void SmartString::setWidth(int w){
	m_width = w;
	if(abs(m_width) < getMaxWidth() * 0.2){
		setColors(E::P.C400);
		m_speed = 5;
	}else if(abs(m_width) < getMaxWidth() * 0.4){
		setColors(E::P.C300);
		m_speed = 4;
	}else if(abs(m_width) < getMaxWidth() * 0.6){
		setColors(E::P.C200);
		m_speed = 3;
	}else if(abs(m_width) < getMaxWidth() * 0.7){
		setColors(E::P.C100);
		m_speed = 2;
	}else{
		setColors(E::P.C50);
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
	this->setVisible(true);
}


#define ANI_OPACING 10.0f
void SmartString::_update(){
	if(m_isGoing){
		setPositionY(getPositionY() + m_speed * SS_SPEEDRATIO * (1 - int(isEnemy) * 2));
		m_tick++;
		if(m_tick > SS_ANI_MOVING && m_tick <= SS_ANI_MOVING + ANI_OPACING){
			this->setOpacity(255 - 255 * (m_tick-SS_ANI_MOVING)/ANI_OPACING);
		}
		if(m_tick == SS_ANI_MOVING + ANI_OPACING)
		{
			m_isGoing = false;
			this->setVisible(false);
		}
	}
}
float SmartString::getRadius(){
	return getContentSize().width * getScale();
}
float SmartString::getMaxWidth(){
	return getRadius() * 12;
}
int SmartString::checkCollision(MainBall *wheel){
	if(!m_isGoing || m_tick == 0)
		return 0;
	Vec2 p = wheel->position;
	float radius = wheel->getRadius();
	Vec2 posNow = getPosition();
	posNow.x = posNow.x + getRadius();

#define STRING_SC	0.75f

float stRadius=getRadius()*STRING_SC;
int ret = 0;
	// left collision
	int dif = radius + stRadius - p.getDistance(posNow);
	float radian = atan2(posNow.y - p.y, posNow.x - p.x);
	if(0 <= dif && p.x < posNow.x){
		wheel->setPosition(wheel->position.x + dif * sin(radian),
		wheel->position.y + dif * cos(radian));
		//m_isGoing = false;
		ret = 1;
	}

	Vec2 endingPoint = Vec2(posNow.x + m_width, posNow.y);
	dif = radius + stRadius - p.getDistance(endingPoint);
	radian = atan2(endingPoint.y - p.y, endingPoint.x - p.x);
	// right collision
	if(0 <= dif && p.x > endingPoint.x){
		wheel->setPosition(wheel->position.x - dif * sin(radian),
		wheel->position.y - dif * cos(radian));
		//m_isGoing = false;
		ret = 2;
	}


	Vec2 midPoint = Vec2(posNow.x + m_width/2, posNow.y);
	// up collision
	if(p.x >= posNow.x && p.x <= endingPoint.x && p.y > posNow.y && p.y - posNow.y < radius + stRadius && !isEnemy){
		//m_isGoing = false;
		wheel->setPositionY(posNow.y + radius + stRadius);
		radian = atan2(midPoint.y - wheel->position.y, midPoint.x - wheel->position.x);
		ret = 3;
	}

	// down collision
	if(p.x >= posNow.x && p.x <= endingPoint.x && p.y < posNow.y && posNow.y - p.y < radius + stRadius && isEnemy){
		//m_isGoing = false;
		wheel->setPositionY(posNow.y - radius - stRadius);
		radian = atan2(midPoint.y - wheel->position.y, midPoint.x - wheel->position.x);
		ret = 4;
	}

	

	if(ret != 0){
		//wheel->angle = radian;
//		/*
		wheel->angle = 0;
		if(getWidth()>1)
		{
			wheel->angle =(wheel->position.x - 
				(m_startingPoint.x+getRadius()+getWidth()/2)
				);
			wheel->angle = wheel->angle < 0? wheel->angle + radius + stRadius: wheel->angle - radius - stRadius;
			wheel->angle = wheel->angle	/getWidth() * 90.0f *PI/180.0f;
		}
//		*/
		//MessageBox(std::to_string( angleMinus90(wheel->angle)*180/PI).c_str(), "s");
		wheel->rotatedAngle = wheel->angle;
		wheel->speed =wheel->speed*0.5+getSpeed();

		
		
//		/*
		if(isEnemy && ret != 3 && angleMinus90(wheel->angle) > PI){
			wheel->angle = anglePlus90(-angleMinus90(wheel->angle));
			wheel->rotatedAngle = wheel->angle;
		}

		if(!isEnemy && ret != 4 && angleMinus90(wheel->angle) < PI){
			wheel->angle = anglePlus90(-angleMinus90(wheel->angle));
			wheel->rotatedAngle = wheel->angle;
		}
//		*/

		/**
		if(ret == 3 && angleMinus90(wheel->angle) < PI){
			wheel->angle = anglePlus90(-angleMinus90(wheel->angle));
			wheel->rotatedAngle = wheel->angle;
		}
		**/

		if(wheel->isReal){
			m_isGoing = false;
			//this->setVisible(false);
		}
	}

	return ret;
}
float SmartString::getSpeed(){
	return m_speed;
}
float SmartString::getWidth(){
	return m_width;
}
