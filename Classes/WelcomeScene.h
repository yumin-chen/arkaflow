#ifndef __WELCOME_SCENE_H__
#define __WELCOME_SCENE_H__

#include "EngineHelper.h"

#define GENERAL_WIDTH (visibleSize.width > visibleSize.height? visibleSize.height: visibleSize.width)
#define SCALE_MAIN (GENERAL_WIDTH/600)
#define MARGIN_WIDTH (0.05*visibleSize.width)
#define MARGIN_SCALE (MARGIN_WIDTH/128)

// these are tags for elements in this scene
#define TAG_STRIPE_LEFT 24
#define TAG_STRIPE_RIGHT 25
#define TAG_WHEEL 26

class Welcome : public cocos2d::LayerColor
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

	// main loop that's called every frame
	virtual void update(float dt);
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void menuNewGameCallback(cocos2d::Ref* pSender);
    void menuHowToPlayCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(Welcome);
};

#endif // __WELCOME_SCENE_H__
