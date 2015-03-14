#ifndef __SETTINGS_SCENE_H__
#define __SETTINGS_SCENE_H__

#include "BaseScene.h"
#include "./UI/BallButton.h"
#include "./UI/BallSlider.h"

class S_Settings : public BaseScene
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

	BallSlider* m_sliderMusic;
	BallSlider* m_sliderSound;

	cocos2d::Label* m_lbMusicVolumeValue;
	cocos2d::Label* m_lbSoundVolumeValue;
};

#endif // __SETTINGS_SCENE_H__
