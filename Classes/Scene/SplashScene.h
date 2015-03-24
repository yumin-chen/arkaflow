#ifndef __SPLASH_SCENE_H__
#define __SPLASH_SCENE_H__

#include "BaseScene.h"

class S_Splash : public BaseScene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();    
	void onKeyEvent(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event){};
    CREATE_FUNC(S_Splash);
private:
};

#endif // __SPLASH_SCENE_H__
