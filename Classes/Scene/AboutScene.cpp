#include "stdafx.h"
#include "AboutScene.h"
#include "WelcomeScene.h"
#include "SettingsScene.h"
#include "MainGameScene.h"
#include "UI/BallButton.h"
#include "UI/TitleBar.h"
#include "UI/BallSlider.h"
#include "UI/EdgedBallButton.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
#define BTM_HEIGHT		(96+16)

#define TAG_BACK	4001
#define TAG_SHARE	4002
#define TAG_RATE	4003
#define TAG_WEBSITE	4004

Scene* S_About::createScene(int previousScene)
{
	auto scene = Scene::create();

	auto layer = S_About::create();
	layer->_previousScene = previousScene;

	scene->addChild(layer);

	return scene;
}

// on "init" you need to initialize your instance
bool S_About::init()
{
	m_bClose = false;

	// super init 

	if ( !BaseScene::init((E::P.C100)) )
	{
		return false;
	}

	m_titleBar = TitleBar::create(S("About", "关于"));
	this->addChild(m_titleBar, 1000);

	m_heartBtn = EdgedBallButton::create(CC_CALLBACK_1(S_About::menuCallback, this));
	m_heartBtn->setScale(0.3f);
	m_heartBtn->setPosition(Vec2(48, 40));
	m_heartBtn->setTag(TAG_BACK);
	m_titleBar->addChild(m_heartBtn, 1000);

	m_heartIcon = Sprite::create("ui/ob_go_back.png");
	m_heartIcon->setColor(C3B(E::P.C700));
	m_heartIcon->setScale(0.9f);
	m_heartIcon->setAnchorPoint(Vec2(0.5, 0.5));
	m_heartIcon->setPosition(m_heartBtn->getContentSize() / 2);
	m_heartBtn->addChild(m_heartIcon, 1000);
	
	// create solid color background
	m_btmBg = BallButton::create(E::P.C50);
	m_btmBg->setScale(0.3f);
	m_btmBg->setPosition(Vec2(E::visibleWidth/2, 128+(-9/15.0f)*128));
//	m_btmBg->setTag(TAG_BTM_BG);
	this->addChild(m_btmBg, 0);

	// create solid color background
	m_bgTop = LayerColor::create(C4B(E::P.C100));
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

//============================================================
	auto icon = Sprite::create("icon.png");
	icon->setScale(0.6f);
	icon->setPosition(E::visibleWidth/2, E::originY + 640 - 24);
	this->addChild(icon, 0);
	
	auto lbTitle = Label::createWithTTF(GAME_TITLE, FONT_BOLD, 24, 
		Size(256, 32), TextHAlignment::CENTER, TextVAlignment::CENTER);
	lbTitle->setPosition(E::visibleWidth/2, E::originY + 480 + 32);
	lbTitle->setAnchorPoint(Vec2(0.5, 0.5));
	lbTitle->setColor(C3B(E::P.C900));
	this->addChild(lbTitle, 0);

	auto lbVersion = Label::createWithTTF("Ver: " VERSION, FONT_MAIN, 24, 
		Size(256, 32), TextHAlignment::CENTER, TextVAlignment::CENTER);
	lbVersion->setPosition(E::visibleWidth/2, E::originY + 480);
	lbVersion->setAnchorPoint(Vec2(0.5, 0.5));
	lbVersion->setColor(C3B(E::P.C900));
	this->addChild(lbVersion, 0);

#define OFFSET_Y__ (320)
	
	auto iconCharmy = Sprite::create("g_charmy_av.png");
	iconCharmy->setScale(0.6f);
	iconCharmy->setAnchorPoint(Vec2(0, 0.5));
	iconCharmy->setPosition(E::originX + 24, E::originY + OFFSET_Y__);
	this->addChild(iconCharmy, 0);

	auto lbCharmy = Label::createWithTTF(S("CharmySoft", "尘泯网络"), FONT_BOLD, 28, 
		Size(320, 64), TextHAlignment::CENTER, TextVAlignment::CENTER);
	lbCharmy->setPosition(E::visibleWidth/2 + 80, E::originY + OFFSET_Y__ + 48);
	lbCharmy->setAnchorPoint(Vec2(0.5, 0.5));
	lbCharmy->setColor(C3B(E::P.C900));
	this->addChild(lbCharmy, 0);

	auto lbCharmyDetail = Label::createWithTTF(S("Charmy Game and Software Development", "尘羽泯游戏软件开发"), FONT_MAIN, 24, 
		Size(320, 64), TextHAlignment::CENTER, TextVAlignment::CENTER);
	lbCharmyDetail->setPosition(E::visibleWidth/2 + 80, E::originY + OFFSET_Y__ );
	lbCharmyDetail->setAnchorPoint(Vec2(0.5, 0.5));
	lbCharmyDetail->setColor(C3B(E::P.C900));
	this->addChild(lbCharmyDetail, 0);

	auto lbLink = Label::createWithTTF("http://www.CharmySoft.com", FONT_MAIN, 24, 
		Size(256, 64), TextHAlignment::CENTER, TextVAlignment::CENTER);
	lbLink->setPosition(E::visibleWidth/2 + 80, E::originY + OFFSET_Y__ - 48);
	lbLink->setAnchorPoint(Vec2(0.5, 0.5));
	lbLink->setColor(C3B(E::P.C900));
	this->addChild(lbLink, 0);

	/*
	
	auto lbVersion = Label::createWithTTF(S("VERSION", "版本"), FONT_BOLD, 24, 
				Size(128, 32), TextHAlignment::LEFT, TextVAlignment::CENTER);
	lbVersion->setPosition(24, E::originY + 480);
	lbVersion->setAnchorPoint(Vec2(0, 0));
	lbVersion->setColor(C3B(E::P.C900));
	this->addChild(lbVersion, 0);
	*/

	auto lbThanks = Label::createWithTTF("Several icons used in this app are from the Google Material Design Icons", FONT_MAIN, 16, 
		Size(DESIGNED_WIDTH, 64), TextHAlignment::CENTER, TextVAlignment::CENTER);
	lbThanks->setPosition(E::visibleWidth/2, E::originY + BTM_HEIGHT + 24);
	lbThanks->setAnchorPoint(Vec2(0.5, 0.5));
	lbThanks->setColor(C3B(E::P.C900));
	this->addChild(lbThanks, 0);

//============================================================


	m_shareBtnBg = BallButton::create(E::P.C700);
	m_shareBtnBg->setScale(0.2f);
	m_shareBtnBg->setPosition(Vec2(E::visibleWidth/2 -(m_shareBtnBg->getContentSize().width*0.35f*2 + 48)/2, -16));
	this->addChild(m_shareBtnBg, 0);

	auto sShareIcon = Sprite::create("ui/b_share.png");
	sShareIcon->setColor(C3B(E::P.C50));
	sShareIcon->setAnchorPoint(Vec2(0, 0));

	m_rateBg = BallButton::create(E::P.C700);
	m_rateBg->setScale(0.2f);
	m_rateBg->setPosition(Vec2(E::visibleWidth/2, -16));
	this->addChild(m_rateBg, 0);

	auto sRateIcon = Sprite::create("ui/b_rate.png");
	sRateIcon->setColor(C3B(E::P.C50));
	sRateIcon->setAnchorPoint(Vec2(0, 0));

	m_websiteBtnBg = BallButton::create(E::P.C700);
	m_websiteBtnBg->setScale(0.2f);
	m_websiteBtnBg->setPosition(Vec2(E::visibleWidth/2 + (m_shareBtnBg->getContentSize().width*0.35f*2 + 48)/2, -16));
	this->addChild(m_websiteBtnBg, 0);

	auto sWebsiteIcon = Sprite::create("ui/b_website.png");
	sWebsiteIcon->setColor(C3B(E::P.C50));
	sWebsiteIcon->setAnchorPoint(Vec2(0, 0));

	auto shareItem = MenuItemSprite::create(
		BallButton::create(E::P.C700),
		BallButton::create(E::P2.C500),
		CC_CALLBACK_1(S_About::menuCallback, this));

	shareItem->setScale(0.35f);
	shareItem->setTag(TAG_SHARE);
	shareItem->addChild(sShareIcon);

	auto rateItem = MenuItemSprite::create(
		BallButton::create(E::P.C700),
		BallButton::create(E::P2.C500),
		CC_CALLBACK_1(S_About::menuCallback, this));

	rateItem->setScale(0.35f);
	rateItem->setTag(TAG_RATE);
	rateItem->addChild(sRateIcon);

	
	auto websiteItem = MenuItemSprite::create(
		BallButton::create(E::P.C700),
		BallButton::create(E::P2.C500),
		CC_CALLBACK_1(S_About::menuCallback, this));

	websiteItem->setScale(0.35f);
	websiteItem->setTag(TAG_WEBSITE);
	websiteItem->addChild(sWebsiteIcon);


	// create menu
	m_menu = Menu::create(shareItem, rateItem, websiteItem, NULL);
	m_menu->setPosition(Vec2(E::visibleWidth/2, 64 + 4 -16));
	m_menu->alignItemsHorizontallyWithPadding(24);
	m_menu->setEnabled(false);
	m_menu->setOpacity(0);
	this->addChild(m_menu, 1);

	runAnimations(false);

	return true;
}

void S_About::runAnimations(bool isReversed){
	auto cbClose = CallFunc::create([this](){
		if(m_bClose){
			switch(_previousScene){
			case 0:
				Director::getInstance()->replaceScene(S_Welcome::createScene());
				break;
			case 1:
				Director::getInstance()->replaceScene(S_Settings::createScene());
				break;
			case 2:
				Director::getInstance()->replaceScene(S_MainGame::createScene());
				break;

			}
			m_bClose = false;
		}
	});

	auto moveBy = MoveBy::create(0.2f , Vec2(0, 64 + 4));
	auto scaleBy = ScaleBy::create(0.2f , 0.35f/0.2f);
	auto fadeOut = FadeOut::create(0.2f);
	auto seq = Sequence::create(cbClose, moveBy, scaleBy, fadeOut, nullptr);
	m_shareBtnBg->runAction(isReversed? seq->reverse(): seq);
	m_rateBg->runAction(isReversed? seq->reverse(): seq->clone());
	m_websiteBtnBg->runAction(isReversed? seq->reverse(): seq->clone());

	
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

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "android/log.h"
#include "platform/android/jni/JniHelper.h"
#define  CLASS_NAME "org/cocos2dx/cpp/AppActivity"
extern "C"{
 void callAndroidFunction(const char* function_name)
 {
	  bool hasMethod;
	  JniMethodInfo jni_methodInfo;
	  hasMethod = JniHelper::getStaticMethodInfo(jni_methodInfo, CLASS_NAME, function_name, "()V");
	  if(hasMethod){
		//cocos2d::MessageBox("function Share() was found", "t");
	   //CCLog("function Share() was found");
	   if(jni_methodInfo.methodID){
		jni_methodInfo.env->CallStaticVoidMethod(jni_methodInfo.classID,  jni_methodInfo.methodID);
		//cocos2d::MessageBox("function Share() was called", "t");
		//function Share() was called
	   }
	  }else{
		  //cocos2d::MessageBox("function Share() was not found", "t");
		  //function Share() was not found
	  }
	 }
}
#endif

void S_About::menuCallback(Ref* pSender)
{
	auto pMenuItem = (MenuItem*)pSender;
	auto tag = pMenuItem->getTag();
	switch(tag)
	{
	case TAG_SHARE:
		{
			putEmitter(m_shareBtnBg->getPosition());
			#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
				callAndroidFunction("Charmy_Share");
			#endif
			break;
		}

	case TAG_RATE:
		{
			putEmitter(m_rateBg->getPosition());
			#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
				callAndroidFunction("Charmy_Rate");
			#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
				ShellExecute(0, L"open", L"http://play.google.com/store/apps/details?id=com.CharmySoft.CCPP", 0, 0, 1);
			#endif
			break;
		}
	case TAG_WEBSITE:
		{
			cocos2d::Application::getInstance()->openURL("http://www.CharmySoft.com");
			break;
		}
	case TAG_BACK:
		{
			m_bClose = true;
			runAnimations(true);
			break;
		}
	}

}



 void S_About::onKeyEvent(EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
	// Back button pressed
	if (keyCode == EventKeyboard::KeyCode::KEY_BACK || keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {
			m_bClose = true;
			runAnimations(true);
	}

	// Enter key pressed
	if (keyCode == EventKeyboard::KeyCode::KEY_KP_ENTER || keyCode == EventKeyboard::KeyCode::KEY_ENTER) {
		//_share();
	}

}
