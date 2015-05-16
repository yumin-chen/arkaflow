#include "stdafx.h"
#include "EngineHelper.h"
#include "BallButton.h"
#include "../Scene/BaseScene.h"

#define NORMAL 0
#define SELECTED 1

BallButton::BallButton() {m_listenerId = -1;}

BallButton::~BallButton() {
}


BallButton* BallButton::create(const int normalColor, const int selectedColor, const cocos2d::ccMenuCallback& callback)
{
	BallButton *btn = new (std::nothrow) BallButton;
    if (btn && btn->initWithTexture(cocos2d::Director::getInstance()->getTextureCache()->addImage("ui/ball.png")))//btn->init("ball.png", "", "", TextureResType::LOCAL))
    {
        btn->autorelease();
		btn->m_normalColor = normalColor;
		btn->m_selectedColor = selectedColor;
		btn->m_callback = callback;
		btn->setColor(cocos2d::C3B(btn->m_normalColor));
		btn->m_state = NORMAL;
        return btn;
    }
    CC_SAFE_DELETE(btn);
    return nullptr;
}

void BallButton::onEnter(){
	Sprite::onEnter();
	if(m_listenerId != -1)
	{
		BaseScene::getCurrentScene()->removeTouchEvents(m_listenerId);
		m_listenerId = -1;
	}
	if(m_selectedColor != 0 || m_callback != nullptr){
		m_isEnabled = true;
		addEvents();
	}
}

void BallButton::onExit(){
	Sprite::onExit();
	if(m_listenerId != -1)
	{
		BaseScene::getCurrentScene()->removeTouchEvents(m_listenerId);
		m_listenerId = -1;
	}
}

void BallButton::addEvents()
{
	TouchEventsFunc listener;
	listener.onTouchBegan = CC_CALLBACK_2(BallButton::onTouchBegan, this);
	listener.onTouchMoved = CC_CALLBACK_2(BallButton::onTouchMoved, this);
	listener.onTouchEnded = CC_CALLBACK_2(BallButton::onTouchEnded, this);
	listener.onTouchCancelled = CC_CALLBACK_2(BallButton::onTouchCancelled, this);
	m_listenerId = BaseScene::getCurrentScene()->addTouchEvents(listener);
}

void BallButton::_updateColor(){
	if(this->m_state == NORMAL){
		this->setColor(cocos2d::C3B(this->m_normalColor));
	}
	else{
		this->setColor(cocos2d::C3B(this->m_selectedColor));
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
	cocos2d::Vec2 p = this->getParent()->convertTouchToNodeSpace(touch);
	cocos2d::Rect rect = this->getBoundingBox();

	if(rect.containsPoint(p) && this->m_state == NORMAL)
	{
		this->m_state = SELECTED;
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
	if(this->m_state == NORMAL){
		return;
	}
	this->m_state = NORMAL;
	_updateColor();
	if( m_callback )
	{
		cocos2d::Vec2 p = this->getParent()->convertTouchToNodeSpace(touch);
		cocos2d::Rect rect = this->getBoundingBox();
		if(rect.containsPoint(p) && this->m_state == NORMAL)
		{
			E::playEffect("da");
			m_callback(this);
		}
	}
}

void BallButton::onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event){
	this->m_state = NORMAL;
	_updateColor();
}
