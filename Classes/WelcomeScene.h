#ifndef __WELCOME_SCENE_H__
#define __WELCOME_SCENE_H__

#include "EngineHelper.h"

// these are tags for elements in this scene
#define TAG_NEW_GAME		25
#define TAG_BACKGROUND		27
#define TAG_NEW_GAME_BG		28
#define	TAG_MENU			29
#define TAG_TITLE			30

class Welcome : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();  

	// main loop that's called every frame
	virtual void update(float dt);
    
    void menuCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(Welcome);
private:
	long m_tick;
	bool m_bClose;
};

#endif // __WELCOME_SCENE_H__
