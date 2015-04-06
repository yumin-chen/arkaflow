#include "stdafx.h"
#include "AppDelegate.h"
#include "EngineHelper.h"
#include "Scene/SplashScene.h"
#include "Scene/WelcomeScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {}

AppDelegate::~AppDelegate() {}

bool AppDelegate::applicationDidFinishLaunching() {
	srand(time(NULL));
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	FileUtils::getInstance()->setDefaultResourceRootPath("res/");
#endif
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
		//glview = GLViewImpl::createWithRect("Ching Chong Ping Pong", Rect(0, 0, 320, 640), 1);
        glview = GLViewImpl::createWithRect("Ching Chong Ping Pong", Rect(0, 0, 2048*0.45, 1536*0.45), 1);
		//glview = GLViewImpl::createWithRect("Ching Chong Ping Pong", Rect(0, 0, DESIGNED_WIDTH, DESIGNED_HEIGHT), 1);
        director->setOpenGLView(glview);
		//glview->setDesignResolutionSize(DESIGNED_WIDTH, DESIGNED_HEIGHT, ResolutionPolicy::NO_BORDER);
    }

	auto ud = UserDefault::getInstance();
	E::calculateScreen();
	E::settings.colorAccent = ud->getIntegerForKey(UD_COLOR_ACCENT, C_CYAN);
	E::settings.musicVolume = ud->getIntegerForKey(UD_MUSIC_VOLUME, 100);
	E::settings.soundVolume = ud->getIntegerForKey(UD_SOUND_VOLUME, 100);
	E::settings.musicEnabled = ud->getBoolForKey(UD_MUSIC_ENABLED, true);
	E::settings.soundEnabled = ud->getBoolForKey(UD_SOUND_ENABLED, true);
	E::settings.currentLevel = ud->getIntegerForKey(UD_CURRENT_LEVEL, 1);
	E::settings.unlockedLevel = ud->getIntegerForKey(UD_UNLOCKED_LEVEL, 1);
	E::setColorAccent(E::settings.colorAccent);
	E::playBgMusic();

	LanguageType lang = CCApplication::getInstance()->getCurrentLanguage();
	switch(lang){
	case LanguageType::ENGLISH:
		E::language = 0;
		break;
	case LanguageType::CHINESE:
		E::language = 1;
		break;
	default:
		E::language = 0;
		break;
	}

    director->setAnimationInterval(1.0 / 60);

#ifndef NDEBUG
	auto scene_ = S_Welcome::createScene();
    director->runWithScene(scene_);
	return true;
#endif


    auto scene = S_Splash::createScene();
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
