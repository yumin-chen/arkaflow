#ifndef __WELCOME_SCENE_H__
#define __WELCOME_SCENE_H__

#include "BaseScene.h"

class S_Welcome : public BaseScene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();  
	virtual void update(float dt);    
    void menuCallback(cocos2d::Ref* pSender);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
    CREATE_FUNC(S_Welcome);
private:
	long m_tick;
	int m_bClose;
};

#endif // __WELCOME_SCENE_H__
