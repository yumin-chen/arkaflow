#ifndef __BASE_SCENE_H__
#define __BASE_SCENE_H__

#include "EngineHelper.h"

class BaseScene : public cocos2d::LayerColor
{
public:
    virtual bool init(int backgroundColor);  
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event);
	static BaseScene* getCurrentScene();
	void setTouchEmitterEnabled(bool);
	void putEmitter(cocos2d::Vec2 pos);
	void putEmitter2(cocos2d::Vec2 pos);
	size_t addTouchEvents(TouchEventsFunc touchEvent);
	/*
	void removeTouchEvents(size_t index);
	*/
#ifndef NDEBUG //if DEBUG
	static void debugPrint(std::string);
#endif
private:
	int m_emitterCreated;
	int m_emitterReleased;
	int m_emitterStopped;
	bool m_touchEmitter;
	std::vector<TouchEventsFunc> _touchEvents;

};

#endif // __BASE_SCENE_H__
