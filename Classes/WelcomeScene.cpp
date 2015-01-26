#include "WelcomeScene.h"
#include "MainGameScene.h"

USING_NS_CC;

Scene* Welcome::createScene()
{
	auto scene = Scene::create();

	auto layer = Welcome::create();


	scene->addChild(layer);

	return scene;
}


bool Welcome::init()
{
	m_tick = 0;
	m_bClose = false;
	// super init 
	if ( !LayerColor::initWithColor(C4B(COLOR_200)) )
	{
		return false;
	}


	this->setScale(E::scale);
	this->setContentSize(Size(E::visibleWidth, E::visibleHeight));
	this->setAnchorPoint(Vec2(0, 0));

	// create solid color background
	auto bg = Sprite::create("ball.png");
	bg->setScale(0.3f);
	bg->setPosition(E::visibleWidth/2, 128);
	bg->setColor(C3B(COLOR_50));
	bg->setTag(TAG_BACKGROUND);
	// add the wheel to the layer
	this->addChild(bg, 0);

	// create solid color background
	auto newGameBg = Sprite::create("ball.png");
	newGameBg->setScale(0.3f);
	newGameBg->setPosition(E::visibleWidth/2, 32);
	newGameBg->setColor(C3B(COLOR_700));
	newGameBg->setTag(TAG_NEW_GAME_BG);
	// add the wheel to the layer
	this->addChild(newGameBg, 0);


	// create title sprite
	auto title = Sprite::create("title.png");
	// position the sprite on the center of the screen
	title->setPosition(Vec2(E::visibleWidth/2 + 206/4, E::visibleHeight/2 + 96 - 234/4));
	title->setScale(0.6f);
	title->setTag(TAG_TITLE);
	title->setOpacity(0);
	// add the sprite as a child to this layer
	this->addChild(title, 0);

	// create the normal sprite for the button NEW GAME
	auto sNewNormal = Sprite::create("ball.png");
	sNewNormal->setColor(C3B(COLOR_700));

	// create the normal sprite for the button NEW GAME
	auto sNewSelected = Sprite::create("ball.png");
	sNewSelected->setColor(C3B(COLOR_200));

	// create the button for new game
	auto newGame = MenuItemSprite::create(
		sNewNormal,
		sNewSelected,
		CC_CALLBACK_1(Welcome::menuCallback, this));

	newGame->setScale(0.6f);
	newGame->setTag(TAG_NEW_GAME);


	// create menu
	auto menu = Menu::create(newGame, NULL);
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
#define ANIMATION_OPAC_BACK_DURATION	7.0f

void Welcome::update( float dt ) 
{
	if(m_bClose){
		m_tick = m_tick - 1;
	}
	else{
		m_tick ++;
	}

	if(m_tick < 0 && m_tick >= -ANIMATION_OPAC_BACK_DURATION){
		this->getChildByTag(TAG_NEW_GAME_BG)->setOpacity(255-(m_tick/(-ANIMATION_OPAC_BACK_DURATION))*255);
	}

	if(m_tick < -ANIMATION_OPAC_BACK_DURATION){
		//m_tick = -ANIMATION_OPAC_BACK_DURATION;
		auto scene = MainGame::createScene();
		Director::getInstance()->replaceScene(scene);//TransitionFadeDown::create(0.5, scene));
		return;
	}

	if(m_tick <= ANIMATION_MOVING_DURATION){
		this->getChildByTag(TAG_BACKGROUND)->setPositionY(128+(m_tick/(ANIMATION_MOVING_DURATION))*128);
		this->getChildByTag(TAG_NEW_GAME_BG)->setPositionY(32+(m_tick/(ANIMATION_MOVING_DURATION))*128);
	}
	if(m_tick >= ANIMATION_MOVING_DURATION && m_tick <= ANIMATION_MOVING_DURATION + ANIMATION_SCALING_DURATION_1){
		this->getChildByTag(TAG_BACKGROUND)->setPositionY(256+((m_tick-ANIMATION_MOVING_DURATION)/(ANIMATION_SCALING_DURATION_1))*128);
		this->getChildByTag(TAG_BACKGROUND)->setScale(0.3f + ((m_tick-ANIMATION_MOVING_DURATION)/(ANIMATION_SCALING_DURATION_1))*4.0f);
	}
	if(m_tick >= ANIMATION_MOVING_DURATION && m_tick <= ANIMATION_MOVING_DURATION + ANIMATION_SCALING_DURATION_2){
		this->getChildByTag(TAG_MENU)->setVisible(false);
		this->getChildByTag(TAG_NEW_GAME_BG)->setOpacity(255);
		this->getChildByTag(TAG_MENU)->setOpacity(0);
		this->getChildByTag(TAG_TITLE)->setOpacity(0);
		this->getChildByTag(TAG_NEW_GAME_BG)->setScale(0.3f + ((m_tick-ANIMATION_MOVING_DURATION)/(ANIMATION_SCALING_DURATION_2))*0.3f);
	}

	if(m_tick >= ANIMATION_MOVING_DURATION + ANIMATION_SCALING_DURATION_2 
		&& m_tick <= ANIMATION_MOVING_DURATION + ANIMATION_SCALING_DURATION_2 + ANIMATION_OPACITING_DURATION){
			this->getChildByTag(TAG_MENU)->setVisible(true);
			this->getChildByTag(TAG_NEW_GAME_BG)->setOpacity(255 - ((m_tick-ANIMATION_MOVING_DURATION - ANIMATION_SCALING_DURATION_2)/(ANIMATION_OPACITING_DURATION))*128);
			this->getChildByTag(TAG_MENU)->setOpacity(((m_tick-ANIMATION_MOVING_DURATION - ANIMATION_SCALING_DURATION_2)/(ANIMATION_OPACITING_DURATION))*255);
			this->getChildByTag(TAG_TITLE)->setOpacity(((m_tick-ANIMATION_MOVING_DURATION - ANIMATION_SCALING_DURATION_2)/(ANIMATION_OPACITING_DURATION))*255);
	}

	if(m_tick == ANIMATION_MOVING_DURATION + ANIMATION_SCALING_DURATION_1){
		this->getChildByTag(TAG_MENU)->setOpacity(255);
		this->getChildByTag(TAG_TITLE)->setOpacity(255);
		this->getChildByTag(TAG_MENU)->setVisible(true);
	}



	if(m_tick == ANIMATION_MOVING_DURATION + ANIMATION_SCALING_DURATION_1 + 100)
	{
		m_tick = 0;
		this->getChildByTag(TAG_BACKGROUND)->setScale(0.3f);
		this->getChildByTag(TAG_BACKGROUND)->setPosition(E::visibleWidth/2, 128);
		this->getChildByTag(TAG_NEW_GAME_BG)->setScale(0.3f);
		this->getChildByTag(TAG_NEW_GAME_BG)->setPosition(E::visibleWidth/2, 32);
		this->getChildByTag(TAG_NEW_GAME_BG)->setOpacity(255);
		this->getChildByTag(TAG_MENU)->setOpacity(0);
		this->getChildByTag(TAG_TITLE)->setOpacity(0);
		this->getChildByTag(TAG_MENU)->setVisible(false);
	}



}

void Welcome::menuCallback(Ref* pSender)
{
	auto pMenuItem = (MenuItem*)pSender;
	auto tag = pMenuItem->getTag();
	switch(tag)
	{
	case TAG_NEW_GAME:
		{
			m_bClose = true;
			m_tick = ANIMATION_MOVING_DURATION + ANIMATION_SCALING_DURATION_1;
			//auto scene = MainGame::createScene();
			//Director::getInstance()->replaceScene(scene);//TransitionFadeDown::create(0.5, scene));
			break;
		}
	}
}
