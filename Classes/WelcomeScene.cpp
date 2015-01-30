#include "stdafx.h"
#include "WelcomeScene.h"
#include "MainGameScene.h"
#include "SettingsScene.h"
#include "BallButton.h"

USING_NS_CC;

#define TAG_NEW_GAME		25
#define	TAG_SETTINGS		31
#define TAG_BACKGROUND		27
#define TAG_NEW_GAME_BG		28
#define	TAG_SETTINGS_BG		32
#define	TAG_MENU			29
#define TAG_TITLE			30

Scene* S_Welcome::createScene()
{


	auto scene = Scene::create();

	auto layer = S_Welcome::create();

	scene->addChild(layer);

	return scene;
}


bool S_Welcome::init()
{
	// super init 
	if ( !LayerColor::initWithColor(C4B(E::C100)) )
	{
		return false;
	}

	m_tick = 0;
	m_bClose = 0;

	this->setScale(E::scale);
	this->setContentSize(Size(E::visibleWidth, E::visibleHeight));
	this->setAnchorPoint(Vec2(0, 0));

	// create solid color background
	auto bg = BallButton::create(E::C50);
	bg->setScale(0.3f);
	bg->setPosition(E::visibleWidth/2, 128);
	bg->setTag(TAG_BACKGROUND);
	// add the wheel to the layer
	this->addChild(bg, 0);

	

	auto newGameBg = BallButton::create(E::C700);
	newGameBg->setScale(0.2f);
	newGameBg->setPosition(E::visibleWidth/2 -(newGameBg->getContentSize().width*0.5f + 24)/2, 32);
	newGameBg->setTag(TAG_NEW_GAME_BG);
	this->addChild(newGameBg, 0);

	auto sNewIcon = Sprite::create("b_newgame.png");
	sNewIcon->setColor(C3B(E::C50));
	sNewIcon->setAnchorPoint(Vec2(0, 0));
	//newGameBg->addChild(sNewIcon);

	auto settingsBg = BallButton::create(E::C700);
	settingsBg->setScale(0.2f);
	settingsBg->setPosition(E::visibleWidth/2 +(settingsBg->getContentSize().width*0.5f + 24)/2, 32);
	settingsBg->setTag(TAG_SETTINGS_BG);
	this->addChild(settingsBg, 0);

	auto sSettingsIcon = Sprite::create("b_settings.png");
	sSettingsIcon->setColor(C3B(E::C50));
	sSettingsIcon->setAnchorPoint(Vec2(0, 0));
	//settingsBg->addChild(sSettingsIcon);

	// create title sprite
	auto title = Sprite::create("title.png");
	// position the sprite on the center of the screen
	title->setPosition(Vec2(E::visibleWidth/2 + 206/4, E::visibleHeight/2 + 96 - 234/4));
	title->setScale(0.6f);
	title->setTag(TAG_TITLE);
	title->setOpacity(0);
	this->addChild(title, 0);

	

	auto sNewNormal = BallButton::create(E::C700);

	auto sNewSelected = BallButton::create(E::C200);

	auto sSettingsNormal = BallButton::create(E::C700);

	auto sSettingsSelected = BallButton::create(E::C200);

	auto newGame = MenuItemSprite::create(
		sNewNormal,
		sNewSelected,
		CC_CALLBACK_1(S_Welcome::menuCallback, this));

	newGame->setScale(0.5f);
	newGame->setTag(TAG_NEW_GAME);
	newGame->addChild(sNewIcon);

	auto settings = MenuItemSprite::create(
		sSettingsNormal,
		sSettingsSelected,
		CC_CALLBACK_1(S_Welcome::menuCallback, this));

	settings->setScale(0.5f);
	settings->setTag(TAG_SETTINGS);
	settings->addChild(sSettingsIcon);

	// create menu
	auto menu = Menu::create(newGame, settings, NULL);
	menu->setPosition(Vec2::ZERO);
	menu->setPosition(Vec2(E::visibleWidth/2, 32 + 128));
	menu->alignItemsHorizontallyWithPadding(24);
	menu->setTag(TAG_MENU);
	menu->setOpacity(0);
	menu->setVisible(false);
	this->addChild(menu, 1);

	// set up the scheduled callbacks
	this->scheduleUpdate();

	return true;
}


#define ANIMATION_MOVING_DURATION		15.0f
#define ANIMATION_SCALING_DURATION_1	45.0f
#define ANIMATION_SCALING_DURATION_2	15.0f
#define ANIMATION_OPACITING_DURATION	15.0f
#define ANIMATION_OPAC_BACK_DURATION	9.0f

void S_Welcome::update( float dt ) 
{
	if(m_bClose){
		m_tick = m_tick - 2;
	}
	else{
		m_tick ++;
	}

	if(m_tick < 0 && m_tick >= -ANIMATION_OPAC_BACK_DURATION){
		this->getChildByTag(TAG_NEW_GAME_BG)->setOpacity(255-(m_tick/(-ANIMATION_OPAC_BACK_DURATION))*255);
		this->getChildByTag(TAG_SETTINGS_BG)->setOpacity(255-(m_tick/(-ANIMATION_OPAC_BACK_DURATION))*255);
	}
	
	if(m_tick < -ANIMATION_OPAC_BACK_DURATION){
		Scene *scene;
		//m_tick = -ANIMATION_OPAC_BACK_DURATION;
		switch(m_bClose){
		case TAG_NEW_GAME:
			scene = S_MainGame::createScene();
			break;
		case TAG_SETTINGS:
			scene = S_Settings::createScene();
			break;
		}

		Director::getInstance()->replaceScene(scene);//TransitionFadeDown::create(0.5, scene));
		return;
	}

	if(m_tick <= ANIMATION_MOVING_DURATION){
		this->getChildByTag(TAG_BACKGROUND)->setPositionY(128+(m_tick/(ANIMATION_MOVING_DURATION))*128);
		this->getChildByTag(TAG_NEW_GAME_BG)->setPositionY(32+(m_tick/(ANIMATION_MOVING_DURATION))*128);
		this->getChildByTag(TAG_SETTINGS_BG)->setPositionY(32+(m_tick/(ANIMATION_MOVING_DURATION))*128);
	}
	if(m_tick >= ANIMATION_MOVING_DURATION && m_tick <= ANIMATION_MOVING_DURATION + ANIMATION_SCALING_DURATION_1){
		this->getChildByTag(TAG_BACKGROUND)->setPositionY(256+((m_tick-ANIMATION_MOVING_DURATION)/(ANIMATION_SCALING_DURATION_1))*128);
		this->getChildByTag(TAG_BACKGROUND)->setScale(0.3f + ((m_tick-ANIMATION_MOVING_DURATION)/(ANIMATION_SCALING_DURATION_1))*5.0f);
	}
	if(m_tick >= ANIMATION_MOVING_DURATION && m_tick <= ANIMATION_MOVING_DURATION + ANIMATION_SCALING_DURATION_2){
		this->getChildByTag(TAG_MENU)->setVisible(false);
		this->getChildByTag(TAG_NEW_GAME_BG)->setOpacity(255);
		this->getChildByTag(TAG_SETTINGS_BG)->setOpacity(255);
		this->getChildByTag(TAG_MENU)->setOpacity(0);
		this->getChildByTag(TAG_TITLE)->setOpacity(0);
		this->getChildByTag(TAG_NEW_GAME_BG)->setScale(0.2f + ((m_tick-ANIMATION_MOVING_DURATION)/(ANIMATION_SCALING_DURATION_2))*0.3f);
		this->getChildByTag(TAG_SETTINGS_BG)->setScale(0.2f + ((m_tick-ANIMATION_MOVING_DURATION)/(ANIMATION_SCALING_DURATION_2))*0.3f);
	}

	if(m_tick >= ANIMATION_MOVING_DURATION + ANIMATION_SCALING_DURATION_2 
		&& m_tick <= ANIMATION_MOVING_DURATION + ANIMATION_SCALING_DURATION_2 + ANIMATION_OPACITING_DURATION){
			this->getChildByTag(TAG_MENU)->setVisible(true);
			this->getChildByTag(TAG_NEW_GAME_BG)->setOpacity(255 - ((m_tick-ANIMATION_MOVING_DURATION - ANIMATION_SCALING_DURATION_2)/(ANIMATION_OPACITING_DURATION))*128);
			this->getChildByTag(TAG_SETTINGS_BG)->setOpacity(255 - ((m_tick-ANIMATION_MOVING_DURATION - ANIMATION_SCALING_DURATION_2)/(ANIMATION_OPACITING_DURATION))*128);
			this->getChildByTag(TAG_MENU)->setOpacity(((m_tick-ANIMATION_MOVING_DURATION - ANIMATION_SCALING_DURATION_2)/(ANIMATION_OPACITING_DURATION))*255);
			this->getChildByTag(TAG_TITLE)->setOpacity(((m_tick-ANIMATION_MOVING_DURATION - ANIMATION_SCALING_DURATION_2)/(ANIMATION_OPACITING_DURATION))*255);
	}

	if(m_tick == ANIMATION_MOVING_DURATION + ANIMATION_SCALING_DURATION_1){
		this->getChildByTag(TAG_MENU)->setOpacity(255);
		this->getChildByTag(TAG_TITLE)->setOpacity(255);
		this->getChildByTag(TAG_MENU)->setVisible(true);
	}


	/*
	if(m_tick == ANIMATION_MOVING_DURATION + ANIMATION_SCALING_DURATION_1 + 100)
	{
		m_tick = 0;
		this->getChildByTag(TAG_BACKGROUND)->setScale(0.3f);
		this->getChildByTag(TAG_BACKGROUND)->setPosition(E::visibleWidth/2, 128);
		this->getChildByTag(TAG_NEW_GAME_BG)->setScale(0.2f);
		this->getChildByTag(TAG_NEW_GAME_BG)->setPositionY(32);
		this->getChildByTag(TAG_NEW_GAME_BG)->setOpacity(255);
		this->getChildByTag(TAG_SETTINGS_BG)->setScale(0.2f);
		this->getChildByTag(TAG_SETTINGS_BG)->setPositionY(32);
		this->getChildByTag(TAG_SETTINGS_BG)->setOpacity(255);
		this->getChildByTag(TAG_MENU)->setOpacity(0);
		this->getChildByTag(TAG_TITLE)->setOpacity(0);
		this->getChildByTag(TAG_MENU)->setVisible(false);
	}
	*/



}

void S_Welcome::menuCallback(Ref* pSender)
{
	auto pMenuItem = (MenuItem*)pSender;
	auto tag = pMenuItem->getTag();
	if(m_bClose == 0){
		m_bClose = tag;
		((Menu *)this->getChildByTag(TAG_MENU))->setEnabled(false);
		m_tick = ANIMATION_MOVING_DURATION + ANIMATION_SCALING_DURATION_1;
	}
	/**
	switch(tag)
	{
	case TAG_NEW_GAME:
	{
	m_bClose = tag;
	m_tick = ANIMATION_MOVING_DURATION + ANIMATION_SCALING_DURATION_1;
	break;
	}

	case TAG_SETTINGS:
	{
	m_bClose = tag;
	m_tick = ANIMATION_MOVING_DURATION + ANIMATION_SCALING_DURATION_1;
	break;
	}
	}
	**/
}
