#include "stdafx.h"
#include "WelcomeScene.h"
#include "MainGameScene.h"
#include "BallButton.h"

using namespace cocos2d;

#define	TAG_BTM_BG		1000
#define	TAG_SHADOW		1001
#define	TAG_PAUSE		1002
#define	TAG_SILENT		1003
#define	TAG_PAUSE_I		1004
#define	TAG_SOUND_I		1005
#define	TAG_GAMEOVER_BG 1006
#define	TAG_GAMEOVER_IC 1007
#define	TAG_RESTART_BG  1008
#define	TAG_RESTART_IC  1009
#define	TAG_RETURN_BG   1010
#define	TAG_RETURN_IC	1011
#define	TAG_STS_BG		1012
#define	TAG_STS_SHINE	1013
#define	TAG_STS			1014
#define	TAG_SCORE		1015
#define	TAG_SCORE_I		1016

void S_MainGame::initAnim(){
	// create solid color background
	auto bg = BallButton::create(E::C50);
	bg->setScale(0.3f);
	bg->setPosition(E::visibleWidth/2, 0);
	bg->setTag(TAG_BTM_BG);
	// add the wheel to the layer
	this->addChild(bg, 15);

	// 
	auto bgTop = LayerColor::create(C4B(E::C100));
	bgTop->setContentSize(Size(E::visibleWidth, E::visibleHeight*0.3f));
	bgTop->setPosition(0, E::visibleHeight*0.7f);
	this->addChild(bgTop, 1);

	// 
	auto bgBtm = LayerColor::create(C4B(E::C100));
	bgBtm->setContentSize(Size(E::visibleWidth, E::visibleHeight*0.3f));
	bgBtm->setPosition(0, 0);
	this->addChild(bgBtm, 1);


	auto pauseButton = BallButton::create(E::C700, E::C200, CC_CALLBACK_1(S_MainGame::menuCallback, this));
	pauseButton->setScale(0.15f);
	pauseButton->setPosition(E::visibleWidth - 48, E::visibleHeight - 48);
	pauseButton->setTag(TAG_PAUSE);
	this->addChild(pauseButton, 1000);

	auto pauseIcon = Sprite::create("b_pause.png");
	pauseIcon->setScale(0.3f);
	pauseIcon->setPosition(E::visibleWidth - 48, E::visibleHeight - 48);
	pauseIcon->setTag(TAG_PAUSE_I);
	pauseIcon->setOpacity(0);
	this->addChild(pauseIcon, 1000);

	auto silentButton = BallButton::create(E::C700, E::C200);
	silentButton->setScale(0.15f);
	silentButton->setPosition(E::visibleWidth - 128, E::visibleHeight - 48);
	silentButton->setTag(TAG_SILENT);
	this->addChild(silentButton, 1000);

	auto soundIcon = Sprite::create("b_sound.png");
	soundIcon->setScale(0.3f);
	soundIcon->setPosition(E::visibleWidth - 128, E::visibleHeight - 48);
	soundIcon->setTag(TAG_SOUND_I);
	soundIcon->setOpacity(0);
	this->addChild(soundIcon, 1000);

	auto scoreBg = BallButton::create(E::C700);
	scoreBg->setScale(0.15f);
	scoreBg->setPosition(48, E::visibleHeight - 48);
	scoreBg->setTag(TAG_SCORE);
	this->addChild(scoreBg, 1000);

	
	m_scoreLabel = Label::createWithSystemFont("", FONT_MAIN, 32, 
		Size(196, scoreBg->getBoundingBox().size.height), TextHAlignment::LEFT, TextVAlignment::CENTER);
	m_scoreLabel->setPosition(96, E::visibleHeight - 48);
	m_scoreLabel->setAnchorPoint(Vec2(0, 0.5));
	m_scoreLabel->enableOutline(C4B(E::C900), 1);
	//m_scoreLabel->enableShadow(C4B_(E::C900, 128),Size(1, -1),0);
	m_scoreLabel->setColor(C3B(E::C700));
	this->addChild(m_scoreLabel, 1000);


	auto scoreIcon = Sprite::create("b_score.png");
	scoreIcon->setScale(0.3f);
	scoreIcon->setPosition(48, E::visibleHeight - 48);
	scoreIcon->setTag(TAG_SCORE_I);
	scoreIcon->setOpacity(0);
	this->addChild(scoreIcon, 1000);

	// create the shadow
	auto shadow = Sprite::create("shadow.png");
	shadow->setScale(1.0f);
	shadow->setAnchorPoint(Vec2(0, 1));
	shadow->setScaleX(E::visibleWidth / DESIGNED_WIDTH);
	shadow->setPosition(0, E::visibleHeight * 0.3f);
	shadow->setTag(TAG_SHADOW);
	shadow->setOpacity(0);
	this->addChild(shadow, 2);

	// game over background
	auto bgGameOver = BallButton::create(E::C700);
	bgGameOver->setTag(TAG_GAMEOVER_BG);
	bgGameOver->setScale(0.3f);
	bgGameOver->setPosition(E::visibleWidth/2, 0);
	bgGameOver->setVisible(false);
	this->addChild(bgGameOver, 1000);

	// game over icon
	auto gameOverIcon = Sprite::create("gameover.png");
	gameOverIcon->setScale(0.5f);
	gameOverIcon->setTag(TAG_GAMEOVER_IC);
	gameOverIcon->setPosition(E::visibleWidth/2, E::visibleHeight/2);
	gameOverIcon->setVisible(false);
	gameOverIcon->setOpacity(0);
	this->addChild(gameOverIcon, 1000);

	// restart background
	auto bgRestart = BallButton::create(E::C400, E::C200, CC_CALLBACK_1(S_MainGame::menuCallback, this));
	bgRestart->setTag(TAG_RESTART_BG);
	bgRestart->setScale(0.2f);
	bgRestart->setPosition(E::visibleWidth*0.3f, 0);
	bgRestart->setVisible(false);
	this->addChild(bgRestart, 1000);

	// restart icon
	auto restartIcon = Sprite::create("b_restart.png");
	restartIcon->setScale(0.6f);
	restartIcon->setTag(TAG_RESTART_IC);
	restartIcon->setPosition(E::visibleWidth*0.3f, E::visibleHeight*0.3f);
	restartIcon->setVisible(false);
	restartIcon->setOpacity(0);
	this->addChild(restartIcon, 1000);

	// return background
	auto bgReturn = BallButton::create(E::C400, E::C200, CC_CALLBACK_1(S_MainGame::menuCallback, this));
	bgReturn->setTag(TAG_RETURN_BG);
	bgReturn->setScale(0.2f);
	bgReturn->setPosition(E::visibleWidth*0.7f, 0);
	bgReturn->setVisible(false);
	this->addChild(bgReturn, 1000);

	// return icon
	auto returnIcon = Sprite::create("b_leave.png");
	returnIcon->setScale(0.6f);
	returnIcon->setTag(TAG_RETURN_IC);
	returnIcon->setPosition(E::visibleWidth*0.7f, E::visibleHeight*0.3f);
	returnIcon->setVisible(false);
	returnIcon->setOpacity(0);
	this->addChild(returnIcon, 1000);


#define STS_POS 0.08f
	// slide to start background
	auto StsBg = Sprite::create("slide_to_start_bg.png");
	StsBg->setScale(0.3f);
	StsBg->setColor(bgBtm->getColor());
	StsBg->setTag(TAG_STS_BG);
	StsBg->setPosition(E::visibleWidth/2, E::visibleHeight*STS_POS);
	this->addChild(StsBg, 5);

	// 
	auto StsShine = Sprite::create("slide_to_start_shine.png");
	StsShine->setScale(0.3f);
	StsShine->setColor(C3B(E::C800));
	StsShine->setTag(TAG_STS_SHINE);
	StsShine->setAnchorPoint(Vec2(0, 0.5));
	StsShine->setPosition(E::visibleWidth/2 - StsBg->getBoundingBox().size.width / 2, E::visibleHeight*STS_POS);
	this->addChild(StsShine, 4);

	//
	auto Sts = LayerColor::create(C4B(E::C800));
	Sts->setTag(TAG_STS);
	Sts->setAnchorPoint(Vec2(0.5, 0.5));
	Sts->setContentSize(Size(StsBg->getBoundingBox().size.width, StsBg->getBoundingBox().size.height));
	Sts->setPosition(E::visibleWidth/2 - StsBg->getBoundingBox().size.width/2, E::visibleHeight*STS_POS - StsBg->getBoundingBox().size.height/2);
	this->addChild(Sts, 4);

}

#define ANI_MOVING_BG		15.0f
#define ANI_SCALING_BG		30.0f
#define ANI_SHADOWING_BG	15.0f
#define ANI_PAUSE_MOVING	30.0f
#define ANI_PAUSE_SCALING	15.0f
#define ANI_PAUSE_OPACING	15.0f

#define ANI_GO_MOVING		15.0f
#define ANI_GO_SCALING		15.0f
#define ANI_GO_OPACING		15.0f

#define ANI_GUIDE_OPACING	30.0f
#define ANI_GUIDE_STAYING	90.0f
void S_MainGame::updateAnim(){
	if(m_close > 0){
		m_tick = m_tick - 1;
	}
	else{
		m_tick ++;
	}

	if(m_tick < 0){
		Director::getInstance()->replaceScene(S_Welcome::createScene());
	}

	if(m_bGuide)
	{
		this->getChildByTag(TAG_STS_BG)->setVisible(true);
		this->getChildByTag(TAG_STS_SHINE)->setVisible(true);
		this->getChildByTag(TAG_STS)->setVisible(true);
		m_scoreLabel->setVisible(false);
		static bool shining = false;
		static long shining_tick = 0;
		static int shining_count = 0;
		if(shining){
			shining_tick = shining_tick + 4;

			int xOffset = shining_tick %      
				int(this->getChildByTag(TAG_STS_BG)->getBoundingBox().size.width -
					this->getChildByTag(TAG_STS_SHINE)->getBoundingBox().size.width);

			if(xOffset == 0){
				shining_tick = 0;
				shining_count ++;
				if(shining_count >= 1){
					shining = false;
					shining_count = 0;
				}
			}else{

				this->getChildByTag(TAG_STS_SHINE)->setPositionX(E::visibleWidth/2 -
					this->getChildByTag(TAG_STS_BG)->getBoundingBox().size.width / 2 + xOffset 
					);
			}

		}else{
			shining_tick++;
			if(shining_tick <= ANI_GUIDE_OPACING)
			{
				this->getChildByTag(TAG_STS)->setOpacity((shining_tick/ANI_GUIDE_OPACING)*255);
			}
			if(shining_tick > ANI_GUIDE_OPACING + ANI_GUIDE_STAYING)
			{
				this->getChildByTag(TAG_STS)->setOpacity(0);
				shining = true;
				shining_tick = 0;
			}
		}
	}else{
		this->getChildByTag(TAG_STS_BG)->setVisible(false);
		this->getChildByTag(TAG_STS_SHINE)->setVisible(false);
		this->getChildByTag(TAG_STS)->setVisible(false);
		m_scoreLabel->setVisible(true);
	}


	if(m_tick <= ANI_MOVING_BG){
		this->getChildByTag(TAG_BTM_BG)->setPositionY(0 + (m_tick/ANI_MOVING_BG)*(E::visibleHeight/2));
		this->getChildByTag(TAG_BTM_BG)->setLocalZOrder(15);
	}

	if(m_tick > ANI_MOVING_BG && m_tick <=  ANI_MOVING_BG + ANI_SCALING_BG){
		this->getChildByTag(TAG_BTM_BG)->setScale(0.3 + ((m_tick-ANI_MOVING_BG)/ANI_SCALING_BG)*4.0f);
		this->getChildByTag(TAG_BTM_BG)->setLocalZOrder(0);
	}

	if(m_tick >= ANI_MOVING_BG + ANI_SCALING_BG/2 && m_tick <=  ANI_MOVING_BG + ANI_SCALING_BG/2 + ANI_SHADOWING_BG){
		this->getChildByTag(TAG_SHADOW)->setOpacity(((m_tick-ANI_MOVING_BG - ANI_SCALING_BG/2)/ANI_SHADOWING_BG)*255);
	}

	if(m_tick <= ANI_PAUSE_MOVING){
		this->getChildByTag(TAG_PAUSE)->setPositionY((m_tick/ANI_PAUSE_MOVING)*(E::visibleHeight-48));
		this->getChildByTag(TAG_SILENT)->setPositionY((m_tick/ANI_PAUSE_MOVING)*(E::visibleHeight-48));
		this->getChildByTag(TAG_SCORE)->setPositionY((m_tick/ANI_PAUSE_MOVING)*(E::visibleHeight-48));
	}
	if(m_tick >= ANI_PAUSE_MOVING && m_tick <= ANI_PAUSE_MOVING+ANI_PAUSE_SCALING){
		this->getChildByTag(TAG_PAUSE)->setScale(0.15 + ((m_tick-ANI_PAUSE_MOVING)/ANI_PAUSE_SCALING)*0.15f);
		this->getChildByTag(TAG_SILENT)->setScale(0.15 + ((m_tick-ANI_PAUSE_MOVING)/ANI_PAUSE_SCALING)*0.15f);
		this->getChildByTag(TAG_SCORE)->setScale(0.15 + ((m_tick-ANI_PAUSE_MOVING)/ANI_PAUSE_SCALING)*0.15f);
		this->getChildByTag(TAG_PAUSE_I)->setOpacity(0);
		this->getChildByTag(TAG_SOUND_I)->setOpacity(0);
		this->getChildByTag(TAG_SCORE_I)->setOpacity(0);
	}

	if(m_tick >= ANI_PAUSE_MOVING+ANI_PAUSE_SCALING  && m_tick <= ANI_PAUSE_MOVING+ANI_PAUSE_SCALING+ANI_PAUSE_OPACING){
		this->getChildByTag(TAG_PAUSE_I)->setOpacity(((m_tick-ANI_PAUSE_MOVING-ANI_PAUSE_OPACING)/ANI_PAUSE_SCALING)*255);
		this->getChildByTag(TAG_SOUND_I)->setOpacity(((m_tick-ANI_PAUSE_MOVING-ANI_PAUSE_OPACING)/ANI_PAUSE_SCALING)*255);
		this->getChildByTag(TAG_SCORE_I)->setOpacity(((m_tick-ANI_PAUSE_MOVING-ANI_PAUSE_OPACING)/ANI_PAUSE_SCALING)*255);
	}
	if(m_isGameOver)
	{
		if(m_close > 0 || m_isRestarting){
			m_tick2 --;
		}else{
			m_tick2 ++;
		}

		if(m_tick2 <= ANI_GO_MOVING)
		{
			this->getChildByTag(TAG_GAMEOVER_BG)->setVisible(true);
			this->getChildByTag(TAG_GAMEOVER_BG)->setPositionY(((m_tick2)/ANI_GO_MOVING)*(E::visibleHeight/2));
			this->getChildByTag(TAG_RESTART_BG)->setVisible(true);
			this->getChildByTag(TAG_RESTART_BG)->setPositionY(((m_tick2)/ANI_GO_MOVING)*(E::visibleHeight*0.3));
			this->getChildByTag(TAG_RETURN_BG)->setVisible(true);
			this->getChildByTag(TAG_RETURN_BG)->setPositionY(((m_tick2)/ANI_GO_MOVING)*(E::visibleHeight*0.3));
		}
		if(m_tick2 >= ANI_GO_MOVING && m_tick2 <= ANI_GO_MOVING + ANI_GO_SCALING)
		{
			this->getChildByTag(TAG_GAMEOVER_BG)->setScale(0.3+((m_tick2-ANI_GO_MOVING)/ANI_GO_SCALING)*1.5);
			this->getChildByTag(TAG_RESTART_BG)->setScale(0.2+((m_tick2-ANI_GO_MOVING)/ANI_GO_SCALING)*0.4);
			this->getChildByTag(TAG_RETURN_BG)->setScale(0.2+((m_tick2-ANI_GO_MOVING)/ANI_GO_SCALING)*0.4);
		}
		if(m_tick2 >= ANI_GO_MOVING + ANI_GO_SCALING && m_tick2 <= ANI_GO_MOVING + ANI_GO_SCALING + ANI_GO_OPACING)
		{
			this->getChildByTag(TAG_GAMEOVER_IC)->setVisible(true);
			this->getChildByTag(TAG_GAMEOVER_IC)->setOpacity(((m_tick2-ANI_GO_MOVING-ANI_GO_SCALING)/ANI_GO_SCALING)*255);
			this->getChildByTag(TAG_RESTART_IC)->setVisible(true);
			this->getChildByTag(TAG_RESTART_IC)->setOpacity(((m_tick2-ANI_GO_MOVING-ANI_GO_SCALING)/ANI_GO_SCALING)*255);
			this->getChildByTag(TAG_RETURN_IC)->setVisible(true);
			this->getChildByTag(TAG_RETURN_IC)->setOpacity(((m_tick2-ANI_GO_MOVING-ANI_GO_SCALING)/ANI_GO_SCALING)*255);
		}
		if(m_tick2 < 0){

			this->getChildByTag(TAG_RETURN_IC)->setVisible(false);
			this->getChildByTag(TAG_RESTART_IC)->setVisible(false);
			this->getChildByTag(TAG_GAMEOVER_IC)->setVisible(false);
			this->getChildByTag(TAG_GAMEOVER_BG)->setVisible(false);
			this->getChildByTag(TAG_RESTART_BG)->setVisible(false);
			this->getChildByTag(TAG_RETURN_BG)->setVisible(false);
			restartGame();
		}
	}
}
void S_MainGame::pause()
{
			m_close = 1;
			m_tick = ANI_PAUSE_MOVING + ANI_PAUSE_SCALING;
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
			break;
		}
	case TAG_RESTART_BG:
		{
			m_isRestarting = true;
			m_tick2 = ANI_GO_MOVING + ANI_GO_SCALING  +ANI_GO_OPACING;
			break;
		}
	case TAG_RETURN_BG:
		{
			m_close = 1;
			m_tick2 = ANI_GO_MOVING + ANI_GO_SCALING  +ANI_GO_OPACING;
			m_tick = ANI_PAUSE_MOVING + ANI_PAUSE_SCALING;
			break;
		}
	}

}
