#include "stdafx.h"
#include "BallButton.h"
#include "BaseScene.h"

#define NORMAL 0
#define SELECTED 1

BallButton::BallButton() {}

BallButton::~BallButton() {
	/*
	cocos2d::Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
	listener->release();
	listener = nullptr;
	*/
}

BallButton* BallButton::create(const int normalColor, const int selectedColor, const cocos2d::ccMenuCallback& callback)
{
	BallButton* pSprite = new BallButton();

	if (pSprite->initWithFile("ball.png"))
	{
		pSprite->autorelease();
		pSprite->normalColor = normalColor;
		pSprite->selectedColor = selectedColor;
		pSprite->m_callback = callback;
		pSprite->setColor(cocos2d::C3B(pSprite->normalColor));
		pSprite->state = NORMAL;
		if(selectedColor != 0 || callback != nullptr){
			pSprite->addEvents();
		}
		return pSprite;
	}

	CC_SAFE_DELETE(pSprite);
	return NULL;
}



void BallButton::addEvents()
{
	TouchEventsFunc listener;
	listener.onTouchBegan = CC_CALLBACK_2(BallButton::onTouchBegan, this);
	listener.onTouchMoved = CC_CALLBACK_2(BallButton::onTouchMoved, this);
	listener.onTouchEnded = CC_CALLBACK_2(BallButton::onTouchEnded, this);
	listener.onTouchCancelled = CC_CALLBACK_2(BallButton::onTouchCancelled, this);
	BaseScene::getCurrentScene()->addTouchEvents(listener);
}

void BallButton::_updateColor(){
	if(this->state == NORMAL){
		this->setColor(cocos2d::C3B(this->normalColor));
	}
	else{
		this->setColor(cocos2d::C3B(this->selectedColor));
	}
}

void BallButton::setVisible(bool visibility){
	Sprite::setVisible(visibility);
	m_isEnabled = visibility;
}

bool BallButton::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
	if(!m_isEnabled){
		return false;
	}
	cocos2d::Vec2 p = touch->getLocation() / E::scale;
	cocos2d::Rect rect = this->getBoundingBox();

	if(rect.containsPoint(p) && this->state == NORMAL)
	{
		this->state = SELECTED;
		E::playEffect("da");
		_updateColor();
		return true; // event consumed
	}

	return false; // event past thru
}

void BallButton::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event){
}

void BallButton::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event){
	if(!m_isEnabled){
		return;
	}
	if(this->state == NORMAL){
		return;
	}
	this->state = NORMAL;
	_updateColor();
	if( m_callback )
	{
		m_callback(this);
	}
}

void BallButton::onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event){
	this->state = NORMAL;
	_updateColor();
}