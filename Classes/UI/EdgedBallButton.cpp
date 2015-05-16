#include "stdafx.h"
#include "EngineHelper.h"
#include "../Scene/BaseScene.h"
#include "EdgedBallButton.h"

USING_NS_CC;

#define NORMAL 0
#define SELECTED 1

EdgedBallButton::EdgedBallButton() {
}

EdgedBallButton::~EdgedBallButton() {
}

EdgedBallButton* EdgedBallButton::create(const cocos2d::ccMenuCallback& callback)
{
	EdgedBallButton *sprite = new (std::nothrow) EdgedBallButton();
    if (sprite && sprite->initWithTexture(Director::getInstance()->getTextureCache()->addImage("ui/outlined_button_o.png")))
    {
        sprite->autorelease();
		sprite->m_state = NORMAL;
		sprite->initOpt();
		sprite->runAnimations();
		sprite->m_callback = callback;
		if(callback){
			sprite->m_isEnabled = true;
			sprite->addEvents();
		}
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

void EdgedBallButton::initOpt(){
	m_innerSprite = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->addImage("ui/outlined_button_i.png"));
	m_innerSprite->setAnchorPoint(Vec2(0, 0));
	addChild(m_innerSprite);

	m_innerSprite->setOpacity(0);
	this->setOpacity(0);
	updateColors();
}

void EdgedBallButton::addEvents()
{
	TouchEventsFunc listener;
	listener.onTouchBegan = CC_CALLBACK_2(EdgedBallButton::onTouchBegan, this);
	listener.onTouchMoved = CC_CALLBACK_2(EdgedBallButton::onTouchMoved, this);
	listener.onTouchEnded = CC_CALLBACK_2(EdgedBallButton::onTouchEnded, this);
	listener.onTouchCancelled = CC_CALLBACK_2(EdgedBallButton::onTouchCancelled, this);
	BaseScene::getCurrentScene()->addTouchEvents(listener);
}


void EdgedBallButton::setVisible(bool visibility){
	Sprite::setVisible(visibility);
	m_isEnabled = visibility;
}


void EdgedBallButton::updateColors(){
	if(m_state == NORMAL){
		setColor(C3B(E::P.C700));
		m_innerSprite->setColor(C3B(E::P.C50));
	}
	else{
		setColor(C3B(E::P.C700));
		m_innerSprite->setColor(C3B(E::P2.A100));
	}
}

void EdgedBallButton::runAnimations(){
	//this->runAction(ScaleBy::create(0.4f, 6.0f));
	this->runAction(FadeIn::create(0.8f));
	m_innerSprite->runAction(FadeIn::create(0.8f));
	//m_innerSprite->runAction(FadeIn::create(0.4f));
}


bool EdgedBallButton::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event){
	if(!m_isEnabled){
		return false;
	}

	cocos2d::Vec2 p = this->getParent()->convertTouchToNodeSpace(touch);
	cocos2d::Rect rect = this->getBoundingBox();

	if(rect.containsPoint(p) && this->m_state == NORMAL)
	{
		this->m_state = SELECTED;
		updateColors();
		return true; // event consumed
	}

	return false; // event past thru
};

void EdgedBallButton::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event){
};
		
void EdgedBallButton::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event){
	if(!m_isEnabled){
		return;
	}
	if(m_state == NORMAL){
		return;
	}
	
	m_state = NORMAL;
	updateColors();
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
};
	
void EdgedBallButton::onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event){
	this->m_state = NORMAL;
	updateColors();
};