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
	size_t addTouchEvents(TouchEventsFunc touchEvent);
	/*
	void removeTouchEvents(size_t index);
	*/
private:
	std::vector<TouchEventsFunc> _touchEvents;
#ifndef NDEBUG //if DEBUG
	void debugPrint(std::string);
#endif

};

#endif // __BASE_SCENE_H__
