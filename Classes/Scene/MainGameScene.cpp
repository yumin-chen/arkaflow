#include "stdafx.h"
#include "MainGameScene.h"
#include "WelcomeScene.h"
#include "UI/BallButton.h"
#include "UI/EdgedBallButton.h"
#include "UI/TitleBar.h"
#include "UI/BallDialog.h"
#include "Levels/Levels.h"
#include "Element/Target.h"

USING_NS_CC;

#define	TAG_PAUSE		1002
#define	TAG_SILENT		1003

Scene* S_MainGame::createScene()
{
	auto scene = Scene::createWithPhysics();
	auto layer = S_MainGame::create();
	layer->m_physicsWorld = scene->getPhysicsWorld();
	scene->getPhysicsWorld()->setGravity(Vec2::ZERO);
#ifndef NDEBUG
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
#endif
	scene->addChild(layer);
	return scene;
}

// on "init" you need to initialize your instance
bool S_MainGame::init()
{
	m_bPaused = false;
	// super init 
	if (!BaseScene::init(E::P.C100)){return false;}

	// disable touch emitter
	setTouchEmitterEnabled(false);

	// create solid color background
	m_mbg = BallButton::create(E::P.C50);
	m_mbg->setScale(0.3f);
	m_mbg->setPosition(Vec2(E::visibleWidth/2, 0));
	auto cbGoHigher = CallFunc::create([this](){m_mbg->setLocalZOrder(15);});
	auto cbGoLower = CallFunc::create([this](){m_mbg->setLocalZOrder(0);});
	this->addChild(m_mbg, 15);
	auto seq = Sequence::create(MoveBy::create(0.4f, Vec2(0, (E::visibleHeight-TITLEBAR_HEIGHT)/2)), cbGoHigher, cbGoLower, ScaleBy::create(0.4f, 16), nullptr);
	m_mbg->runAction(seq);

	m_game = Levels::createLevel(1);
	m_game->setOpacity(0);
	addChild(m_game, 2);
	m_game->runAction(Sequence::create(DelayTime::create(0.6f), FadeIn::create(0.3f), nullptr));

	// 
	auto bgBtm = LayerColor::create(C4B(E::P.C100));
	bgBtm->setContentSize(Size(E::visibleWidth, GAME_BTM_HEIGHT));
	bgBtm->setPosition(0, 0);
	this->addChild(bgBtm, 1);

	m_titleBar = TitleBar::create(S("", "乾坤弹球"));
	this->addChild(m_titleBar, 999);

	auto pauseButton = EdgedBallButton::create(CC_CALLBACK_1(S_MainGame::menuCallback, this));
	pauseButton->setScale(0.3f);
	pauseButton->setPosition(Vec2(E::visibleWidth - 48, 40));
	pauseButton->setTag(TAG_PAUSE);
	m_titleBar->addChild(pauseButton, 1000);

	auto pauseIcon = Sprite::create("ui/ob_pause.png");
	pauseIcon->setColor(C3B(E::P.C700));
	pauseIcon->setAnchorPoint(Vec2(0, 0));
	pauseButton->addChild(pauseIcon, 1000);

	auto silentButton = EdgedBallButton::create(CC_CALLBACK_1(S_MainGame::menuCallback, this));
	silentButton->setScale(0.3f);
	silentButton->setPosition(Vec2(E::visibleWidth - 128, 40));
	silentButton->setTag(TAG_SILENT);
	m_titleBar->addChild(silentButton, 1000);

	m_soundIcon = Sprite::create(E::settings.musicEnabled && E::settings.soundEnabled ? "ui/ob_sound_on.png": "ui/ob_sound_off.png");
	m_soundIcon->setColor(C3B(E::P.C700));
	m_soundIcon->setAnchorPoint(Vec2(0, 0));
	silentButton->addChild(m_soundIcon, 1000);

	// create the shadow
	auto shadow = Sprite::create("ui/shadow.png");
	shadow->setScale(1.0f);
	shadow->setAnchorPoint(Vec2(0, 1));
	shadow->setScaleX(E::visibleWidth / DESIGNED_WIDTH);
	shadow->setPosition(0, GAME_BTM_HEIGHT);
	shadow->setOpacity(0);
	this->addChild(shadow, 2);
	shadow->runAction(Sequence::create(DelayTime::create(0.4f), FadeIn::create(0.6f), nullptr));

	// slide to start background
	m_stsBackground = Sprite::create("ui/slide_to_start_bg.png");
	m_stsBackground->setScale(0.3f);
	m_stsBackground->setColor(bgBtm->getColor());
	m_stsBackground->setPosition(Vec2(E::visibleWidth/2, GAME_BTM_HEIGHT/2-48));
	this->addChild(m_stsBackground, 5);

	// 
	m_stsShine = Sprite::create("ui/slide_to_start_shine.png");
	m_stsShine->setScale(0.3f);
	m_stsShine->setColor(C3B(E::P.C800));
	m_stsShine->setAnchorPoint(Vec2(0, 0.5));
	m_stsShine->setPosition(Vec2(E::visibleWidth/2 - m_stsBackground->getBoundingBox().size.width / 2, GAME_BTM_HEIGHT/2-48));
	this->addChild(m_stsShine, 4);

	//
	m_stsLayer = LayerColor::create(C4B(E::P.C800));
	m_stsLayer->setAnchorPoint(Vec2(0.5, 0.5));
	m_stsLayer->setContentSize(Size(m_stsBackground->getBoundingBox().size.width, m_stsBackground->getBoundingBox().size.height));
	m_stsLayer->setPosition(Vec2(E::visibleWidth/2 - m_stsBackground->getBoundingBox().size.width/2, GAME_BTM_HEIGHT/2-48 - m_stsBackground->getBoundingBox().size.height/2));
	this->addChild(m_stsLayer, 4);

	auto shiningMove = MoveBy::create(1.0f, Vec2(m_stsBackground->getBoundingBox().size.width - m_stsShine->getBoundingBox().size.width, 0));
	auto cbm_stsLayerShinePos = CallFunc::create([this](){m_stsShine->setPositionX(E::visibleWidth/2 - m_stsBackground->getBoundingBox().size.width / 2);});
	m_stsShine->runAction(RepeatForever::create(Sequence::create(shiningMove, cbm_stsLayerShinePos, nullptr)));
	m_stsLayer->runAction(RepeatForever::create(Sequence::create(FadeIn::create(0.5f), DelayTime::create(1.0f), FadeOut::create(0.5f), DelayTime::create(3.0f), nullptr)));
	

	// create edges
	auto edgeSp = Sprite::create();
	auto boundBody = PhysicsBody::createEdgeBox(Size(E::visibleWidth+30, E::visibleHeight - TITLEBAR_HEIGHT+30), SMOOTH_MATERIAL, 16);
	boundBody->setContactTestBitmask(0xFFFFFFFF);
	boundBody->setCategoryBitmask(0xFFFFFF00);
	boundBody->setDynamic(false);
	edgeSp->setPosition(Vec2(E::visibleWidth / 2, (E::visibleHeight - TITLEBAR_HEIGHT) / 2));
	edgeSp->setPhysicsBody(boundBody);
	edgeSp->setTag(TAG_PHY_EDGE);
	this->addChild(edgeSp);

	//
	m_wheel = new MainBall;
	m_wheel->isReal = true;
	// create the spinning wheel
	auto wheel_inner = Sprite::create("ui/ball_inner.png");
	wheel_inner->setPosition(256/2, 256/2);
	wheel_inner->setTag(0);
	wheel_inner->setColor(C3B(E::P.C800));
	//wheel_inner->setScale(0.15f);

	auto wheel = Sprite::create("ui/ball_outer.png");
	wheel->setColor(C3B(E::P.C400));
	wheel->setScale(0.2f);
	wheel->addChild(wheel_inner);
	wheel->setTag(TAG_PHY_BALL);
	//wheel->getPhysicsBody()->

	// add the wheel to the layer
	this->addChild(wheel, 10);

	m_ballStreak = MotionStreak::create(2.0f, 0, 4, C3B(E::P.C600), "ui/streak.png");
	this->addChild(m_ballStreak, 9);

	m_wheel->sprite = wheel;

	m_smartstring = SmartString::create();
	this->addChild(m_smartstring, 11);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(S_MainGame::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

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
	if(!m_bPaused && !m_isGameOver){
	auto o = m_wheel->sprite->getChildByTag(0);
	o->setRotation(o->getRotation() + dt * 360);
	m_ballStreak->setPosition( m_wheel->sprite->getPosition() );
	m_smartstring->update(dt);
	m_game->update(dt);
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
	m_bStringTouchFocus = false;
	if(BaseScene::onTouchBegan(touch, event)){
		return true;
	}
	cocos2d::Vec2 p = touch->getLocation() / E::scale;

	if(Rect(0, 0, E::visibleWidth, (E::visibleHeight - TITLEBAR_HEIGHT)*0.3f).containsPoint(p))
	{
		m_stsBackground->setVisible(false);
		m_stsShine->setVisible(false);
		m_stsLayer->setVisible(false);
		m_smartstring->setStartingPoint(p);
		m_bStringTouchFocus = true;
		return true; // event consumed
	}

	return false; // event past thru
}

void S_MainGame::onTouchMoved(Touch* touch, Event* event){
	BaseScene::onTouchMoved(touch, event);
	if(m_bStringTouchFocus)
		m_smartstring->setEndingPoint(touch->getLocation() / E::scale);
}

void S_MainGame::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event){
	BaseScene::onTouchEnded(touch, event);
	if(m_bStringTouchFocus){
		m_smartstring->setEndingPoint(touch->getLocation() / E::scale);
		m_smartstring->go();
	}
}

void S_MainGame::restartGame(){
	m_isGameOver = false;
	m_isRestarting = false;
	m_stsBackground->setVisible(true);
	m_stsShine->setVisible(true);
	m_stsLayer->setVisible(true);
	m_score = 0;
	m_wheel->speed = 0;
	m_wheel->rotate = 0;//60*PI/180.0;
	m_wheel->angle = 180.0*PI/180.0f;
	m_wheel->rotatedAngle = m_wheel->angle;
	m_wheel->setPosition(E::visibleWidth/2, GAME_BTM_HEIGHT/2);
	m_titleBar->setString(stdp::to_string(m_score));
	
	auto wheelBody = PhysicsBody::createCircle(192*0.5f*m_wheel->sprite->getScale(), SMOOTH_MATERIAL);
	wheelBody->setContactTestBitmask(0xFFFFFFFF);
	//wheelBody->set
	m_wheel->sprite->setPhysicsBody(wheelBody);
}

void S_MainGame::leaveGame(){
	Director::getInstance()->replaceScene(S_Welcome::createScene());
}

void S_MainGame::gameOver(){
	m_isGameOver = true;
	m_wheel->sprite->getPhysicsBody()->removeFromWorld();
	auto gameOverDialog = BallDialog::create(S("Game Over", "游戏结束"), CC_CALLBACK_0(S_MainGame::restartGame, this), CC_CALLBACK_0(S_MainGame::leaveGame, this), "ui/b_restart.png", "ui/b_leave.png");
	this->addChild(gameOverDialog, 1000);
}

void S_MainGame::pause()
{
	m_bPaused = true;
}

void S_MainGame::menuCallback(Ref* pSender)
{
	auto pMenuItem = (MenuItem*)pSender;
	auto tag = pMenuItem->getTag();
	switch(tag)
	{
	case TAG_PAUSE:
		{
			pause();
			break;
		}

	case TAG_SILENT:
		{
			if(E::settings.soundEnabled || E::settings.musicEnabled){
				E::settings.soundEnabled = false;
				E::settings.musicEnabled = false;
				CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
				CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
				m_soundIcon->setTexture("ui/ob_sound_off.png");
			}
			else{
				E::settings.soundEnabled = true;
				E::settings.musicEnabled = true;
				m_soundIcon->setTexture("ui/ob_sound_on.png");
				E::playBgMusic();
			}
			break;
		}
	}

}


bool S_MainGame::onContactBegin(PhysicsContact& contact)
{
	if(m_isGameOver || m_bPaused){
		return false;
	}
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();
	if (nodeA && nodeB)
	{
		if (nodeA->getTag() == TAG_PHY_BALL && nodeB->getTag() == TAG_PHY_STRING)
		{
			((SmartString*)nodeB)->onContactWithBall();
			E::playEffect("da");
		}
		else if (nodeA->getTag() == TAG_PHY_STRING && nodeB->getTag() == TAG_PHY_BALL)
		{
			((SmartString*)nodeA)->onContactWithBall();	
			E::playEffect("da");
		}

		if (nodeA->getTag() == TAG_PHY_BALL && nodeB->getTag() == TAG_PHY_TARGET)
		{
			((Target*)nodeB)->beHit();
			E::playEffect("beng");
		}
		else if (nodeA->getTag() == TAG_PHY_TARGET && nodeB->getTag() == TAG_PHY_BALL)
		{
			((Target*)nodeA)->beHit();
			E::playEffect("beng");
		}
	}

	if(nodeA->getTag() == TAG_PHY_BALL || nodeB->getTag() == TAG_PHY_BALL){
		Vec2 pos;
		if(nodeA->getTag() == TAG_PHY_BALL){pos = nodeA->getPosition();}
		else{pos = nodeB->getPosition();}
		putEmitter(pos);
	}
	
	if(nodeA->getTag() == TAG_PHY_EDGE || nodeB->getTag() == TAG_PHY_EDGE){
		bool b = false;
#define WHEEL_RADIUS (m_wheel->sprite->getContentSize().width*192/256*m_wheel->sprite->getScale()*E::scale)
		/*
		auto cbCloseAS = CallFunc::create([this](){m_physicsWorld->setAutoStep(false);});
		auto cbOpenAS = CallFunc::create([this](){m_physicsWorld->setAutoStep(true);});
		//auto delay = DelayTime::create(0.05f)
		//up
		if(((E::visibleHeight - TITLEBAR_HEIGHT) - m_wheel->sprite->getPositionY()) <= WHEEL_RADIUS){
			this->runAction(Sequence::create(cbCloseAS, MoveBy::create(0.05f, Vec2(0, 8)), MoveBy::create(0.05f, Vec2(0, -8)), cbOpenAS, nullptr));
			b = true;
		}
		//left
		if(m_wheel->sprite->getPositionX() <= WHEEL_RADIUS){
			this->runAction(Sequence::create(cbCloseAS, MoveBy::create(0.05f, Vec2(-8, 0)), MoveBy::create(0.05f, Vec2(8, 0)), cbOpenAS, nullptr));
			b = true;
		}
		
		//right
		if((E::visibleWidth - m_wheel->sprite->getPositionX()) <= WHEEL_RADIUS){
			this->runAction(Sequence::create(cbCloseAS, MoveBy::create(0.05f, Vec2(8, 0)), MoveBy::create(0.05f, Vec2(-8, 0)), cbOpenAS, nullptr));
			b = true;
		}

		if(b){
			E::playEffect("di");
		}
		*/

		//down
		if(m_wheel->sprite->getPositionY() <= WHEEL_RADIUS){
			//this->runAction(Sequence::create(MoveBy::create(0.05f, Vec2(0, -8)), MoveBy::create(0.05f, Vec2(0, 8)), nullptr));
			E::playEffect("beng");
			gameOver();
		}else{E::playEffect("di");}
	}
	//bodies can collide
	return true;
}

void S_MainGame::addScore(int score){
	m_score += score;
	m_titleBar->setString(stdp::to_string(m_score));
}
