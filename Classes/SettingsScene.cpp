#include "stdafx.h"
#include "SettingsScene.h"
#include "WelcomeScene.h"
#include "BallButton.h"

USING_NS_CC;
#define BTM_HEIGHT 128

#define	TAG_BTM_BG		2000
#define	TAG_SHADOW		2001
#define	TAG_OK_BG		2002
#define TAG_CC_BG		2003
#define	TAG_OKCANCEL	2004
#define	TAG_OK			2005
#define TAG_CANCEL		2006
#define	TAG_BG_TOP		2007
#define	TAG_OK_NORMAL	2008
#define	TAG_OK_SELECTED	2009
#define	TAG_CC_NORMAL	2010
#define	TAG_CC_SELECTED	2011
#define TAG_COLOR_MENU  2100

Scene* S_Settings::createScene()
{
	auto scene = Scene::create();

	auto layer = S_Settings::create();

	scene->addChild(layer);

	return scene;
}

// on "init" you need to initialize your instance
bool S_Settings::init()
{
	m_bClose = false;
	m_tick = 0;
	// super init 

	if ( !BaseScene::init((E::C100)) )
	{
		return false;
	}

	// create solid color background
	auto bg = BallButton::create(E::C50);
	bg->setScale(0.3f);
	bg->setPosition(E::visibleWidth/2, 128+(-9/15.0f)*128);
	bg->setTag(TAG_BTM_BG);
	// add the wheel to the layer
	this->addChild(bg, 0);

	// create solid color background
	auto bgTop = LayerColor::create(C4B(E::C100));
	bgTop->setTag(TAG_BG_TOP);
	bgTop->setContentSize(Size(E::visibleWidth, E::visibleHeight - BTM_HEIGHT));
	bgTop->setPosition(0, BTM_HEIGHT);
	// add the wheel to the layer
	this->addChild(bgTop, 0);

	// create the shadow
	auto shadow = Sprite::create("shadow.png");
	shadow->setScale(1.0f);
	shadow->setAnchorPoint(Vec2(0, 1));
	shadow->setScaleX(E::visibleWidth / DESIGNED_WIDTH);
	shadow->setPosition(0, BTM_HEIGHT);
	shadow->setTag(TAG_SHADOW);
	shadow->setOpacity(0);
	this->addChild(shadow, 0);




	auto okBtnBg = BallButton::create(E::C700);
	okBtnBg->setScale(0.2f);
	okBtnBg->setPosition(E::visibleWidth/2 -(okBtnBg->getContentSize().width*0.4f + 24)/2, 32-48);
	okBtnBg->setTag(TAG_OK_BG);
	this->addChild(okBtnBg, 0);

	auto sOkIcon = Sprite::create("b_ok.png");
	sOkIcon->setColor(C3B(E::C50));
	sOkIcon->setAnchorPoint(Vec2(0, 0));

	auto cancelBg = BallButton::create(E::C700);
	cancelBg->setScale(0.2f);
	cancelBg->setPosition(E::visibleWidth/2 +(cancelBg->getContentSize().width*0.4f + 24)/2, 32-48);
	cancelBg->setTag(TAG_CC_BG);
	this->addChild(cancelBg, 0);

	auto sCancelIcon = Sprite::create("b_cancel.png");
	sCancelIcon->setColor(C3B(E::C50));
	sCancelIcon->setAnchorPoint(Vec2(0, 0));


	m_OkNormal = BallButton::create(E::C700);

	m_OkSelected = BallButton::create(E::C200);

	auto OkItem = MenuItemSprite::create(
		m_OkNormal,
		m_OkSelected,
		CC_CALLBACK_1(S_Settings::menuCallback, this));

	OkItem->setScale(0.4f);
	OkItem->setTag(TAG_OK);
	OkItem->addChild(sOkIcon);

	m_CancelNormal = BallButton::create(E::C700);

	m_CancelSelected = BallButton::create(E::C200);


	auto cancelItem = MenuItemSprite::create(
		m_CancelNormal,
		m_CancelSelected,
		CC_CALLBACK_1(S_Settings::menuCallback, this));

	cancelItem->setScale(0.4f);
	cancelItem->setTag(TAG_CANCEL);
	cancelItem->addChild(sCancelIcon);


	// create menu
	auto menu = Menu::create(OkItem, cancelItem, NULL);
	menu->setPosition(Vec2(E::visibleWidth/2, 64));
	menu->alignItemsHorizontallyWithPadding(24);
	menu->setTag(TAG_OKCANCEL);
	menu->setOpacity(0);
	menu->setVisible(false);
	this->addChild(menu, 1);
	

	BallButton* CPalette[16];
	m_tempColorAccent = E::settings.colorAccent;
	for(int i = 0; i < 16; i ++){
		E::setColorAccent(i);
		CPalette[i] = BallButton::create(E::C500, E::C200, CC_CALLBACK_1(S_Settings::menuCallback, this));
		CPalette[i]->setScale(0.3f);
		CPalette[i]->setAnchorPoint(Vec2(0, 0));
		CPalette[i]->setTag(TAG_COLOR_MENU+i);
#define PALETTE_ITEM_WIDTH (80 + (E::visibleWidth - DESIGNED_WIDTH) * 0.1)
		CPalette[i]->setPosition((E::visibleWidth - PALETTE_ITEM_WIDTH * 5) / 2  + PALETTE_ITEM_WIDTH * (i % 5), E::visibleHeight * 0.9 - 64 - (80) * (i / 5));
		this->addChild(CPalette[i]);
	}
	E::setColorAccent(m_tempColorAccent);

	// set up the scheduled callbacks
	this->scheduleUpdate();

	return true;
}

#define ANI_SCALING_BG	30.0f
#define ANI_MOVING		15.0f
#define ANI_SCALING		15.0f
#define ANI_OPACITING	15.0f
#define ANI_OPAC_BACK	2.0f
void S_Settings::update( float dt )
{
	if(m_bClose){
		m_tick = m_tick - 3;
	}
	else{
		m_tick ++;
	}

	if(m_tick < -ANI_OPAC_BACK){
		Director::getInstance()->replaceScene(S_Welcome::createScene());//TransitionFadeDown::create(0.5, scene));
		return;
	}

	if(m_tick <= ANI_SCALING_BG){
		this->getChildByTag(TAG_BTM_BG)->setScale(1 + (m_tick/ANI_SCALING_BG)*3.0f);
		this->getChildByTag(TAG_SHADOW)->setOpacity((m_tick/ANI_SCALING_BG)*255);
	}
	if(m_tick <= ANI_MOVING){
		this->getChildByTag(TAG_OK_BG)->setPositionY(32-48+(m_tick/(ANI_MOVING))*(64+16));
		this->getChildByTag(TAG_CC_BG)->setPositionY(32-48+(m_tick/(ANI_MOVING))*(64+16));
	}

	if(m_tick >= ANI_MOVING && m_tick <= ANI_MOVING + ANI_SCALING){
		this->getChildByTag(TAG_OKCANCEL)->setVisible(false);
		this->getChildByTag(TAG_OK_BG)->setOpacity(255);
		this->getChildByTag(TAG_CC_BG)->setOpacity(255);
		this->getChildByTag(TAG_OKCANCEL)->setOpacity(0);
		this->getChildByTag(TAG_OK_BG)->setScale(0.2f + ((m_tick-ANI_MOVING)/(ANI_SCALING))*0.2f);
		this->getChildByTag(TAG_CC_BG)->setScale(0.2f + ((m_tick-ANI_MOVING)/(ANI_SCALING))*0.2f);
	}
	if(m_tick >= ANI_MOVING + ANI_SCALING 
		&& m_tick <= ANI_MOVING + ANI_SCALING + ANI_OPACITING){
			this->getChildByTag(TAG_OKCANCEL)->setVisible(true);
			this->getChildByTag(TAG_OK_BG)->setOpacity(255 - ((m_tick-ANI_MOVING - ANI_SCALING)/(ANI_OPACITING))*128);
			this->getChildByTag(TAG_CC_BG)->setOpacity(255 - ((m_tick-ANI_MOVING - ANI_SCALING)/(ANI_OPACITING))*128);
			this->getChildByTag(TAG_OKCANCEL)->setOpacity(((m_tick-ANI_MOVING - ANI_SCALING)/(ANI_OPACITING))*255);
	}
	/*
	if(m_tick == ANI_MOVING + 100)
	{
		this->getChildByTag(TAG_OK_BG)->setPositionY(32-48);
		this->getChildByTag(TAG_CC_BG)->setPositionY(32-48);
		this->getChildByTag(TAG_BTM_BG)->setScale(1);
		this->getChildByTag(TAG_SHADOW)->setOpacity(0);
		m_tick = 0;
	}
	*/
	m_tick ++;
}


void S_Settings::onKeyReleased(EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
	// Back button pressed
	if (keyCode == EventKeyboard::KeyCode::KEY_BACKSPACE) {
	}


}

void S_Settings::menuCallback(Ref* pSender)
{
	auto pMenuItem = (MenuItem*)pSender;
	auto tag = pMenuItem->getTag();
	if(tag >= TAG_COLOR_MENU && tag <= TAG_COLOR_MENU + 15){
		m_tempColorAccent = tag - TAG_COLOR_MENU;
		E::setColorAccent(m_tempColorAccent);
		m_OkNormal->setColor(C3B(E::C700));
		m_OkSelected->setColor(C3B(E::C200));
		m_CancelNormal->setColor(C3B(E::C700));
		m_CancelSelected->setColor(C3B(E::C200));
		this->getChildByTag(TAG_OK_BG)->setColor(C3B(E::C700));
		this->getChildByTag(TAG_CC_BG)->setColor(C3B(E::C700));
		this->getChildByTag(TAG_BG_TOP)->setColor(C3B(E::C200));
		this->getChildByTag(TAG_BTM_BG)->setColor(C3B(E::C50));
		this->setColor(C3B(E::C200));
	}
	switch(tag)
	{
	case TAG_OK:
		{
			E::settings.colorAccent = m_tempColorAccent;
			E::setColorAccent(E::settings.colorAccent);
			m_bClose = true;
			m_tick = ANI_MOVING + ANI_SCALING;
			break;
		}

	case TAG_CANCEL:
		{
			E::setColorAccent(E::settings.colorAccent);
			m_bClose = true;
			m_tick = ANI_MOVING + ANI_SCALING;
			break;
		}
	}

}
