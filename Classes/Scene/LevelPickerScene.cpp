#include "stdafx.h"
#include "LevelPickerScene.h"
#include "MainGameScene.h"
#include "AboutScene.h"
#include "Levels/Levels.h"
#include "UI/BallButton.h"
#include "UI/TitleBar.h"
#include "UI/BallSlider.h"
#include "UI/EdgedBallButton.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
#define BTM_HEIGHT		(96+16)


#define	TAG_OK			5005
#define TAG_CANCEL		5006
#define TAG_HEART		5007
#define TAG_COLOR_MENU  5100

Scene* S_LevelPicker::createScene()
{
	auto scene = Scene::create();

	auto layer = S_LevelPicker::create();

	scene->addChild(layer);

	return scene;
}

// on "init" you need to initialize your instance
bool S_LevelPicker::init()
{
	m_bClose = 0;
	// super init 

	if ( !BaseScene::init((E::P.C50)) )
	{
		return false;
	}

	
	m_tempLevel = E::settings.currentLevel;

	m_titleBar = TitleBar::create(S("Levels", "关卡选择"));
	this->addChild(m_titleBar, 1000);

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
		CC_CALLBACK_1(S_LevelPicker::menuCallback, this));

	OkItem->setScale(0.35f);
	OkItem->setTag(TAG_OK);
	OkItem->addChild(sOkIcon);

	m_CancelNormal = BallButton::create(E::P.C700);

	m_CancelSelected = BallButton::create(E::P2.C500);


	auto cancelItem = MenuItemSprite::create(
		m_CancelNormal,
		m_CancelSelected,
		CC_CALLBACK_1(S_LevelPicker::menuCallback, this));

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


	int __x = 0;
	int __y = 0;
	if(E::originX < 192){
		__x = E::originX;
		__y = -128;
	}

	auto m_lbCurrent = Label::createWithTTF(S("CURRENT", "当前关"), FONT_BOLD, 24, 
				Size(128, 32), TextHAlignment::LEFT, TextVAlignment::CENTER);
	m_lbCurrent->setPosition(__x + 24, E::visibleHeight - 128);
	m_lbCurrent->setAnchorPoint(Vec2(0, 0));
	m_lbCurrent->setColor(C3B(E::P.C900));
	this->addChild(m_lbCurrent);
	
		auto m_currentBall = BallButton::create(E::P.C500, E::P.C200, CC_CALLBACK_1(S_LevelPicker::menuCallback, this));
		m_currentBall->setScale(0.3f);
		m_currentBall->setAnchorPoint(Vec2(0, 0));
		m_lbLevel = Label::createWithTTF(stdp::to_string(E::settings.currentLevel), FONT_BOLD, 128, 
			m_currentBall->getContentSize(), TextHAlignment::CENTER, TextVAlignment::CENTER);
		m_lbLevel->setPosition(m_currentBall->getContentSize()/2);
		//lbLevel->setAnchorPoint(Vec2(0.5, 0.5));
		m_lbLevel->enableShadow(Color4B(0, 0, 0, 128), Size(8, -8));
		m_lbLevel->setColor(Color3B(255, 255, 255));
		m_currentBall->addChild(m_lbLevel);
		m_currentBall->setPosition(Vec2(__x + 32, E::visibleHeight - 128 - 80));
		this->addChild(m_currentBall);

	auto m_lbLevels = Label::createWithTTF(S("LEVELS", "选择关"), FONT_BOLD, 24, 
				Size(128, 32), TextHAlignment::LEFT, TextVAlignment::CENTER);
	m_lbLevels->setPosition(E::originX + 24, E::visibleHeight - 128 + __y);
	m_lbLevels->setAnchorPoint(Vec2(0, 0));
	m_lbLevels->setColor(C3B(E::P.C900));
	this->addChild(m_lbLevels);
#define MAX_PALETTE 16
#define PALETTE_ITEM_WIDTH (80 )//+ (E::visibleWidth - DESIGNED_WIDTH) * 0.1)
	int NUM_OF_COLUMS = 5;
	BallButton* CPalette[MAX_LEVEL];
	ColorPalette tempPalette;
	for(int i = 0; i < MAX_LEVEL; i ++){
		E::getColorPaletteFromID(tempPalette, i % MAX_PALETTE);
		CPalette[i] = BallButton::create(tempPalette.C500, tempPalette.C200, CC_CALLBACK_1(S_LevelPicker::menuCallback, this));
		CPalette[i]->setScale(0.3f);
		CPalette[i]->setAnchorPoint(Vec2(0, 0));
		CPalette[i]->setTag(TAG_COLOR_MENU+i);
		auto lbLevel = Label::createWithTTF(stdp::to_string(i+1), FONT_BOLD, 128, 
			CPalette[i]->getContentSize(), TextHAlignment::CENTER, TextVAlignment::CENTER);
		lbLevel->setPosition(CPalette[i]->getContentSize()/2);
		//lbLevel->setAnchorPoint(Vec2(0.5, 0.5));
		lbLevel->enableShadow(Color4B(0, 0, 0, 128), Size(8, -8));
		lbLevel->setColor(Color3B(255, 255, 255));
		CPalette[i]->addChild(lbLevel);
		CPalette[i]->setPosition(Vec2((E::visibleWidth - PALETTE_ITEM_WIDTH * NUM_OF_COLUMS) / 2  + PALETTE_ITEM_WIDTH * (i % NUM_OF_COLUMS), __y + E::visibleHeight - 128 - 80 - (80) * (i / NUM_OF_COLUMS)));
		this->addChild(CPalette[i]);
	}

	runAnimations(false);

	return true;
}

void S_LevelPicker::runAnimations(bool isReversed){
	auto cbClose = CallFunc::create([this](){
		if(m_bClose == 1){
			Director::getInstance()->replaceScene(S_MainGame::createScene());
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

void S_LevelPicker::menuCallback(Ref* pSender)
{
	auto pMenuItem = (MenuItem*)pSender;
	auto tag = pMenuItem->getTag();
	if(tag >= TAG_COLOR_MENU && tag < TAG_COLOR_MENU + MAX_LEVEL){
		if(tag - TAG_COLOR_MENU + 1 > E::settings.unlockedLevel)
			return;
		m_tempLevel = tag - TAG_COLOR_MENU + 1;
		m_lbLevel->setString(stdp::to_string(m_tempLevel));
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
	}

}

 void S_LevelPicker::onKeyEvent(EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
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

void S_LevelPicker::_ok(){
	E::settings.currentLevel = m_tempLevel;
	m_bClose = 1;
	runAnimations(true);
}

void S_LevelPicker::_cancel(){
	m_tempLevel = E::settings.currentLevel;
	m_lbLevel->setString(stdp::to_string(m_tempLevel));
	m_bClose = 1;
	runAnimations(true);
}
