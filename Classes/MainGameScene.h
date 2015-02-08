#ifndef __MAIN_GAME_SCENE_H__
#define __MAIN_GAME_SCENE_H__

#include "EngineHelper.h"
#include "SmartString.h"
#include "MainBall.h"


class S_MainGame : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();  
    
    void update( float dt );

	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);

	bool onTouchBegan(Touch* touch, Event* event);

	void onTouchMoved(Touch* touch, Event* event);

	void onTouchEnded(Touch* touch, Event* event);

	void menuCallback(cocos2d::Ref* pSender);

	float getWheelRadius();

	void restartGame();

    
    CREATE_FUNC(S_MainGame);

private:

	
	void initAnim();
	void updateAnim();
	void updateEnemyAI();
	void checkCollision(MainBall* wheel);
	void pause();
	int m_close;
	
	long m_tick;
	long m_tick2;
	bool m_isGameOver;
	bool m_isRestarting;
	bool m_bGuide;

	

	MainBall* m_wheel; 

	SmartString* m_smartstring_enemy;
	SmartString* m_smartstring;
};

#endif // __MAIN_GAME_SCENE_H__
