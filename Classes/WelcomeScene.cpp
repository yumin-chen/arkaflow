#include "EngineHelper.h"
#include "WelcomeScene.h"
#include "Palette.h"

USING_NS_CC;

Scene* Welcome::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Welcome::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Welcome::init()
{

    // super init 
	if ( !LayerColor::initWithColor(COLOR_LIGHTBLUE4) )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // create title sprite
    auto title = Sprite::create("title.png");

    // position the sprite on the center of the screen
    title->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height*0.7 + origin.y));
	title->setScale(0.6*visibleSize.width/title->getContentSize().width);
	// add the sprite as a child to this layer
    this->addChild(title, 0);

    // create the spinning wheel
    auto wheel = Sprite::create("wheel.png");
    wheel->setScale(visibleSize.width*0.2/wheel->getContentSize().width);
    wheel->setPosition(Vec2(origin.x + visibleSize.width/2 + title->getBoundingBox().size.width*0.4,
    		origin.y + visibleSize.height*0.7 + title->getContentSize().height*0.3));
    wheel->setTag(TAG_WHEEL);
	wheel->setScale
    // add the wheel to the layer
    this->addChild(wheel, 0);


	// create the left stripe
	auto stripeLeft = Sprite::create("stripes.png", Rect(0, 0, 128, visibleSize.height/MARGIN_SCALE + 128));
	stripeLeft->setScale(MARGIN_SCALE);
	stripeLeft->setAnchorPoint(Vec2(0, 0));

	// set the strip repeat to fill the whole line
	Texture2D::TexParams texParams;

	texParams.magFilter = GL_LINEAR;

	texParams.minFilter = GL_LINEAR;

	texParams.wrapS = GL_REPEAT;

	texParams.wrapT = GL_REPEAT;

	stripeLeft->getTexture()->setTexParameters(texParams);

	stripeLeft->setTag(TAG_STRIPE_LEFT);

    // add the left stripe as a child to this layer
    this->addChild(stripeLeft, 0);

	// create the right stripe
	auto stripeRight = Sprite::createWithTexture(stripeLeft->getTexture(), Rect(0, 0, 128, visibleSize.height/MARGIN_SCALE + 128));

	stripeRight->setAnchorPoint(Vec2(0, 0));

	stripeRight->setScale(MARGIN_SCALE);

	stripeRight->getTexture()->setTexParameters(texParams);

	stripeRight->setTag(TAG_STRIPE_RIGHT);

	stripeRight->setFlippedX(true);

	this->addChild(stripeRight, 0);
    
	// create the button for new game
	auto newGame = MenuItemImage::create(
				"b_newgame.png",
				"b_newgame_s.png",
		    	CC_CALLBACK_1(Welcome::menuNewGameCallback, this));

	newGame->setScale(visibleSize.width*0.15/newGame->getContentSize().width);
	newGame->setPosition(Vec2(origin.x + visibleSize.width*0.3,
			title->getPositionY() - title->getBoundingBox().size.height));

	// create the label for new game
		    auto fontNewGame = MenuItemFont::create("New Game",
			    	CC_CALLBACK_1(Welcome::menuNewGameCallback, this));
			fontNewGame->setFontName(FONT_MAIN);
			fontNewGame->setFontSize(48 * SCALE_MAIN);
		    fontNewGame->setColor(COLOR_DARKBLUE3);
    fontNewGame->setAnchorPoint(Vec2(0, 0.5));
    fontNewGame->setPosition(Vec2(newGame->getPositionX() + newGame->getBoundingBox().size.width*0.6,
                            newGame->getPositionY()));


	// create the button for how to play
		auto howToPlay = MenuItemImage::create(
					"b_howtoplay.png",
					"b_howtoplay_s.png",
			    	CC_CALLBACK_1(Welcome::menuHowToPlayCallback, this));

		howToPlay->setScale(visibleSize.width*0.15/howToPlay->getContentSize().width);
		howToPlay->setPosition(Vec2(origin.x + visibleSize.width*0.3,
				title->getPositionY() - title->getBoundingBox().size.height -
				newGame->getBoundingBox().size.height*1.2));


		// create the label for how to play
		    auto fontHowToPlay = MenuItemFont::create("How To Play",
			    	CC_CALLBACK_1(Welcome::menuHowToPlayCallback, this));
			fontHowToPlay->setFontName(FONT_MAIN);
			fontHowToPlay->setFontSize(48 * SCALE_MAIN);
		    fontHowToPlay->setColor(COLOR_DARKBLUE3);
		    fontHowToPlay->setAnchorPoint(Vec2(0, 0.5));
		    fontHowToPlay->setPosition(Vec2(howToPlay->getPositionX() + howToPlay->getBoundingBox().size.width*0.6,
		    		howToPlay->getPositionY()));

		    // create menu, it's an autorelease object
		    auto menu = Menu::create(newGame, fontNewGame, howToPlay, fontHowToPlay, NULL);
		    menu->setPosition(Vec2::ZERO);
		    this->addChild(menu, 1);

	// set up the scheduled callbacks
	this->scheduleUpdate();

    return true;
}

void Welcome::update( float dt ) 
{
	static int tick = 0;
	Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->getChildByTag(TAG_STRIPE_LEFT)->setPosition(Vec2(origin.x,
		origin.y - int(tick /MARGIN_SCALE) % int(MARGIN_WIDTH)));
	this->getChildByTag(TAG_STRIPE_RIGHT)->setPosition(Vec2(origin.x  + visibleSize.width - MARGIN_WIDTH,
		origin.y - int(tick /MARGIN_SCALE) % int(MARGIN_WIDTH)));
	this->getChildByTag(TAG_WHEEL)->setRotation(tick *4);
	tick ++;
}


void Welcome::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void Welcome::menuNewGameCallback(Ref* pSender)
{


}

void Welcome::menuHowToPlayCallback(Ref* pSender)
{


}
