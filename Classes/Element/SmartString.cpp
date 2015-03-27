#include "stdafx.h"
#include "SmartString.h"
#include "Scene/MainGameScene.h"
#include "EngineHelper.h"
#include "math.h"

USING_NS_CC;

SmartString::SmartString() {
}

SmartString::~SmartString() {
}

SmartString* SmartString::create()
{
	SmartString* pSprite = new SmartString();
	if (pSprite->initWithTexture(Director::getInstance()->getTextureCache()->addImage("ui/ball_outer.png"), Rect(0, 0, 128, 256)))
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
	m_pBody = nullptr;
	m_middle = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->addImage("ui/ball_outer.png"), Rect(128, 0, 1, 256));
	m_middle->setAnchorPoint(Vec2(0, 0));
	m_right = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->addImage("ui/ball_outer.png"), Rect(128, 0, 128, 256));
	m_right->setAnchorPoint(Vec2(0, 0));
	m_leftInner = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->addImage("ui/string_inner.png"), Rect(0, 0, 128, 256));
	m_middleInner = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->addImage("ui/string_inner.png"), Rect(128, 0, 1, 256));
	m_rightInner = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->addImage("ui/string_inner.png"), Rect(128, 0, 128, 256));
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
	this->setTag(TAG_PHY_STRING);
	setColors(E::P.C900);
	m_isGoing = false;
}

void SmartString::onContactWithBall(){
	detachBody();
	m_isGoing = false;
	animFadeOut();
	E::playEffect("da");
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
	m_leftInner->setOpacity(opacity);
	m_middleInner->setOpacity(opacity);
	m_rightInner->setOpacity(opacity);
}
		
void SmartString::setPosition(const Vec2& pos){
	Sprite::setPosition(Vec2(pos.x, pos.y));
	_updatePosition();
}
void SmartString::setPositionY(float y){
	Sprite::setPositionY(y);
	_updatePosition();
}

void SmartString::detachBody(){
	if(m_pBody != nullptr){
		m_pBody->removeFromWorld();
		m_pBody = nullptr;
		this->setPhysicsBody(nullptr);
	}
}

void SmartString::setStartingPoint(const Vec2& p){
	detachBody();
	stopAllActions();
	
	m_startingPoint = p;
	this->setWidth(0);
	this->setPosition(Vec2(m_startingPoint.x - getRadius(), m_startingPoint.y));
	this->setRotation(0);
	this->setVisible(true);
	this->setOpacity(255);
	m_isGoing = false;
}
void SmartString::setEndingPoint(const Vec2& p){
	setWidth(p.getDistance(m_startingPoint));
	if(m_startingPoint.x != p.x){
	float angle = - atan((m_startingPoint.y - p.y)/ (m_startingPoint.x - p.x)) /PI * 180;
	if(p.x < m_startingPoint.x){
		angle = - 90 - (90 - angle);
	}
	setRotation(angle);
	}
	this->setVisible(true);
	this->setOpacity(255);
}
void SmartString::setWidth(int w){
	m_width = w;
	if(abs(m_width) < getMaxWidth() * 0.2){
		setColors(E::P.C400);
	}else if(abs(m_width) < getMaxWidth() * 0.4){
		setColors(E::P.C300);
	}else if(abs(m_width) < getMaxWidth() * 0.6){
		setColors(E::P.C200);
	}else if(abs(m_width) < getMaxWidth() * 0.7){
		setColors(E::P.C100);
	}else{
		setColors(E::P.C50);
	}
	m_speed = 3 * getMaxWidth() / (abs(m_width) + 128);
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
	detachBody();
	float d = 192 * this->getScale();
	float w = m_width + d;
	m_pBody = PhysicsBody::createBox(Size(w, d), SMOOTH_MATERIAL);
	w-=d/4;
	w*= E::scale;

	m_pBody->setVelocity(Vec2(0, m_speed * SS_SPEEDRATIO * E::scale));
#define SS_FORCERATIO -500
	m_pBody->applyForce(Vec2(0, m_speed * SS_FORCERATIO * E::scale));
	m_pBody->setPositionOffset(Vec2((w) / 2 * cos(getRotation() * PI / 180) , - w / 2* sin(getRotation() * PI / 180)));
	m_pBody->setRotationEnable(false);
	m_pBody->setCollisionBitmask(0x0000000F);
	m_pBody->setContactTestBitmask(0x0000000F);

	this->setPhysicsBody(m_pBody);
	m_deltaDiff = 0;
	m_isGoing = true;
	this->setVisible(true);
}

#define MOVING_TIME 0.3f
void SmartString::update(float dt){
	if(m_isGoing){
		m_deltaDiff = m_deltaDiff + dt;
		if(m_deltaDiff > MOVING_TIME){
			m_isGoing = false;
			animFadeOut();
		}
	}
}

float SmartString::getRadius(){
	return getContentSize().width * getScale();
}

float SmartString::getMaxWidth(){
	return 192;
}

float SmartString::getSpeed(){
	return m_speed;
}
float SmartString::getWidth(){
	return m_width;
}

void SmartString::animFadeOut(){
	auto cbSetVisible = CallFunc::create([this](){setVisible(false); detachBody();});
	this->runAction(Sequence::create(FadeOut::create(0.2f), cbSetVisible, nullptr));
	m_leftInner->runAction(FadeOut::create(0.2f));
	m_middleInner->runAction(FadeOut::create(0.2f));
	m_rightInner->runAction(FadeOut::create(0.2f));
}
