#ifndef __MAIN_GAME_SCENE_H__
#define __MAIN_GAME_SCENE_H__

#include "scene/BaseScene.h"
#include "element/SmartString.h"
#include "element/MainBall.h"
#include "UI/BallButton.h"

#define MAIN_BALL_DIAMETER 192*0.2
#define MAIN_BALL_RADIUS (MAIN_BALL_DIAMETER/2)

class S_MainGame : public BaseScene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();  
    
    void update( float dt );

	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);

	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);

	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

	void menuCallback(cocos2d::Ref* pSender);

	float getWheelRadius();

	void restartGame();

    
    CREATE_FUNC(S_MainGame);

private:

	
	void initAnim();
	void updateAnim();
	void updateEnemyAI();
	void checkCollision(MainBall* wheel);
	void collidingWithBorder();
	void addScore(int);
	void pause();
	int m_close;
	
	long m_tick;
	long m_tick2;
	bool m_isGameOver;
	bool m_isRestarting;
	bool m_bGuide;
	bool m_bPaused;

	

	MainBall* m_wheel; 
	cocos2d::Label* m_scoreLabel;
	BallButton* m_mbg;
	int m_score;

	SmartString* m_smartstring_enemy;
	SmartString* m_smartstring;
};

#endif // __MAIN_GAME_SCENE_H__
