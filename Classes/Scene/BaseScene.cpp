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
#ifndef NDEBUG
	Vec2 p = touch->getLocation() / E::scale;
	debugPrint("Began:" + stdp::to_string(p.x) + ", " + stdp::to_string(p.y));
#endif
	//cocos2d::MessageBox("clicked", "test");
	for (std::vector<TouchEventsFunc>::iterator it = _touchEvents.begin() ;it != _touchEvents.end(); ++it)
	{
		if(it->onTouchBegan && it->onTouchBegan(touch, event)){
			return true;
		}
	}
	return false;
}

void BaseScene::onTouchMoved(Touch* touch, Event* event){
#ifndef NDEBUG
	Vec2 p = touch->getLocation() / E::scale;
	debugPrint("Moved:" + stdp::to_string(p.x) + ", " + stdp::to_string(p.y));
#endif
	for (std::vector<TouchEventsFunc>::iterator it = _touchEvents.begin() ;it != _touchEvents.end(); ++it)
	{
		if(it->onTouchMoved){
			it->onTouchMoved(touch, event);
		}
	}
}

void BaseScene::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event){
#ifndef NDEBUG
	Vec2 p = touch->getLocation() / E::scale;
	debugPrint("Ended:" + stdp::to_string(p.x) + ", " + stdp::to_string(p.y));
#endif
	for (std::vector<TouchEventsFunc>::iterator it = _touchEvents.begin() ;it != _touchEvents.end(); ++it)
	{
		if(it->onTouchEnded){
			it->onTouchEnded(touch, event);
		}
	}
}

void BaseScene::onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event){
	for (std::vector<TouchEventsFunc>::iterator it = _touchEvents.begin() ;it != _touchEvents.end(); ++it)
	{
		if(it->onTouchCancelled){
			it->onTouchCancelled(touch, event);
		}
	}
}

BaseScene* BaseScene::getCurrentScene(){
	return s_CurrentScene;
}

size_t BaseScene::addTouchEvents(TouchEventsFunc touchEvent){
	_touchEvents.push_back(touchEvent);
	return _touchEvents.size() - 1;
};

/*
void BaseScene::removeTouchEvents(size_t index){
	_touchEvents.at(index).onTouchBegan = nullptr;
	_touchEvents.at(index).onTouchMoved = nullptr;
	_touchEvents.at(index).onTouchEnded = nullptr;
	_touchEvents.at(index).onTouchCancelled = nullptr;
};
*/


#ifndef NDEBUG //if DEBUG
void BaseScene::debugPrint(std::string output){
	static Label* label = nullptr;
	static BaseScene *thisScene = nullptr;
	if(label == nullptr || thisScene != this){
		label = Label::createWithSystemFont(output, "Arial", 24, 
			Size(E::visibleWidth, 48), TextHAlignment::LEFT, TextVAlignment::BOTTOM);
		label->setPosition(24, 24);
		label->setAnchorPoint(Vec2(0, 0));
		label->enableShadow(Color4B(0, 0, 0, 128), Size(1, -1));
		this->addChild(label, 10000);
		thisScene = this;
	}
	label->setString(output);
};
#endif