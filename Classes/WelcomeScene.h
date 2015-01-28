#ifndef __WELCOME_SCENE_H__
#define __WELCOME_SCENE_H__

#include "EngineHelper.h"

class S_Welcome : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();  

	// main loop that's called every frame
	virtual void update(float dt);
    
    void menuCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(S_Welcome);
private:
	long m_tick;
	int m_bClose;
};

#endif // __WELCOME_SCENE_H__
