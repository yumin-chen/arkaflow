#include "stdafx.h"
#include "WelcomeScene.h"
#include "MainGameScene.h"
#include "SettingsScene.h"
#include "Element/Triangle.h"
#include "Element/Ring.h"
#include "UI/BallButton.h"
#include "UI/BallDialog.h"

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


	srand(time(NULL));

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

	putEmitterOnBackground();

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
	if(strcmp(GAME_TITLE, "Ching Chong Ping Pong") == 0){
		title1_str = "Ching\nChong";
		title2_str = "Ping\nPong";
	}else if(strcmp(GAME_TITLE, "乾坤弹球") == 0){
		title1_str = "乾坤";
		title2_str = "弹球";
	}

	m_title = Label::createWithTTF(title1_str, FONT_BOLD, 128,
				Size(E::visibleWidth, 256), TextHAlignment::CENTER, TextVAlignment::CENTER);
	m_title->setPosition(Vec2(E::visibleWidth/2 - 48, E::visibleHeight/2 + 256));
	//m_title->enableShadow(Color4B(0, 0, 0, 128), Size(2, -2));
	m_title->setColor(C3B(E::P.C900));
	m_title->setOpacity(0);
	this->addChild(m_title, 0);

	m_title2 = Label::createWithTTF(title2_str, FONT_BOLD, 128,
				Size(E::visibleWidth, 256), TextHAlignment::CENTER, TextVAlignment::CENTER);
	m_title2->setPosition(Vec2(E::visibleWidth/2 + 64, E::visibleHeight/2 + 128 * int(E::language == 1)));
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


 
void S_Welcome::putEmitterOnBackground(){
	auto _emitter = ParticleSystemQuad::createWithTotalParticles(100);

    this->addChild(_emitter, 10);
    _emitter->setTexture( Director::getInstance()->getTextureCache()->addImage("target.png") );

	_emitter->setAngle(45);
	_emitter->setAngleVar(30);

    // duration
    _emitter->setDuration(-1);

    // gravity
    _emitter->setGravity(Vec2::ZERO);

    // speed of particles
    _emitter->setSpeed(160);
    _emitter->setSpeedVar(20);

    // radial
    //_emitter->setRadialAccel(-30);
    //_emitter->setRadialAccelVar(-10);

    // tagential
    //_emitter->setTangentialAccel(30);
    //_emitter->setTangentialAccelVar(0);

    // emitter position
    _emitter->setPosition(-128, -128);
    _emitter->setPosVar(Vec2::ZERO);

    // life of particles
    _emitter->setLife(12.0f);
    _emitter->setLifeVar(2.0f);


	// spin of particles
    _emitter->setStartSpin(0);
    _emitter->setStartSpinVar(30);
    _emitter->setEndSpin(360);
    _emitter->setEndSpinVar(360);


    // color of particles
	_emitter->setStartColor(C4F_(E::P.C700, 0.15f));
    _emitter->setStartColorVar(Color4F(0.1f, 0.1f, 0.1f, 0.1f));
    _emitter->setEndColor(C4F_(E::P.C500, 0.1f));
    _emitter->setEndColorVar(Color4F(0.1f, 0.1f, 0.1f, 0.1f));

    // size, in pixels
    _emitter->setStartSize(28.0f);
    _emitter->setStartSizeVar(4.0f);
    _emitter->setEndSize(ParticleSystem::START_SIZE_EQUAL_TO_END_SIZE);

    // emits per second
    _emitter->setEmissionRate(_emitter->getTotalParticles()/_emitter->getLife());

    // additive

    _emitter->setBlendAdditive(false);
	//auto cbStopEmitter = CallFunc::create([this](){m_emitterStopped++; ((ParticleSystemQuad*)this->getChildByTag(m_emitterStopped))->stopSystem();});
	//auto cbRemoveEmitter = CallFunc::create([this](){m_emitterReleased++; this->getChildByTag(m_emitterReleased)->removeFromParentAndCleanup(true);});
	//_emitter->runAction(Sequence::create(DelayTime::create(0.3f), cbStopEmitter, DelayTime::create(2.0f), cbRemoveEmitter, nullptr));

}
