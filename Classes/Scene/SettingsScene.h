#ifndef __SETTINGS_SCENE_H__
#define __SETTINGS_SCENE_H__

#include "BaseScene.h"
#include "UI/BallButton.h"
#include "UI/EdgedBallButton.h"
#include "UI/BallSlider.h"
#include "UI/TitleBar.h"

class S_Settings : public BaseScene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();  
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
	void menuCallback(cocos2d::Ref* pSender);
    CREATE_FUNC(S_Settings);

private:
	void _ok();
	void _cancel();
	bool m_bClose;
	int m_tempColorAccent;
	void runAnimations(bool);

	BallButton* m_OkNormal;
	BallButton* m_OkSelected;
	BallButton* m_CancelNormal;
	BallButton* m_CancelSelected;
	BallButton* m_okBtnBg;
	BallButton* m_cancelBg;
	BallButton* m_btmBg;
	TitleBar* m_titleBar;

	EdgedBallButton* m_spMusicBtn;
	EdgedBallButton* m_spSoundBtn;

	cocos2d::Sprite* m_spMusicIcon;
	cocos2d::Sprite* m_spSoundIcon;

	cocos2d::Menu* m_menu;
	cocos2d::Sprite* m_shadow;
	cocos2d::LayerColor* m_bgTop;

	BallSlider* m_sliderMusic;
	BallSlider* m_sliderSound;

	cocos2d::Label* m_lbTheme;
	cocos2d::Label* m_lbAudio;
	cocos2d::Label* m_lbMusicVolume;
	cocos2d::Label* m_lbSoundVolume;
	cocos2d::Label* m_lbMusicVolumeValue;
	cocos2d::Label* m_lbSoundVolumeValue;
};

#endif // __SETTINGS_SCENE_H__
