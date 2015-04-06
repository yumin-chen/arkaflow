#include "stdafx.h"
#include "SplashScene.h"
#include "WelcomeScene.h"

USING_NS_CC;

Scene* S_Splash::createScene()
{
	auto scene = Scene::create();
	auto layer = S_Splash::create();
	scene->addChild(layer);
	return scene;
}


bool S_Splash::init()
{
	// super init 
	if ( !BaseScene::init((E::P.C50)))
	{
		return false;
	}

	auto iconCharmy = Sprite::create("g_charmysoft_logo.png");
	iconCharmy->setScale(0.75f);
	iconCharmy->setAnchorPoint(Vec2(0.5, 0.5));
	iconCharmy->setOpacity(0);
	iconCharmy->setPosition(E::visibleWidth / 2, E::visibleHeight / 2);
	this->addChild(iconCharmy, 0);
	auto callback = CallFunc::create([this](){Director::getInstance()->replaceScene(S_Welcome::createScene());});
	iconCharmy->runAction(Sequence::create(FadeIn::create(0.5f), DelayTime::create(2.0f), FadeOut::create(0.5f), callback, nullptr));

	return true;
}
