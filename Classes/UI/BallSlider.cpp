#include "stdafx.h"
#include "EngineHelper.h"
#include "BallSlider.h"
#include "../Scene/BaseScene.h"

USING_NS_CC;

BallSlider::BallSlider() {}

BallSlider::~BallSlider() {
}

BallSlider* BallSlider::create()
{
    BallSlider* widget = new (std::nothrow) BallSlider();
    if (widget && widget->init())
    {
        widget->autorelease();
		widget->loadBarTexture("ui/slider_back.png"); // what the slider looks like
		widget->loadSlidBallTextures("ui/slidernode_n.png", "ui/slidernode_p.png");
		widget->loadProgressBarTexture("ui/slider_progressbar.png");
		widget->initRenderers();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return nullptr;
}



void BallSlider::initRenderers()
{
#define BALL_SCALE 0.3f
	_slidBallNormalRenderer->setScale(BALL_SCALE);
	_sliderBallNormalTextureScaleX = BALL_SCALE;
	_sliderBallNormalTextureScaleY = BALL_SCALE;
	_slidBallPressedRenderer->setScale(BALL_SCALE);
	auto center = Sprite::create("ui/slidernode_center.png");
	center->setScale(BALL_SCALE);
	_slidBallRenderer->addChild(center);

	//_slidBallNormalRenderer->runAction(RotateBy::create(1E32f, 1E32f * 720));

	updateColors();
}

void BallSlider::updateColors()
{
	_barRenderer->setColor(C3B(E::P.C900));
	_progressBarRenderer->setColor(C3B(E::P.C300));
	_slidBallNormalRenderer->setColor(C3B(E::P.C500));
	_slidBallPressedRenderer->setColor(C3B(E::P2.C800));
}

void BallSlider::setWidth(float w){
	ignoreContentAdaptWithSize(false);
	setContentSize(Size(w, getContentSize().height));
	//adaptRenderers();
}


void BallSlider::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unusedEvent){
	Slider::onTouchEnded(touch, unusedEvent);
	E::playEffect("da");
}