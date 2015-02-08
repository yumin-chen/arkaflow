#include "stdafx.h"
#include "MainGameScene.h"
#include "BallButton.h"

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
	// super init 

	if ( !LayerColor::initWithColor(C4B(E::C100)) )
	{
		return false;
	}


	this->setScale(E::scale);
	this->setContentSize(Size(E::visibleWidth, E::visibleHeight));
	this->setAnchorPoint(Vec2(0, 0));

	initAnim();

	m_wheel = new MainBall;
	m_wheel->isReal = true;
	// create the spinning wheel
	auto wheel = Sprite::create("wheel.png");
	wheel->setColor(C3B(E::C900));
	wheel->setScale(0.15f);
	// add the wheel to the layer
	this->addChild(wheel, 10);

	m_wheel->sprite = wheel;
	restartGame();

	m_smartstring = SmartString::create();
	this->addChild(m_smartstring, 11);

	m_smartstring_enemy = SmartString::create();
	this->addChild(m_smartstring_enemy, 11);
	m_smartstring_enemy->isEnemy = true;

	auto listener = cocos2d::EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(S_MainGame::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(S_MainGame::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(S_MainGame::onTouchEnded, this);

	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	// set up the scheduled callbacks
	this->scheduleUpdate();

	return true;
}


void S_MainGame::update( float dt )
{
	updateAnim();

	m_smartstring->_update();
	m_smartstring_enemy->_update();

	updateEnemyAI();

	checkCollision(m_wheel);
}

void S_MainGame::onKeyReleased(EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
	// Back button pressed
	if (keyCode == EventKeyboard::KeyCode::KEY_BACKSPACE) {
		pause();
	}


}


bool S_MainGame::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{   
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
	//this->ccTouchBegan(touch, event);
	m_smartstring->setEndingPoint(touch->getLocation() / E::scale);
}

void S_MainGame::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event){
	m_smartstring->setEndingPoint(touch->getLocation() / E::scale);
	m_smartstring->go();
}

float S_MainGame::getWheelRadius(){
	return m_wheel->sprite->getContentSize().width * m_wheel->sprite->getScale() /2;
}
 ;
void S_MainGame::restartGame(){
	m_isGameOver = false;
	m_isRestarting = false;
	m_bGuide = true;
	m_wheel->speed = 0;
	m_wheel->rotate = 0;//60*PI/180.0;
	m_wheel->angle = 180*PI/180.0;
	m_wheel->rotatedAngle = m_wheel->angle;
	m_wheel->setPosition(E::visibleWidth/2, E::visibleHeight*0.23f);
}
