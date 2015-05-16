#include "stdafx.h"
#include "WelcomeScene.h"
#include "MainGameScene.h"
#include "SettingsScene.h"
#include "../Element/Triangle.h"
#include "../Element/Ring.h"
#include "../UI/BallButton.h"
#include "../UI/BallDialog.h"

USING_NS_CC;


#define TAG_NEW_GAME		25
#define	TAG_SETTINGS		31
/*
#define TAG_BACKGROUND		27
#define TAG_NEW_GAME_BG		28
#define	TAG_SETTINGS_BG		32
*/

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
	if ( !BaseScene::init((E::P.C50)))
	{
		return false;
	}
	m_bClose = 0;

	// create solid color background
	m_bg = BallButton::create(E::P.C100);
	m_bg->setScale(0.3f);
	m_bg->setPosition(Vec2(E::visibleWidth/2, 96));
	//bg->setTag(TAG_BACKGROUND);
	this->addChild(m_bg, 0);

	m_tri = Triangle::create();
	m_tri->setScale(0.6 + rand() % 40 / 100);
	m_tri->setRotation(rand());
	m_tri->setOpacity(0);
	this->addChild(m_tri);

	m_ring = Ring::create();
	m_ring->setScale(0.6 + rand() % 40 / 100);
	m_ring->setOpacity(0);
	this->addChild(m_ring);

	if(rand() % 2 == 0){
		m_tri->setPosition(rand() % 160, E::originY + DESIGNED_HEIGHT / 2 - 96 - rand() % 160);
		m_ring->setPosition(E::visibleWidth - rand() % 160, E:: originY + DESIGNED_HEIGHT / 2 + 256 + rand() % 160);	
	}
	else{
		m_ring->setPosition(rand() % 160, E::originY + DESIGNED_HEIGHT / 2 - 96 - rand() % 160);
		m_tri->setPosition(E::visibleWidth  - rand() % 160, E:: originY + DESIGNED_HEIGHT / 2 + 256 + rand() % 160);	
	}

	m_newGameBg = BallButton::create(E::P.C700);
	m_newGameBg->setScale(0.2f);
	m_newGameBg->setPosition(Vec2(E::visibleWidth/2 -(m_newGameBg->getContentSize().width*0.5f + 24)/2, 0));
	//newGameBg->setTag(TAG_NEW_GAME_BG);
	this->addChild(m_newGameBg, 0);

	auto sNewIcon = Sprite::create("ui/b_newgame.png");
	sNewIcon->setColor(C3B(E::P.C50));
	sNewIcon->setAnchorPoint(Vec2(0, 0));
	//newGameBg->addChild(sNewIcon);

	m_settingsBg = BallButton::create(E::P.C700);
	m_settingsBg->setScale(0.2f);
	m_settingsBg->setPosition(Vec2(E::visibleWidth/2 +(m_settingsBg->getContentSize().width*0.5f + 24)/2, 0));
	//settingsBg->setTag(TAG_SETTINGS_BG);
	this->addChild(m_settingsBg, 0);

	auto sSettingsIcon = Sprite::create("ui/b_settings.png");
	sSettingsIcon->setColor(C3B(E::P.C50));
	sSettingsIcon->setAnchorPoint(Vec2(0, 0));
	//settingsBg->addChild(sSettingsIcon);

	std::string title1_str = "";
	std::string title2_str = "";
	// create title
	if(strcmp(GAME_TITLE, "Arkaflow") == 0){
		if(E::visibleWidth > E::visibleHeight)
		{
			title2_str = GAME_TITLE;
		}
		else
		{
			title1_str = "Arka";
			title2_str = "flow"; 
		}
	}else if(strcmp(GAME_TITLE, "溜溜的圈圈") == 0){
		if(E::visibleWidth > E::visibleHeight)
		{
			title2_str = GAME_TITLE;
		}
		else
		{
			title1_str = "溜溜的";
			title2_str = "圈圈";
		}
	}

	m_title = Label::createWithTTF(title1_str, FONT_BOLD, 128,
				Size(E::visibleWidth, 256), TextHAlignment::CENTER, TextVAlignment::CENTER);
	m_title->setPosition(Vec2(E::visibleWidth/2 - 48, E::visibleHeight/2 + 192));
	//m_title->enableShadow(Color4B(0, 0, 0, 128), Size(2, -2));
	m_title->setColor(C3B(E::P.C900));
	m_title->setOpacity(0);
	this->addChild(m_title, 0);

	m_title2 = Label::createWithTTF(title2_str, FONT_BOLD, 128,
				Size(E::visibleWidth, 256), TextHAlignment::CENTER, TextVAlignment::CENTER);
	m_title2->setPosition(Vec2(E::visibleWidth/2 + 32 + 64 * int(E::language == 1), E::visibleHeight/2 + 64));
	m_title2->setColor(C3B(E::P.C900));
	m_title2->setOpacity(0);
	this->addChild(m_title2, 0);




	auto newGame = MenuItemSprite::create(
		BallButton::create(E::P.C700),
		BallButton::create(E::P2.C500),
		CC_CALLBACK_1(S_Welcome::menuCallback, this));

	newGame->setScale(0.5f);
	newGame->setTag(TAG_NEW_GAME);
	newGame->addChild(sNewIcon);

	auto settings = MenuItemSprite::create(
		BallButton::create(E::P.C700),
		BallButton::create(E::P2.C500),
		CC_CALLBACK_1(S_Welcome::menuCallback, this));

	settings->setScale(0.5f);
	settings->setTag(TAG_SETTINGS);
	settings->addChild(sSettingsIcon);

	// create menu
	m_menu = Menu::create(newGame, settings, NULL);
	m_menu->setPosition(Vec2::ZERO);
	m_menu->setPosition(Vec2(E::visibleWidth/2, 32 + 128));
	m_menu->alignItemsHorizontallyWithPadding(24);
	m_menu->setOpacity(0);
	m_menu->setEnabled(false);
	this->addChild(m_menu, 1);

	// animations
	runAnimations(false);

	return true;
}

void S_Welcome::runAnimations(bool isReversed){
	auto cbScene = CallFunc::create([this](){
		if(m_bClose == 0){
			return;
		}
		Scene *scene;
		switch(m_bClose){
		case TAG_NEW_GAME:
			scene = S_MainGame::createScene();
			break;
		case TAG_SETTINGS:
			scene = S_Settings::createScene();
			break;
		}
		Director::getInstance()->replaceScene(scene);//TransitionFadeDown::create(0.5, scene));
		m_bClose = 0;
		return;
	});
	auto moveBy = MoveBy::create(0.3f , Vec2(0, 128 + 32));
	auto scaleBy = ScaleBy::create(0.3f, 0.5f/0.2f);
	auto fadeOut = FadeOut::create(0.3f);
	auto delay = DelayTime::create(0.2f);
	auto seq = Sequence::create(cbScene, moveBy, scaleBy, fadeOut, delay, nullptr);
	m_newGameBg->runAction(isReversed? seq->reverse(): seq);
	m_settingsBg->runAction(isReversed? seq->reverse(): seq->clone());
	
	Sequence* seqMenu;
	if(isReversed){auto cbMenu = CallFunc::create([this](){m_menu->setEnabled(false);});
	seqMenu = Sequence::create(delay->clone(), cbMenu, FadeOut::create(0.3f), nullptr);}
	else{auto menuDelay = DelayTime::create(0.6f);
	auto cbMenu = CallFunc::create([this](){m_menu->setEnabled(true);});
	seqMenu = Sequence::create(menuDelay, FadeIn::create(0.3f), cbMenu, nullptr);}
	m_menu->runAction(seqMenu);


	Action* contentAnim; 
	Action* contentAnim_trans; 
	if(isReversed){contentAnim = FadeOut::create(0.4f); contentAnim_trans = contentAnim->clone();}
	else{contentAnim = Sequence::create(DelayTime::create(0.6f), FadeIn::create(0.4f), nullptr); contentAnim_trans = Sequence::create(DelayTime::create(0.6f), FadeTo::create(0.4f, 64), nullptr);}
	m_title->runAction(contentAnim);
	m_title2->runAction(contentAnim->clone());
	m_ring->runAction(contentAnim_trans);
	m_tri->runAction(contentAnim_trans->clone());
	
	auto bgScaleBy = ScaleBy::create(0.8f, 24.0f);
	auto bgAnim = Sequence::create(moveBy->clone(), bgScaleBy, nullptr);
	m_bg->runAction(isReversed? bgAnim->reverse(): bgAnim);
}

void S_Welcome::menuCallback(Ref* pSender)
{
	auto pMenuItem = (MenuItem*)pSender;
	auto tag = pMenuItem->getTag();
	putEmitter(tag == TAG_NEW_GAME? m_newGameBg->getPosition() : tag == TAG_SETTINGS? m_settingsBg->getPosition() :pMenuItem->getPosition());
	if(m_bClose == 0){
		m_bClose = tag;

		runAnimations(true);
	}
}

 void S_Welcome::onKeyEvent(EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
	// Back button pressed
	if (keyCode == EventKeyboard::KeyCode::KEY_BACK || keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {
		auto exitDialog = BallDialog::create(S("Do you want to exit?", "要退出游戏吗？"), CC_CALLBACK_0(S_Welcome::_exitGame, this));
		this->addChild(exitDialog, 1000);
	}

	else if(keyCode == EventKeyboard::KeyCode::KEY_MENU){
		m_bClose = TAG_SETTINGS;
		runAnimations(true);
	}

		// Enter key pressed
	else if (keyCode == EventKeyboard::KeyCode::KEY_KP_ENTER || keyCode == EventKeyboard::KeyCode::KEY_ENTER) {
		m_bClose = TAG_NEW_GAME;
		runAnimations(true);
	}

}

 void S_Welcome::_exitGame(){
		Director::getInstance()->end();	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        exit(0);
#endif
 }
