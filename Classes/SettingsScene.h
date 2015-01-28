#ifndef __SETTINGS_SCENE_H__
#define __SETTINGS_SCENE_H__

#include "EngineHelper.h"

class S_Settings : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();  
    
    void update( float dt );

	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);

	void menuCallback(cocos2d::Ref* pSender);
    
    CREATE_FUNC(S_Settings);

private:

	long m_tick;
	bool m_bClose;
	int m_tempColorAccent;
	int pltNormalColors[16], pltselectedColors[16];
};

#endif // __SETTINGS_SCENE_H__
