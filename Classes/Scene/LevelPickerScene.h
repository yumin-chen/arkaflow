#ifndef __LEVEL_PICKER_SCENE_H__
#define __LEVEL_PICKER_SCENE_H__

#include "BaseScene.h"
#include "../UI/BallButton.h"
#include "../UI/EdgedBallButton.h"
#include "../UI/BallSlider.h"
#include "../UI/TitleBar.h"

class S_LevelPicker : public BaseScene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();  
	void onKeyEvent(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
	void menuCallback(cocos2d::Ref* pSender);
    CREATE_FUNC(S_LevelPicker);

private:
	void _ok();
	void _cancel();
	int m_bClose;
	int m_tempLevel;
	void runAnimations(bool);

	BallButton* m_OkNormal;
	BallButton* m_OkSelected;
	BallButton* m_CancelNormal;
	BallButton* m_CancelSelected;
	BallButton* m_okBtnBg;
	BallButton* m_cancelBg;
	BallButton* m_btmBg;
	TitleBar* m_titleBar;

	
	cocos2d::Menu* m_menu;
	cocos2d::Sprite* m_shadow;
	cocos2d::LayerColor* m_bgTop;
	cocos2d::Label* m_lbLevel;
};

#endif // __LEVEL_PICKER_SCENE_H__
