#ifndef __ABOUT_SCENE_H__
#define __ABOUT_SCENE_H__

#include "BaseScene.h"
#include "UI/BallButton.h"
#include "UI/EdgedBallButton.h"
#include "UI/BallSlider.h"
#include "UI/TitleBar.h"

class S_About : public BaseScene
{
public:
    static cocos2d::Scene* createScene(int previousScene);
    virtual bool init();  
	void onKeyEvent(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
	void menuCallback(cocos2d::Ref* pSender);
	int _previousScene;
    CREATE_FUNC(S_About);

private:
	void runAnimations(bool);	
	BallButton* m_shareBtnBg;
	BallButton* m_rateBg;
	BallButton* m_websiteBtnBg;
	BallButton* m_btmBg;
	TitleBar* m_titleBar;

	cocos2d::Sprite* m_heartIcon;
	EdgedBallButton* m_heartBtn;
	cocos2d::Menu* m_menu;
	cocos2d::Sprite* m_shadow;
	cocos2d::LayerColor* m_bgTop;

	bool m_bClose;
};

#endif // __ABOUT_SCENE_H__
