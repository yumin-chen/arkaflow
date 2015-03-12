#include "stdafx.h"
#include "AppDelegate.h"
#include "EngineHelper.h"
#include "WelcomeScene.h"
#include "Palette.h"

USING_NS_CC;

AppDelegate::AppDelegate() {}

AppDelegate::~AppDelegate() {}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
		//glview = GLViewImpl::createWithRect("Ching Chong Ping Pong", Rect(0, 0, 320, 640), 1);
        glview = GLViewImpl::createWithRect("Ching Chong Ping Pong", Rect(0, 0, 800, 640), 1);
		//glview = GLViewImpl::createWithRect("Ching Chong Ping Pong", Rect(0, 0, DESIGNED_WIDTH, DESIGNED_HEIGHT), 1);
        director->setOpenGLView(glview);
		//glview->setDesignResolutionSize(DESIGNED_WIDTH, DESIGNED_HEIGHT, ResolutionPolicy::NO_BORDER);
    }

	E::calculateScreen();
	E::settings.colorAccent = C_CYAN;
	E::setColorAccent(E::settings.colorAccent);
	E::playBgMusic();

    director->setAnimationInterval(1.0 / 60);

    auto scene = S_Welcome::createScene();

    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
