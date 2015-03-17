#include "stdafx.h"
#include "WelcomeScene.h"
#include "MainGameScene.h"
#include "UI/BallButton.h"
#include "UI/EdgedBallButton.h"
#include "UI/TitleBar.h"
#include "UI/BallDialog.h"

using namespace cocos2d;


#define	TAG_PAUSE		1002
#define	TAG_SILENT		1003
/*
#define	TAG_BTM_BG		1000
#define	TAG_SHADOW		1001
#define	TAG_PAUSE_I		1004
#define	TAG_SOUND_I		1005
#define	TAG_STS_BG		1012
#define	TAG_STS_SHINE	1013
#define	TAG_STS			1014
#define	TAG_SCORE		1015
#define	TAG_SCORE_I		1016
*/

void S_MainGame::initAnim(){
	// create solid color background
	m_mbg = BallButton::create(E::P.C50);
	m_mbg->setScale(0.3f);
	m_mbg->setPosition(Vec2(E::visibleWidth/2, 0));
	//m_mbg->setTag(TAG_BTM_BG);
	auto cbGoHigher = CallFunc::create([this](){m_mbg->setLocalZOrder(15);});
	auto cbGoLower = CallFunc::create([this](){m_mbg->setLocalZOrder(0);});
	this->addChild(m_mbg, 15);
	auto seq = Sequence::create(MoveBy::create(0.4f, Vec2(0, (E::visibleHeight-TITLEBAR_HEIGHT)/2)), cbGoHigher, cbGoLower, ScaleBy::create(0.4f, 16), nullptr);
	m_mbg->runAction(seq);

	// 
	auto bgTop = LayerColor::create(C4B(E::P.C100));
	bgTop->setContentSize(Size(E::visibleWidth, (E::visibleHeight-TITLEBAR_HEIGHT)*0.3f));
	bgTop->setPosition(0, (E::visibleHeight-TITLEBAR_HEIGHT)*0.7f);
	this->addChild(bgTop, 1);

	// 
	auto bgBtm = LayerColor::create(C4B(E::P.C100));
	bgBtm->setContentSize(Size(E::visibleWidth, (E::visibleHeight-TITLEBAR_HEIGHT)*0.3f));
	bgBtm->setPosition(0, 0);
	this->addChild(bgBtm, 1);

	m_titleBar = TitleBar::create(S("", "乾坤弹球"));
	this->addChild(m_titleBar, 999);


	auto pauseButton = EdgedBallButton::create(CC_CALLBACK_1(S_MainGame::menuCallback, this));
	pauseButton->setScale(0.3f);
	pauseButton->setPosition(Vec2(E::visibleWidth - 48, 40));
	pauseButton->setTag(TAG_PAUSE);
	m_titleBar->addChild(pauseButton, 1000);

	auto pauseIcon = Sprite::create("ob_pause.png");
	//pauseIcon->setScale(2.5f);
	pauseIcon->setColor(C3B(E::P.C700));
	//pauseIcon->setPosition(E::visibleWidth - 48, E::visibleHeight - 48);
	pauseIcon->setAnchorPoint(Vec2(0, 0));
	//pauseIcon->setTag(TAG_PAUSE_I);
	//pauseIcon->setOpacity(0);
	pauseButton->addChild(pauseIcon, 1000);

	auto silentButton = EdgedBallButton::create(CC_CALLBACK_1(S_MainGame::menuCallback, this));
	silentButton->setScale(0.3f);
	silentButton->setPosition(Vec2(E::visibleWidth - 128, 40));
	silentButton->setTag(TAG_SILENT);
	m_titleBar->addChild(silentButton, 1000);

	m_soundIcon = Sprite::create(E::settings.musicEnabled && E::settings.soundEnabled ? "ob_sound_on.png": "ob_sound_off.png");
	//soundIcon->setScale(2.5f);
	m_soundIcon->setColor(C3B(E::P.C700));
	//soundIcon->setPosition(E::visibleWidth - 128, E::visibleHeight - 48);
	m_soundIcon->setAnchorPoint(Vec2(0, 0));
	//soundIcon->setTag(TAG_SOUND_I);
	//soundIcon->setOpacity(0);
	silentButton->addChild(m_soundIcon, 1000);

	// create the shadow
	auto shadow = Sprite::create("shadow.png");
	shadow->setScale(1.0f);
	shadow->setAnchorPoint(Vec2(0, 1));
	shadow->setScaleX(E::visibleWidth / DESIGNED_WIDTH);
	shadow->setPosition(0, (E::visibleHeight-TITLEBAR_HEIGHT) * 0.3f);
	//shadow->setTag(TAG_SHADOW);
	shadow->setOpacity(0);
	this->addChild(shadow, 2);
	shadow->runAction(Sequence::create(DelayTime::create(0.4f), FadeIn::create(0.4f), nullptr));

#define STS_POS 0.08f
	// slide to start background
	m_stsBackground = Sprite::create("slide_to_start_bg.png");
	m_stsBackground->setScale(0.3f);
	m_stsBackground->setColor(bgBtm->getColor());
	//m_stsBackground->setTag(TAG_STS_BG);
	m_stsBackground->setPosition(Vec2(E::visibleWidth/2, E::visibleHeight*STS_POS));
	this->addChild(m_stsBackground, 5);

	// 
	m_stsShine = Sprite::create("slide_to_start_shine.png");
	m_stsShine->setScale(0.3f);
	m_stsShine->setColor(C3B(E::P.C800));
	//m_stsShine->setTag(TAG_STS_SHINE);
	m_stsShine->setAnchorPoint(Vec2(0, 0.5));
	m_stsShine->setPosition(Vec2(E::visibleWidth/2 - m_stsBackground->getBoundingBox().size.width / 2, E::visibleHeight*STS_POS));
	this->addChild(m_stsShine, 4);

	//
	m_stsLayer = LayerColor::create(C4B(E::P.C800));
	//m_stsLayer->setTag(TAG_STS);
	m_stsLayer->setAnchorPoint(Vec2(0.5, 0.5));
	m_stsLayer->setContentSize(Size(m_stsBackground->getBoundingBox().size.width, m_stsBackground->getBoundingBox().size.height));
	m_stsLayer->setPosition(Vec2(E::visibleWidth/2 - m_stsBackground->getBoundingBox().size.width/2, E::visibleHeight*STS_POS - m_stsBackground->getBoundingBox().size.height/2));
	this->addChild(m_stsLayer, 4);

	auto shiningMove = MoveBy::create(1.0f, Vec2(m_stsBackground->getBoundingBox().size.width - m_stsShine->getBoundingBox().size.width, 0));
	auto cbm_stsLayerShinePos = CallFunc::create([this](){m_stsShine->setPositionX(E::visibleWidth/2 - m_stsBackground->getBoundingBox().size.width / 2);});
	m_stsShine->runAction(RepeatForever::create(Sequence::create(shiningMove, cbm_stsLayerShinePos, nullptr)));

	m_stsLayer->runAction(RepeatForever::create(Sequence::create(FadeIn::create(0.5f), DelayTime::create(1.0f), FadeOut::create(0.5f), DelayTime::create(3.0f), nullptr)));
	

}

void S_MainGame::gameOver(){
	m_isGameOver = true;
	auto gameOverDialog = BallDialog::create(S("Game Over", "游戏结束"), CC_CALLBACK_0(S_MainGame::restartGame, this), CC_CALLBACK_0(S_MainGame::leaveGame, this), "b_restart.png", "b_leave.png");
	this->addChild(gameOverDialog, 1000);
}

#define ANI_GUIDE_OPACING	30.0f
#define ANI_GUIDE_STAYING	90.0f

void S_MainGame::pause()
{
			m_close = 1;
//			m_tick = ANI_PAUSE_MOVING + ANI_PAUSE_SCALING;
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
				m_soundIcon->setTexture("ob_sound_off.png");
			}
			else{
				E::settings.soundEnabled = true;
				E::settings.musicEnabled = true;
				m_soundIcon->setTexture("ob_sound_on.png");
			}
			break;
		}
	}

}
