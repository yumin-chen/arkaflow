#ifndef __MAIN_GAME_SCENE_H__
#define __MAIN_GAME_SCENE_H__

#include "BaseScene.h"
#include "../Element/SmartString.h"
#include "../UI/BallButton.h"
#include "../UI/TitleBar.h"
#include "../Levels/BaseLevel.h"

#define MAIN_BALL_DIAMETER (192*0.2)
#define MAIN_BALL_RADIUS (MAIN_BALL_DIAMETER/2)

#define GAME_BTM_HEIGHT	(192)

#define	TAG_PHY				19950204
#define TAG_PHY_EDGE		(TAG_PHY+1)
#define TAG_PHY_EDGE_BTM	(TAG_PHY+2)
#define TAG_PHY_BALL		(TAG_PHY+3)
#define TAG_PHY_STRING		(TAG_PHY+4)
#define TAG_PHY_TARGET		(TAG_PHY+5)
#define TAG_PHY_BLOCK		(TAG_PHY+6)

class S_MainGame : public BaseScene
{
public:
	S_MainGame();
    static cocos2d::Scene* createScene();
    virtual bool init();      
    void update( float dt );
	void restartGame();
	void leaveGame();    
	void nextLevelDialog();
	void backHomeDialog();
	void pickLevelDialog();
	void static printString(std::string);
	cocos2d::Sprite* getMainBall();
    CREATE_FUNC(S_MainGame);

private:
	void initAnim();
	bool onContactBegin(cocos2d::PhysicsContact& contact);
	bool onContactPreSolve(cocos2d::PhysicsContact& contact, cocos2d::PhysicsContactPreSolve& solve);
	void onKeyEvent(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	void menuCallback(cocos2d::Ref* pSender);
	void collidingWithBorder();
	void pause();
	void gameOver();
	void backLevel();
	void pickLevel();
	void goToAboutPage();

	bool m_isGameOver;
	bool m_isRestarting;
	bool m_bPaused;
	bool m_bStringTouchFocus;
	double m_dGameTimer;

	cocos2d::MotionStreak* m_ballStreak;
	cocos2d::PhysicsWorld* m_physicsWorld;
	cocos2d::Sprite* m_soundIcon;
	cocos2d::Sprite* m_stsBackground;
	cocos2d::Sprite* m_stsShine;
	cocos2d::LayerColor* m_stsLayer;
	cocos2d::Label* m_minuteLabel;
	cocos2d::Label* m_secondLabel;
	cocos2d::Label* m_printer;
	TitleBar* m_titleBar;
	BallButton* m_mbg;
	BaseLevel* m_game;

	SmartString* m_smartstring;
};

#endif // __MAIN_GAME_SCENE_H__
