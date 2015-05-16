#ifndef __WELCOME_SCENE_H__
#define __WELCOME_SCENE_H__

#include "BaseScene.h"
#include "../Element/Triangle.h"
#include "../Element/Ring.h"
#include "../UI/BallButton.h"

class S_Welcome : public BaseScene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();    
    void menuCallback(cocos2d::Ref* pSender);
	void onKeyEvent(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
    CREATE_FUNC(S_Welcome);
private:
	int m_bClose;
	void runAnimations(bool);
	void _exitGame();
	cocos2d::Menu* m_menu;
	cocos2d::Label* m_title;
	cocos2d::Label* m_title2;
	Ring* m_ring;
	Triangle* m_tri;
	BallButton* m_bg;
	BallButton* m_newGameBg;
	BallButton* m_settingsBg;
};

#endif // __WELCOME_SCENE_H__
