#include "stdafx.h"
#include "MainGameScene.h"
#include "UI/BallButton.h"

USING_NS_CC;

Scene* S_MainGame::createScene()
{
	auto scene = Scene::create();
	auto layer = S_MainGame::create();
	scene->addChild(layer);
	return scene;
}

// on "init" you need to initialize your instance
bool S_MainGame::init()
{
	m_close = 0;
	m_tick = 0;
	m_bPaused = false;

	// super init 

	if ( !BaseScene::init(E::P.C100) )
	{
		return false;
	}

	initAnim();

	m_wheel = new MainBall;
	m_wheel->isReal = true;
	// create the spinning wheel
	auto wheel_inner = Sprite::create("ball_inner.png");
	wheel_inner->setPosition(256/2, 256/2);
	wheel_inner->setTag(0);
	wheel_inner->setColor(C3B(E::P.C800));
	//wheel_inner->setScale(0.15f);

	auto wheel = Sprite::create("ball_outer.png");
	wheel->setColor(C3B(E::P.C400));
	wheel->setScale(0.2f);
	wheel->addChild(wheel_inner);
	// add the wheel to the layer
	this->addChild(wheel, 10);



	m_wheel->sprite = wheel;

	m_smartstring = SmartString::create();
	this->addChild(m_smartstring, 11);

	m_smartstring_enemy = SmartString::create();
	this->addChild(m_smartstring_enemy, 11);
	m_smartstring_enemy->isEnemy = true;

	
	restartGame();

	// enable keyboard
	this->setKeyboardEnabled(true);

	// set up the scheduled callbacks
	this->scheduleUpdate();

	return true;
}

// the parameter dt stands for delta time, which is the time difference between the previous and the current frame.
void S_MainGame::update( float dt ) 
{
	updateAnim();
	if(!m_bPaused && !m_isGameOver){
	auto o = m_wheel->sprite->getChildByTag(0);
	o->setRotation(o->getRotation() + dt * 360);

	m_smartstring->_update();
	m_smartstring_enemy->_update();

	updateEnemyAI();

	checkCollision(m_wheel);
	}
}

void S_MainGame::onKeyReleased(EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
	// Back button pressed
	if (keyCode == EventKeyboard::KeyCode::KEY_BACKSPACE) {
		pause();
	}
	
	if (keyCode == EventKeyboard::KeyCode::KEY_G) {
		m_bPaused = false;
	}

}


bool S_MainGame::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{   
	BaseScene::onTouchBegan(touch, event);
	m_bGuide = false;
	cocos2d::Vec2 p = touch->getLocation() / E::scale;

	if(Rect(0, 0, E::visibleWidth, E::visibleHeight*0.3f).containsPoint(p))
	{
		m_smartstring->setStartingPoint(p);
		return true; // event consumed
	}

	return false; // event past thru
}

void S_MainGame::onTouchMoved(Touch* touch, Event* event){
	BaseScene::onTouchMoved(touch, event);
	m_smartstring->setEndingPoint(touch->getLocation() / E::scale);
}

void S_MainGame::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event){
	BaseScene::onTouchEnded(touch, event);
	m_smartstring->setEndingPoint(touch->getLocation() / E::scale);
	m_smartstring->go();
}

void S_MainGame::restartGame(){
	m_isGameOver = false;
	m_isRestarting = false;
	m_bGuide = true;
	m_score = 0;
	m_wheel->speed = 0;
	m_wheel->rotate = 0;//60*PI/180.0;
	m_wheel->angle = 180.0*PI/180.0f;
	m_wheel->rotatedAngle = m_wheel->angle;
	m_wheel->setPosition(E::visibleWidth/2, E::visibleHeight*0.15f);
	m_scoreLabel->setString(stdp::to_string(m_score));
}
