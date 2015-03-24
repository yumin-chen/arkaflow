#include "stdafx.h"
#include "MainGameScene.h"
#include "AboutScene.h"
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
#define	TAG_RESTART		1004
#define	TAG_HOME		1005
#define	TAG_PICKLEVEL	1006

Scene* S_MainGame::createScene()
{
	auto scene = Scene::createWithPhysics();
	auto layer = S_MainGame::create();
	layer->m_physicsWorld = scene->getPhysicsWorld();
	scene->getPhysicsWorld()->setGravity(Vec2::ZERO);
#ifndef NDEBUG
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
#endif
	scene->addChild(layer);
	return scene;
}

// on "init" you need to initialize your instance
bool S_MainGame::init()
{
	m_game = nullptr;
	m_bPaused = false;
	// super init 
	if (!BaseScene::init(E::P.C100)){return false;}
#ifndef NDEBUG
	E::settings.currentLevel = 9;
#endif

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

	// 
	auto bgBtm = LayerColor::create(C4B(E::P.C100));
	bgBtm->setContentSize(Size(E::visibleWidth, GAME_BTM_HEIGHT));
	bgBtm->setPosition(0, 0);
	this->addChild(bgBtm, 1);

	m_titleBar = TitleBar::create();
	this->addChild(m_titleBar, 999);

	m_minuteLabel = Label::createWithTTF("00'", FONT_BOLD, 40, 
			Size(E::visibleWidth, TITLEBAR_HEIGHT), TextHAlignment::CENTER, TextVAlignment::CENTER);
	m_minuteLabel->setPosition(-32, TITLEBAR_HEIGHT/2);
	m_minuteLabel->setAnchorPoint(Vec2(0, 0.5));
	m_minuteLabel->enableShadow(Color4B(0, 0, 0, 128), Size(2, -2));
	m_minuteLabel->setColor(Color3B(255, 255, 255));
	m_titleBar->addChild(m_minuteLabel, 1);
	m_secondLabel = Label::createWithTTF("00\"", FONT_BOLD, 40, 
			Size(E::visibleWidth, TITLEBAR_HEIGHT), TextHAlignment::CENTER, TextVAlignment::CENTER);
	m_secondLabel->setPosition(+32, TITLEBAR_HEIGHT/2);
	m_secondLabel->setAnchorPoint(Vec2(0, 0.5));
	m_secondLabel->enableShadow(Color4B(0, 0, 0, 128), Size(2, -2));
	m_secondLabel->setColor(Color3B(255, 255, 255));
	m_titleBar->addChild(m_secondLabel, 1);

	auto homeButton = EdgedBallButton::create(CC_CALLBACK_1(S_MainGame::menuCallback, this));
	homeButton->setScale(0.3f);
	homeButton->setPosition(Vec2(48, 40));
	homeButton->setTag(TAG_HOME);
	m_titleBar->addChild(homeButton, 1000);

	auto homeIcon = Sprite::create("ui/ob_home.png");
	homeIcon->setColor(C3B(E::P.C700));
	homeIcon->setAnchorPoint(Vec2(0, 0));
	homeButton->addChild(homeIcon, 1000);

	auto pickLevelButton = EdgedBallButton::create(CC_CALLBACK_1(S_MainGame::menuCallback, this));
	pickLevelButton->setScale(0.3f);
	pickLevelButton->setPosition(Vec2(128, 40));
	pickLevelButton->setTag(TAG_PICKLEVEL);
	m_titleBar->addChild(pickLevelButton, 1000);

	auto pickLevelIcon = Sprite::create("ui/ob_pick_level.png");
	pickLevelIcon->setColor(C3B(E::P.C700));
	pickLevelIcon->setAnchorPoint(Vec2(0, 0));
	pickLevelButton->addChild(pickLevelIcon, 1000);

	auto restartButton = EdgedBallButton::create(CC_CALLBACK_1(S_MainGame::menuCallback, this));
	restartButton->setScale(0.3f);
	restartButton->setPosition(Vec2(E::visibleWidth - 48, 40));
	restartButton->setTag(TAG_RESTART);
	m_titleBar->addChild(restartButton, 1000);

	auto restartIcon = Sprite::create("ui/ob_restart.png");
	restartIcon->setColor(C3B(E::P.C700));
	restartIcon->setAnchorPoint(Vec2(0, 0));
	restartButton->addChild(restartIcon, 1000);

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
	auto boundBody = PhysicsBody::createEdgeBox(Size(E::visibleWidth+32, E::visibleHeight - TITLEBAR_HEIGHT+32+128), SMOOTH_MATERIAL, 14);
	boundBody->setContactTestBitmask(0xFFFFFFFF);
	boundBody->setCategoryBitmask(0xFFFFFF00);
	boundBody->setDynamic(false);
	edgeSp->setPosition(Vec2(E::visibleWidth / 2, (E::visibleHeight - TITLEBAR_HEIGHT) / 2 - 64));
	edgeSp->setPhysicsBody(boundBody);
	edgeSp->setTag(TAG_PHY_EDGE);
	this->addChild(edgeSp);

	auto edgeBtmSp = Sprite::create();
	auto boundBtmBody = PhysicsBody::createBox(Size(E::visibleWidth, 64), SMOOTH_MATERIAL);
	boundBtmBody->setContactTestBitmask(0xFFFFFFFF);
	boundBtmBody->setCategoryBitmask(0xFFFFFF00);
	boundBtmBody->setDynamic(false);
	edgeBtmSp->setPosition(Vec2(E::visibleWidth / 2, -32));
	edgeBtmSp->setPhysicsBody(boundBtmBody);
	edgeBtmSp->setTag(TAG_PHY_EDGE_BTM);
	this->addChild(edgeBtmSp);

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
	contactListener->onContactPreSolve = CC_CALLBACK_2(S_MainGame::onContactPreSolve, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	restartGame();

	// set up the scheduled callbacks
	this->scheduleUpdate();

	return true;
}

std::string makeTwoDigits(std::string s){
	if(s.length() == 1){
		return "0" + s;
	}
	return s;
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
		m_dGameTimer = m_dGameTimer + dt;
		int intTime = int(m_dGameTimer);
		
		m_minuteLabel->setString(makeTwoDigits(stdp::to_string(intTime)) + "'");
		m_secondLabel->setString(makeTwoDigits(stdp::to_string(int(60 * (m_dGameTimer - intTime)))) + "\"");

	}
}

void S_MainGame::onKeyEvent(EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
	// Back button pressed
	if (keyCode == EventKeyboard::KeyCode::KEY_BACK || keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {
		backHomeDialog();
	}
	
	if (keyCode == EventKeyboard::KeyCode::KEY_G) {
		m_bPaused = false;
	}

}

void S_MainGame::backHomeDialog(){
	auto leaveDialog = BallDialog::create(S("If you go back to home page, your current game will be lost, are you sure?", "返回主菜单后当前游戏数据将丢失，您确定要返回主菜单吗？"), CC_CALLBACK_0(S_MainGame::leaveGame, this));
	this->addChild(leaveDialog, 1000);
}

void S_MainGame::pickLevelDialog(){
	auto leaveDialog = BallDialog::create(S("If you pick a new level, your current game will be lost, are you sure?", "选择新的关卡后当前游戏数据将丢失，您确定要选择关卡吗？"), CC_CALLBACK_0(S_MainGame::pickLevel, this));
	this->addChild(leaveDialog, 1000);
}

void S_MainGame::pickLevel(){
}

bool S_MainGame::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{   
	m_bStringTouchFocus = false;
	if(BaseScene::onTouchBegan(touch, event)){
		return true;
	}
	cocos2d::Vec2 p = touch->getLocation() / E::scale;

	if(Rect(0, 0, E::visibleWidth, GAME_BTM_HEIGHT).containsPoint(p))
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
	m_wheel->speed = 0;
	m_wheel->rotate = 0;//60*PI/180.0;
	m_wheel->angle = 180.0*PI/180.0f;
	m_wheel->rotatedAngle = m_wheel->angle;
	m_wheel->setPosition(E::visibleWidth/2, GAME_BTM_HEIGHT/2);
	m_dGameTimer = 0;
	m_minuteLabel->setString("00'");
	m_secondLabel->setString("00\"");
	
	auto wheelBody = PhysicsBody::createCircle(192*0.5f*m_wheel->sprite->getScale(), SMOOTH_MATERIAL);
	wheelBody->setContactTestBitmask(0xFFFFFFFF);
	m_wheel->sprite->setPhysicsBody(wheelBody);
	if(m_game && m_game->getLevel() == E::settings.currentLevel){
		m_game->restart();
	}else{
		if(m_game)
			m_game->removeFromParentAndCleanup(true);
		m_game = Levels::createLevel(E::settings.currentLevel);
		m_game->setOpacity(0);
		addChild(m_game, 2);
		m_game->runAction(Sequence::create(DelayTime::create(0.6f), FadeIn::create(0.3f), nullptr));
	}

	
}

void S_MainGame::nextLevelDialog(){
	m_isGameOver = true;
	m_wheel->sprite->getPhysicsBody()->removeFromWorld();
	E::settings.currentLevel++;
	if(E::settings.currentLevel > MAX_LEVEL){
		E::settings.currentLevel = 1;
		auto nextLevelDialog = BallDialog::create(S("You've completed all levels. Thanks for playing!", "你已通过所有关卡，谢谢您对游戏的支持与喜爱！"), CC_CALLBACK_0(S_MainGame::goToAboutPage, this), CC_CALLBACK_0(S_MainGame::restartGame, this), "ui/b_heart.png", "ui/b_restart.png");
		this->addChild(nextLevelDialog, 1000);
		return;
	}
	if(E::settings.currentLevel > E::settings.unlockedLevel){
		E::settings.unlockedLevel = E::settings.currentLevel;
	}
	auto ud = UserDefault::getInstance();
	ud->setIntegerForKey(UD_CURRENT_LEVEL, E::settings.currentLevel);
	ud->setIntegerForKey(UD_UNLOCKED_LEVEL, E::settings.unlockedLevel);
	auto nextLevelDialog = BallDialog::create(S("Level accomplished!", "恭喜您，过关了！"), CC_CALLBACK_0(S_MainGame::restartGame, this), CC_CALLBACK_0(S_MainGame::backLevel, this), "ui/b_next.png", "ui/b_restart.png");
	this->addChild(nextLevelDialog, 1000);
}

void S_MainGame::backLevel(){
	E::settings.currentLevel--;
	auto ud = UserDefault::getInstance();
	ud->setIntegerForKey(UD_CURRENT_LEVEL, E::settings.currentLevel);
	restartGame();
}

void S_MainGame::leaveGame(){
	Director::getInstance()->replaceScene(S_Welcome::createScene());
}

void S_MainGame::goToAboutPage(){
	Director::getInstance()->replaceScene(S_About::createScene(2));
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

	case TAG_RESTART:
		{
			auto leaveDialog = BallDialog::create(S("Do you want to restart this game?", "是否想要重新开始这一关？"), CC_CALLBACK_0(S_MainGame::restartGame, this));
			this->addChild(leaveDialog, 1000);
			break;
		}
	case TAG_HOME:
		{
			backHomeDialog();
			break;
		}
	case TAG_PICKLEVEL:
		{
			pickLevelDialog();
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
		}
		else if (nodeA->getTag() == TAG_PHY_TARGET && nodeB->getTag() == TAG_PHY_BALL)
		{
			((Target*)nodeA)->beHit();
		}
	}

	if(nodeA->getTag() == TAG_PHY_BALL || nodeB->getTag() == TAG_PHY_BALL){
		Vec2 pos;
		if(nodeA->getTag() == TAG_PHY_BALL){pos = nodeA->getPosition();}
		else{pos = nodeB->getPosition();}
		putEmitter(pos);
	}
	
	if(nodeA->getTag() == TAG_PHY_EDGE || nodeB->getTag() == TAG_PHY_EDGE || nodeA->getTag() == TAG_PHY_BLOCK || nodeB->getTag() == TAG_PHY_BLOCK){
		E::playEffect("di");
	}
	else if(nodeA->getTag() == TAG_PHY_EDGE_BTM || nodeB->getTag() == TAG_PHY_EDGE_BTM){
		E::playEffect("beng");
		gameOver();
	}
	//bodies can collide
	return true;
}

bool S_MainGame::onContactPreSolve(PhysicsContact& contact, PhysicsContactPreSolve& solve){
	/*
	if(m_isGameOver || m_bPaused){
		return false;
	}
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();
	if (nodeA && nodeB)
	{
		if (nodeA->getTag() == TAG_PHY_BALL || nodeB->getTag() == TAG_PHY_BALL)
		{
			Vec2 v = solve.getSurfaceVelocity();
			if(sqrt(v.x * v.x + v.y * v.y) < 640){
				float angle = atan2(v.y, v.x);
				Vec2 newv = Vec2(640 * sin(angle), -640 * cos(angle));
				solve.setSurfaceVelocity(newv);
				float newangle = atan2(newv.y, newv.x);
				if(newangle != angle){
					printf("error");
				}
				return true;
			}
		}
	}
	*/
	return true;
}
