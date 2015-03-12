#include "stdafx.h"
#include "BaseScene.h"

USING_NS_CC;

static BaseScene *s_CurrentScene = nullptr;

bool BaseScene::init(int backgroundColor)
{
	s_CurrentScene = this;
	if ( !LayerColor::initWithColor(C4B(backgroundColor)) )
	{
		return false;
	}

	this->setScale(E::scale);
	this->setContentSize(Size(E::visibleWidth, E::visibleHeight));
	this->setAnchorPoint(Vec2(0, 0));

	auto listener = cocos2d::EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(BaseScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(BaseScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(BaseScene::onTouchEnded, this);
	listener->onTouchCancelled = CC_CALLBACK_2(BaseScene::onTouchCancelled, this);

	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	return true;
}

bool BaseScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{   
	for (std::vector<TouchEventsFunc>::iterator it = _touchEvents.begin() ;it != _touchEvents.end(); ++it)
	{
		if(it->onTouchBegan(touch, event)){
			return true;
		}
	}
	return false;
}

void BaseScene::onTouchMoved(Touch* touch, Event* event){
	for (std::vector<TouchEventsFunc>::iterator it = _touchEvents.begin() ;it != _touchEvents.end(); ++it)
		it->onTouchMoved(touch, event);
}

void BaseScene::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event){
	for (std::vector<TouchEventsFunc>::iterator it = _touchEvents.begin() ;it != _touchEvents.end(); ++it)
		it->onTouchEnded(touch, event);
}

void BaseScene::onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event){
	for (std::vector<TouchEventsFunc>::iterator it = _touchEvents.begin() ;it != _touchEvents.end(); ++it)
		it->onTouchCancelled(touch, event);
}

BaseScene* BaseScene::getCurrentScene(){
	return s_CurrentScene;
}

void BaseScene::addTouchEvents(TouchEventsFunc touchEvent){
	_touchEvents.push_back(touchEvent);
};
