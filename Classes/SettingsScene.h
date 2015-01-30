#ifndef __SETTINGS_SCENE_H__
#define __SETTINGS_SCENE_H__

#include "EngineHelper.h"
#include "BallButton.h"

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

	BallButton* m_OkNormal;
	BallButton* m_OkSelected;
	BallButton* m_CancelNormal;
	BallButton* m_CancelSelected;
};

#endif // __SETTINGS_SCENE_H__
