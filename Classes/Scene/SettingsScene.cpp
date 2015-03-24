#include "stdafx.h"
#include "SettingsScene.h"
#include "WelcomeScene.h"
#include "AboutScene.h"
#include "UI/BallButton.h"
#include "UI/TitleBar.h"
#include "UI/BallSlider.h"
#include "UI/EdgedBallButton.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
#define BTM_HEIGHT		(96+16)


#define	TAG_OK			2005
#define TAG_CANCEL		2006
#define TAG_HEART		2007
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
	m_bClose = 0;
	// super init 

	if ( !BaseScene::init((E::P.C50)) )
	{
		return false;
	}

	m_titleBar = TitleBar::create(S("Settings", "游戏设置"));
	this->addChild(m_titleBar, 1000);

	m_heartBtn = EdgedBallButton::create(CC_CALLBACK_1(S_Settings::menuCallback, this));
	m_heartBtn->setScale(0.3f);
	m_heartBtn->setPosition(Vec2(E::visibleWidth - 48, 40));
	m_heartBtn->setTag(TAG_HEART);
	m_titleBar->addChild(m_heartBtn, 1000);

	m_heartIcon = Sprite::create("ui/ob_heart.png");
	m_heartIcon->setScale(0.9f);
	m_heartIcon->setAnchorPoint(Vec2(0.5, 0.5));
	m_heartIcon->setPosition(m_heartBtn->getContentSize() / 2);
	m_heartBtn->addChild(m_heartIcon, 1000);
	m_heartIcon->setColor(C3B(E::P.C700));
	m_heartIcon->runAction(RepeatForever::create(Sequence::create(TintTo::create(0.5f, C3B(E::P.A400)), TintTo::create(0.5f, C3B(E::P.C700)), nullptr)));

	// create solid color background
	m_btmBg = BallButton::create(E::P.C100);
	m_btmBg->setScale(0.3f);
	m_btmBg->setPosition(Vec2(E::visibleWidth/2, 128+(-9/15.0f)*128));
//	m_btmBg->setTag(TAG_BTM_BG);
	this->addChild(m_btmBg, 0);

	// create solid color background
	m_bgTop = LayerColor::create(C4B(E::P.C50));
//	m_bgTop->setTag(TAG_BG_TOP);
	m_bgTop->setContentSize(Size(E::visibleWidth, E::visibleHeight - BTM_HEIGHT));
	m_bgTop->setPosition(0, BTM_HEIGHT);
	this->addChild(m_bgTop, 0);

	// create the shadow
	m_shadow = Sprite::create("ui/shadow.png");
	m_shadow->setScale(1.0f);
	m_shadow->setAnchorPoint(Vec2(0, 1));
	m_shadow->setScaleX(E::visibleWidth / DESIGNED_WIDTH);
	m_shadow->setPosition(0, BTM_HEIGHT);
//	m_shadow->setTag(TAG_SHADOW);
	m_shadow->setOpacity(0);
	this->addChild(m_shadow, 0);

	m_okBtnBg = BallButton::create(E::P.C700);
	m_okBtnBg->setScale(0.2f);
	m_okBtnBg->setPosition(Vec2(E::visibleWidth/2 -(m_okBtnBg->getContentSize().width*0.35f + 24)/2, -16));
	this->addChild(m_okBtnBg, 0);

	auto sOkIcon = Sprite::create("ui/b_ok.png");
	sOkIcon->setColor(C3B(E::P.C50));
	sOkIcon->setAnchorPoint(Vec2(0, 0));

	m_cancelBg = BallButton::create(E::P.C700);
	m_cancelBg->setScale(0.2f);
	m_cancelBg->setPosition(Vec2(E::visibleWidth/2 +(m_cancelBg->getContentSize().width*0.35f + 24)/2, -16));
	this->addChild(m_cancelBg, 0);

	auto sCancelIcon = Sprite::create("ui/b_cancel.png");
	sCancelIcon->setColor(C3B(E::P.C50));
	sCancelIcon->setAnchorPoint(Vec2(0, 0));

	m_OkNormal = BallButton::create(E::P.C700);

	m_OkSelected = BallButton::create(E::P2.C500);

	auto OkItem = MenuItemSprite::create(
		m_OkNormal,
		m_OkSelected,
		CC_CALLBACK_1(S_Settings::menuCallback, this));

	OkItem->setScale(0.35f);
	OkItem->setTag(TAG_OK);
	OkItem->addChild(sOkIcon);

	m_CancelNormal = BallButton::create(E::P.C700);

	m_CancelSelected = BallButton::create(E::P2.C500);


	auto cancelItem = MenuItemSprite::create(
		m_CancelNormal,
		m_CancelSelected,
		CC_CALLBACK_1(S_Settings::menuCallback, this));

	cancelItem->setScale(0.35f);
	cancelItem->setTag(TAG_CANCEL);
	cancelItem->addChild(sCancelIcon);


	// create menu
	m_menu = Menu::create(OkItem, cancelItem, NULL);
	m_menu->setPosition(Vec2(E::visibleWidth/2, 64 + 4 -16));
	m_menu->alignItemsHorizontallyWithPadding(24);
	m_menu->setEnabled(false);
	m_menu->setOpacity(0);
	this->addChild(m_menu, 1);


	m_lbTheme = Label::createWithTTF(S("THEME", "配色方案"), FONT_BOLD, 24, 
				Size(128, 32), TextHAlignment::LEFT, TextVAlignment::CENTER);
	m_lbTheme->setPosition(24, E::visibleHeight - 128);
	m_lbTheme->setAnchorPoint(Vec2(0, 0));
	m_lbTheme->setColor(C3B(E::P.C900));
	this->addChild(m_lbTheme);
	
#define MAX_PALETTE 17
#define PALETTE_ITEM_WIDTH (80 )//+ (E::visibleWidth - DESIGNED_WIDTH) * 0.1)
	int NUM_OF_COLUMS = ((E::visibleWidth - 32) / PALETTE_ITEM_WIDTH);
	BallButton* CPalette[MAX_PALETTE];
	m_tempColorAccent = E::settings.colorAccent;
	ColorPalette tempPalette;
	for(int i = 0; i < MAX_PALETTE; i ++){
		E::getColorPaletteFromID(tempPalette, i == 16? m_tempColorAccent: i);
		CPalette[i] = BallButton::create(i == 16? 0xFFFFFF: tempPalette.C500, tempPalette.C200, CC_CALLBACK_1(S_Settings::menuCallback, this));
		CPalette[i]->setScale(0.3f);
		CPalette[i]->setAnchorPoint(Vec2(0, 0));
		CPalette[i]->setTag(TAG_COLOR_MENU+i);
		if(i == 16){
			CPalette[i]->setTexture("ui/colorful.png");
		}

		CPalette[i]->setPosition(Vec2((E::visibleWidth - PALETTE_ITEM_WIDTH * NUM_OF_COLUMS) / 2  + PALETTE_ITEM_WIDTH * (i % NUM_OF_COLUMS), E::visibleHeight - 128 - 80 - (80) * (i / NUM_OF_COLUMS)));
		this->addChild(CPalette[i]);
	}

	m_lbAudio = Label::createWithTTF(S("AUDIO", "音量调节"), FONT_BOLD, 24, 
				Size(128, 32), TextHAlignment::LEFT, TextVAlignment::CENTER);
	m_lbAudio->setPosition(24, E::visibleHeight - 128 - 80 - (80) * (MAX_PALETTE / NUM_OF_COLUMS) - 64);
	m_lbAudio->setAnchorPoint(Vec2(0, 0));
	m_lbAudio->setColor(C3B(E::P.C900));
	this->addChild(m_lbAudio);

	m_lbMusicVolume = Label::createWithTTF(S("Music", "音乐"), FONT_MAIN, 24, 
				Size(128, 64), TextHAlignment::LEFT, TextVAlignment::CENTER);
	m_lbMusicVolume->setPosition(E::originX + 96 + 12, E::visibleHeight - 128 - 80 - (80) * (MAX_PALETTE / NUM_OF_COLUMS) - 64 - 40 - 32);
	m_lbMusicVolume->setAnchorPoint(Vec2(0, 0));
	m_lbMusicVolume->setColor(C3B(E::P.C900));
	this->addChild(m_lbMusicVolume);

	m_lbSoundVolume = Label::createWithTTF(S("Sound", "音效"), FONT_MAIN, 24, 
				Size(128, 64), TextHAlignment::LEFT, TextVAlignment::CENTER);
	m_lbSoundVolume->setPosition(E::originX + 96 + 12, E::visibleHeight - 128 - 80 - (80) * (MAX_PALETTE / NUM_OF_COLUMS) - 64 - 40 - 80 - 32);
	m_lbSoundVolume->setAnchorPoint(Vec2(0, 0));
	m_lbSoundVolume->setColor(C3B(E::P.C900));
	this->addChild(m_lbSoundVolume);

	m_spMusicBtn = EdgedBallButton::create(CC_CALLBACK_1(S_Settings::menuCallback, this));
	m_spMusicBtn->setPosition(E::originX + 64, E::visibleHeight - 128 - 80 - (80) * (MAX_PALETTE / NUM_OF_COLUMS) - 64 - 40);
#define TAG_MUSIC_BTN	2020
	m_spMusicBtn->setTag(TAG_MUSIC_BTN);
	m_spMusicBtn->setScale(0.3f);
	this->addChild(m_spMusicBtn);

	m_spMusicIcon = Sprite::create(E::settings.musicEnabled? "ui/ob_music_on.png": "ui/ob_music_off.png");
	m_spMusicIcon->setPosition(Vec2(128, 128));
	m_spMusicIcon->setScale(0.9f);
	m_spMusicIcon->setColor(C3B(E::P.C700));
	m_spMusicBtn->addChild(m_spMusicIcon);

	m_spSoundBtn = EdgedBallButton::create(CC_CALLBACK_1(S_Settings::menuCallback, this));
	m_spSoundBtn->setPosition(E::originX + 64, E::visibleHeight - 128 - 80 - (80) * (MAX_PALETTE / NUM_OF_COLUMS) - 64 - 40 - 80);
#define TAG_SOUND_BTN	2021
	m_spSoundBtn->setTag(TAG_SOUND_BTN);
	m_spSoundBtn->setScale(0.3f);
	this->addChild(m_spSoundBtn);

	m_spSoundIcon = Sprite::create(E::settings.soundEnabled? "ui/ob_notif_on.png": "ui/ob_notif_off.png");
	m_spSoundIcon->setPosition(Vec2(128, 128));
	m_spSoundIcon->setScale(0.9f);
	m_spSoundIcon->setColor(C3B(E::P.C700));
	m_spSoundBtn->addChild(m_spSoundIcon);

	m_lbMusicVolumeValue = Label::createWithTTF(stdp::to_string(E::settings.musicVolume), FONT_MAIN, 24,
				Size(128, 64), TextHAlignment::LEFT, TextVAlignment::CENTER);
	m_lbMusicVolumeValue->setPosition(E::originX + 320+64+24, E::visibleHeight - 128 - 80 - (80) * (MAX_PALETTE / NUM_OF_COLUMS) - 64 - 40 - 32);
	m_lbMusicVolumeValue->setAnchorPoint(Vec2(0, 0));
	m_lbMusicVolumeValue->setColor(C3B(E::P.C900));
	this->addChild(m_lbMusicVolumeValue);

	m_lbSoundVolumeValue = Label::createWithTTF(stdp::to_string(E::settings.soundVolume), FONT_MAIN, 24, 
				Size(128, 64), TextHAlignment::LEFT, TextVAlignment::CENTER);
	m_lbSoundVolumeValue->setPosition(E::originX + 320+64+24, E::visibleHeight - 128 - 80 - (80) * (MAX_PALETTE / NUM_OF_COLUMS) - 64 - 40 - 80 - 32);
	m_lbSoundVolumeValue->setAnchorPoint(Vec2(0, 0));
	m_lbSoundVolumeValue->setColor(C3B(E::P.C900));
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

	runAnimations(false);

	return true;
}

void S_Settings::runAnimations(bool isReversed){
	auto cbClose = CallFunc::create([this](){
		if(m_bClose == 1){
			Director::getInstance()->replaceScene(S_Welcome::createScene());
			m_bClose = 0;
		}else 
		if(m_bClose == 2){
			E::setColorAccent(E::settings.colorAccent);
			CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(E::settings.musicVolume/100.0f);
			CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(E::settings.soundVolume/100.0f);
			Director::getInstance()->replaceScene(S_About::createScene(1));
			m_bClose = 0;
		}
	});

	auto moveBy = MoveBy::create(0.2f , Vec2(0, 64 + 4));
	auto scaleBy = ScaleBy::create(0.2f , 0.35f/0.2f);
	auto fadeOut = FadeOut::create(0.2f);
	auto seq = Sequence::create(cbClose, moveBy, scaleBy, fadeOut, nullptr);
	m_okBtnBg->runAction(isReversed? seq->reverse(): seq);
	m_cancelBg->runAction(isReversed? seq->reverse(): seq->clone());

	
	auto menuDelay = DelayTime::create(0.4f);
	auto cbMenuDisable = CallFunc::create([this](){m_menu->setEnabled(false);});
	auto cbMenuEnable = CallFunc::create([this](){m_menu->setEnabled(true);});
	Sequence* menuSeq;
	if(isReversed){menuSeq = Sequence::create(cbMenuDisable, FadeOut::create(0.2f), nullptr);}
	else{menuSeq = Sequence::create(menuDelay, FadeIn::create(0.2f), cbMenuEnable, nullptr);}
	m_menu->runAction(menuSeq);
	
	if(isReversed){m_shadow->runAction(FadeOut::create(0.6f));}
	else{m_shadow->runAction(FadeIn::create(0.6f));}

	auto btmScaleBy = ScaleBy::create(0.6f , 16.0f);
	m_btmBg->runAction(isReversed? btmScaleBy->reverse(): btmScaleBy);

	if(isReversed){
		m_titleBar->fadeOut();
	}

}

void S_Settings::menuCallback(Ref* pSender)
{
	auto pMenuItem = (MenuItem*)pSender;
	auto tag = pMenuItem->getTag();
	if(tag >= TAG_COLOR_MENU && tag <= TAG_COLOR_MENU + 16){
		m_tempColorAccent = tag - TAG_COLOR_MENU;
		E::setColorAccent(m_tempColorAccent);
		m_OkNormal->setColor(C3B(E::P.C700));
		m_OkSelected->setColor(C3B(E::P2.C500));
		m_CancelNormal->setColor(C3B(E::P.C700));
		m_CancelSelected->setColor(C3B(E::P2.C500));
		m_okBtnBg->setColor(C3B(E::P.C700));
		m_cancelBg->setColor(C3B(E::P.C700));
		m_bgTop->setColor(C3B(E::P.C50));
		m_btmBg->setColor(C3B(E::P.C100));
		m_lbTheme->setColor(C3B(E::P.C900));
		m_lbAudio->setColor(C3B(E::P.C900));
		m_lbMusicVolume->setColor(C3B(E::P.C900));
		m_lbSoundVolume->setColor(C3B(E::P.C900));
		m_lbMusicVolumeValue->setColor(C3B(E::P.C900));
		m_lbSoundVolumeValue->setColor(C3B(E::P.C900));
		m_spMusicIcon->setColor(C3B(E::P.C700));
		m_spSoundIcon->setColor(C3B(E::P.C700));
		m_spMusicBtn->updateColors();
		m_spSoundBtn->updateColors();
		m_titleBar->updateColors();
		m_sliderMusic->updateColors();
		m_sliderSound->updateColors();
		m_heartBtn->updateColors();
		m_heartIcon->setColor(C3B(E::P.C700));
		m_heartIcon->stopAllActions();
		m_heartIcon->runAction(RepeatForever::create(Sequence::create(TintTo::create(0.5f, C3B(E::P.A400)), TintTo::create(0.5f, C3B(E::P.C700)), nullptr)));
		this->setColor(C3B(E::P.C200));
	}
	switch(tag)
	{
	case TAG_OK:
		{
			putEmitter(m_okBtnBg->getPosition());
			_ok();
			break;
		}

	case TAG_CANCEL:
		{
			putEmitter(m_cancelBg->getPosition());
			_cancel();
			break;
		}
	case TAG_MUSIC_BTN:
		{
			E::settings.musicEnabled = !E::settings.musicEnabled;
			m_spMusicIcon->setTexture(E::settings.musicEnabled? "ui/ob_music_on.png": "ui/ob_music_off.png");
			if(!E::settings.musicEnabled){
				CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
			}else{
				E::playBgMusic();
			}
			break;
		}
	case TAG_SOUND_BTN:
		{
			E::settings.soundEnabled = !E::settings.soundEnabled;
			m_spSoundIcon->setTexture(E::settings.soundEnabled? "ui/ob_notif_on.png": "ui/ob_notif_off.png");
			if(!E::settings.musicEnabled){
				CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
			}	
			break;
		}
	case TAG_HEART:
		{
			m_bClose = 2;
			runAnimations(true);
			break;
		}
	}

}

 void S_Settings::onKeyEvent(EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
	// Back button pressed
	if (keyCode == EventKeyboard::KeyCode::KEY_BACK || keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {
		_cancel();
	}

	// Enter key pressed
	if (keyCode == EventKeyboard::KeyCode::KEY_KP_ENTER || keyCode == EventKeyboard::KeyCode::KEY_ENTER) {
		_ok();
	}

}

void S_Settings::_ok(){
				E::settings.colorAccent = m_tempColorAccent;
			E::settings.musicVolume = m_sliderMusic->getPercent();
			E::settings.soundVolume = m_sliderSound->getPercent();
	auto ud = UserDefault::getInstance();
	ud->setIntegerForKey(UD_COLOR_ACCENT, E::settings.colorAccent);
	ud->setIntegerForKey(UD_MUSIC_VOLUME, E::settings.musicVolume);
	ud->setIntegerForKey(UD_SOUND_VOLUME, E::settings.soundVolume);
			CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(E::settings.musicVolume/100.0f);
			CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(E::settings.soundVolume/100.0f);
			E::setColorAccent(E::settings.colorAccent);
			m_bClose = 1;			
			runAnimations(true);
}

void S_Settings::_cancel(){
			E::setColorAccent(E::settings.colorAccent);
			CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(E::settings.musicVolume/100.0f);
			CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(E::settings.soundVolume/100.0f);
			m_bClose = 1;
			runAnimations(true);
			//m_tick = ANI_MOVING + ANI_SCALING;
}
