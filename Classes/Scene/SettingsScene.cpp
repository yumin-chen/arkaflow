#include "stdafx.h"
#include "SettingsScene.h"
#include "WelcomeScene.h"
#include "UI/BallButton.h"
#include "UI/TitleBar.h"
#include "UI/BallSlider.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
#define BTM_HEIGHT		128


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
#define	TAG_TITLE_BG	2200

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
	bg->setPosition(Vec2(E::visibleWidth/2, 128+(-9/15.0f)*128));
	bg->setTag(TAG_BTM_BG);
	this->addChild(bg, 0);

	// create solid color background
	auto bgTop = LayerColor::create(C4B(E::C100));
	bgTop->setTag(TAG_BG_TOP);
	bgTop->setContentSize(Size(E::visibleWidth, E::visibleHeight - BTM_HEIGHT));
	bgTop->setPosition(0, BTM_HEIGHT);
	this->addChild(bgTop, 0);

	// create solid color background
	auto bgTitleBar = TitleBar::create(S("Settings", "游戏设置"));
	bgTitleBar->setTag(TAG_TITLE_BG);
	this->addChild(bgTitleBar, 0);

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
	okBtnBg->setPosition(Vec2(E::visibleWidth/2 -(okBtnBg->getContentSize().width*0.4f + 24)/2, 32-48));
	okBtnBg->setTag(TAG_OK_BG);
	this->addChild(okBtnBg, 0);

	auto sOkIcon = Sprite::create("b_ok.png");
	sOkIcon->setColor(C3B(E::C50));
	sOkIcon->setAnchorPoint(Vec2(0, 0));

	auto cancelBg = BallButton::create(E::C700);
	cancelBg->setScale(0.2f);
	cancelBg->setPosition(Vec2(E::visibleWidth/2 +(cancelBg->getContentSize().width*0.4f + 24)/2, 32-48));
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


	auto lbTheme = Label::createWithSystemFont(S("THEME", "配色方案"), FONT_BOLD, 24, 
				Size(128, 32), TextHAlignment::LEFT, TextVAlignment::CENTER);
	lbTheme->setPosition(24, E::visibleHeight - 128);
	lbTheme->setAnchorPoint(Vec2(0, 0));
	lbTheme->setColor(C3B(E::C900));
	this->addChild(lbTheme);
	
#define MAX_PALETTE 16
#define PALETTE_ITEM_WIDTH (80 )//+ (E::visibleWidth - DESIGNED_WIDTH) * 0.1)
	int NUM_OF_COLUMS = ((E::visibleWidth - 32) / PALETTE_ITEM_WIDTH);
	BallButton* CPalette[MAX_PALETTE];
	m_tempColorAccent = E::settings.colorAccent;
	for(int i = 0; i < MAX_PALETTE; i ++){
		E::setColorAccent(i);
		CPalette[i] = BallButton::create(E::C500, E::C200, CC_CALLBACK_1(S_Settings::menuCallback, this));
		CPalette[i]->setScale(0.3f);
		CPalette[i]->setAnchorPoint(Vec2(0, 0));
		CPalette[i]->setTag(TAG_COLOR_MENU+i);

		CPalette[i]->setPosition(Vec2((E::visibleWidth - PALETTE_ITEM_WIDTH * NUM_OF_COLUMS) / 2  + PALETTE_ITEM_WIDTH * (i % NUM_OF_COLUMS), E::visibleHeight - 128 - 80 - (80) * (i / NUM_OF_COLUMS)));
		this->addChild(CPalette[i]);
	}
	E::setColorAccent(m_tempColorAccent);

	auto lbAudio = Label::createWithSystemFont(S("AUDIO", "音量调节"), FONT_BOLD, 24, 
				Size(128, 32), TextHAlignment::LEFT, TextVAlignment::CENTER);
	lbAudio->setPosition(24, E::visibleHeight - 128 - 80 - (80) * (MAX_PALETTE / NUM_OF_COLUMS) - 64);
	lbAudio->setAnchorPoint(Vec2(0, 0));
	lbAudio->setColor(C3B(E::C900));
	this->addChild(lbAudio);

		auto lbMusicVolume = Label::createWithSystemFont(S("Music", "音乐"), FONT_MAIN, 24, 
				Size(128, 64), TextHAlignment::LEFT, TextVAlignment::CENTER);
	lbMusicVolume->setPosition(E::originX + 96 + 12, E::visibleHeight - 128 - 80 - (80) * (MAX_PALETTE / NUM_OF_COLUMS) - 64 - 40 - 32);
	lbMusicVolume->setAnchorPoint(Vec2(0, 0));
	lbMusicVolume->setColor(C3B(E::C900));
	this->addChild(lbMusicVolume);

			auto lbSoundVolume = Label::createWithSystemFont(S("Sound", "音效"), FONT_MAIN, 24, 
				Size(128, 64), TextHAlignment::LEFT, TextVAlignment::CENTER);
	lbSoundVolume->setPosition(E::originX + 96 + 12, E::visibleHeight - 128 - 80 - (80) * (MAX_PALETTE / NUM_OF_COLUMS) - 64 - 40 - 80 - 32);
	lbSoundVolume->setAnchorPoint(Vec2(0, 0));
	lbSoundVolume->setColor(C3B(E::C900));
	this->addChild(lbSoundVolume);

	auto spMusicIcon = Sprite::create("v_music.png");
	spMusicIcon->setPosition(E::originX + 64, E::visibleHeight - 128 - 80 - (80) * (MAX_PALETTE / NUM_OF_COLUMS) - 64 - 40);
	spMusicIcon->setScale(0.25f);
	this->addChild(spMusicIcon);

	auto spSoundIcon = Sprite::create("v_sound.png");
	spSoundIcon->setPosition(E::originX + 64, E::visibleHeight - 128 - 80 - (80) * (MAX_PALETTE / NUM_OF_COLUMS) - 64 - 40 - 80);
	spSoundIcon->setScale(0.25f);
	this->addChild(spSoundIcon);

	m_lbMusicVolumeValue = Label::createWithSystemFont(stdp::to_string(E::settings.musicVolume), FONT_MAIN, 24,
				Size(128, 64), TextHAlignment::LEFT, TextVAlignment::CENTER);
	m_lbMusicVolumeValue->setPosition(E::originX + 320+64+24, E::visibleHeight - 128 - 80 - (80) * (MAX_PALETTE / NUM_OF_COLUMS) - 64 - 40 - 32);
	m_lbMusicVolumeValue->setAnchorPoint(Vec2(0, 0));
	m_lbMusicVolumeValue->setColor(C3B(E::C900));
	this->addChild(m_lbMusicVolumeValue);

	m_lbSoundVolumeValue = Label::createWithSystemFont(stdp::to_string(E::settings.soundVolume), FONT_MAIN, 24, 
				Size(128, 64), TextHAlignment::LEFT, TextVAlignment::CENTER);
	m_lbSoundVolumeValue->setPosition(E::originX + 320+64+24, E::visibleHeight - 128 - 80 - (80) * (MAX_PALETTE / NUM_OF_COLUMS) - 64 - 40 - 80 - 32);
	m_lbSoundVolumeValue->setAnchorPoint(Vec2(0, 0));
	m_lbSoundVolumeValue->setColor(C3B(E::C900));
	this->addChild(m_lbSoundVolumeValue);

	m_sliderMusic = BallSlider::create();
	m_sliderMusic->setAnchorPoint(Vec2(0, 0.5));
	m_sliderMusic->setPosition(Vec2(E::originX + 192 - 16, E::visibleHeight - 128 - 80 - (80) * (MAX_PALETTE / NUM_OF_COLUMS) - 64 - 40));
	m_sliderMusic->setWidth(200);
	m_sliderMusic->setPercent(E::settings.musicVolume);
	m_sliderMusic->addEventListener([&](Ref* sender, ui::Slider::EventType type){
		switch(type){
		case ui::Slider::EventType::ON_PERCENTAGE_CHANGED:
			m_lbMusicVolumeValue->setString(stdp::to_string(((BallSlider*)sender)->getPercent()));
			CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(((BallSlider*)sender)->getPercent()/100.0f);
			break;
		}
						
	});

	this->addChild(m_sliderMusic);

	m_sliderSound = BallSlider::create();
	m_sliderSound->setAnchorPoint(Vec2(0, 0.5));
	m_sliderSound->setPosition(Vec2(E::originX + 192 - 16, E::visibleHeight - 128 - 80 - (80) * (MAX_PALETTE / NUM_OF_COLUMS) - 64 - 40 - 80));
	m_sliderSound->setWidth(200);
	m_sliderSound->setPercent(E::settings.soundVolume);
	m_sliderSound->addEventListener([&](Ref* sender, ui::Slider::EventType type){
		switch(type){
		case ui::Slider::EventType::ON_PERCENTAGE_CHANGED:
			m_lbSoundVolumeValue->setString(stdp::to_string(((BallSlider*)sender)->getPercent()));
			CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(((BallSlider*)sender)->getPercent()/100.0f);
			break;
		}
						
	});

	this->addChild(m_sliderSound);


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
		((TitleBar*)this->getChildByTag(TAG_TITLE_BG))->updateColors();
		this->setColor(C3B(E::C200));
	}
	switch(tag)
	{
	case TAG_OK:
		{
			E::settings.colorAccent = m_tempColorAccent;
			E::settings.musicVolume = m_sliderMusic->getPercent();
			E::settings.soundVolume = m_sliderSound->getPercent();
			CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(E::settings.musicVolume/100.0f);
			CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(E::settings.soundVolume/100.0f);
			E::setColorAccent(E::settings.colorAccent);
			m_bClose = true;
			m_tick = ANI_MOVING + ANI_SCALING;
			break;
		}

	case TAG_CANCEL:
		{
			E::setColorAccent(E::settings.colorAccent);
			CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(E::settings.musicVolume/100.0f);
			CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(E::settings.soundVolume/100.0f);
			m_bClose = true;
			m_tick = ANI_MOVING + ANI_SCALING;
			break;
		}
	}

}
