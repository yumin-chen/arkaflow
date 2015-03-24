#include "stdafx.h"
#include "BaseScene.h"

USING_NS_CC;

#define TAG_EMITTER_START	20150204

static BaseScene *s_CurrentScene = nullptr;

bool BaseScene::init(int backgroundColor)
{
	s_CurrentScene = this;
	m_emitterCreated = TAG_EMITTER_START;
	m_emitterReleased = TAG_EMITTER_START;
	m_emitterStopped = TAG_EMITTER_START;
	m_touchEmitter = true;
	if ( !LayerColor::initWithColor(C4B(backgroundColor)) )
	{
		return false;
	}

	this->setScale(E::scale);
	this->setContentSize(Size(E::visibleWidth, E::visibleHeight));
	this->setAnchorPoint(Vec2(0, 0));

	auto listener = cocos2d::EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(BaseScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(BaseScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(BaseScene::onTouchEnded, this);
	listener->onTouchCancelled = CC_CALLBACK_2(BaseScene::onTouchCancelled, this);

	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	// creating a keyboard event listener
	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(BaseScene::onKeyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(BaseScene::onKeyReleased, this);

	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);
	return true;
}

void BaseScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event){
	for (std::vector<KeyboardEventsFunc>::iterator it = _keyboardEvents.begin() ;it != _keyboardEvents.end(); ++it)
	{
		if(it->onKeyPressed && it->onKeyPressed(keyCode, event)){
			return;
		}
	}
}

void BaseScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event){
	for (std::vector<KeyboardEventsFunc>::iterator it = _keyboardEvents.begin() ;it != _keyboardEvents.end(); ++it)
	{
		if(it->onKeyReleased && it->onKeyReleased(keyCode, event)){
			return;
		}
	}
	onKeyEvent(keyCode, event);
}

bool BaseScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{   
	/*
#ifndef NDEBUG
	Vec2 p = touch->getLocation() / E::scale;
	debugPrint("Began:" + stdp::to_string(p.x) + ", " + stdp::to_string(p.y));
#endif
	*/
	//cocos2d::MessageBox("clicked", "test");
	for (std::vector<TouchEventsFunc>::iterator it = _touchEvents.begin() ;it != _touchEvents.end(); ++it)
	{
		if(it->onTouchBegan && it->onTouchBegan(touch, event)){
			return true;
		}
	}
	if(m_touchEmitter)
		putEmitter(touch->getLocation()/E::scale);
	return false;
}

void BaseScene::onTouchMoved(Touch* touch, Event* event)
{
	/*
#ifndef NDEBUG
	Vec2 p = touch->getLocation() / E::scale;
	debugPrint("Moved:" + stdp::to_string(p.x) + ", " + stdp::to_string(p.y));
#endif
	*/
	for (std::vector<TouchEventsFunc>::iterator it = _touchEvents.begin() ;it != _touchEvents.end(); ++it)
	{
		if(it->onTouchMoved){
			it->onTouchMoved(touch, event);
		}
	}
}

void BaseScene::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event){
	/*
#ifndef NDEBUG
	Vec2 p = touch->getLocation() / E::scale;
	debugPrint("Ended:" + stdp::to_string(p.x) + ", " + stdp::to_string(p.y));
#endif
	*/
	for (std::vector<TouchEventsFunc>::iterator it = _touchEvents.begin() ;it != _touchEvents.end(); ++it)
	{
		if(it->onTouchEnded){
			it->onTouchEnded(touch, event);
		}
	}
	if(m_touchEmitter)
		putEmitter(touch->getLocation()/E::scale);
}

void BaseScene::onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event){
	for (std::vector<TouchEventsFunc>::iterator it = _touchEvents.begin() ;it != _touchEvents.end(); ++it)
	{
		if(it->onTouchCancelled){
			it->onTouchCancelled(touch, event);
		}
	}
}

BaseScene* BaseScene::getCurrentScene(){
	return s_CurrentScene;
}

int BaseScene::addTouchEvents(TouchEventsFunc touchEvent){
	static int id_generator = 0;
	id_generator++;
	touchEvent.id = id_generator;
	_touchEvents.push_back(touchEvent);
	return id_generator;
};


bool BaseScene::removeTouchEvents(int id){
	for (std::vector<TouchEventsFunc>::iterator it = _touchEvents.begin() ;it != _touchEvents.end(); ++it)
	{
		if(it->id == id){
			_touchEvents.erase(it);
			return (true);
		}
	}
	return false;
};

int BaseScene::addKeyboardEvents(KeyboardEventsFunc keyboardEvent){
	static int id_generator = 0;
	id_generator++;
	keyboardEvent.id = id_generator;
	_keyboardEvents.push_back(keyboardEvent);
	return id_generator;
};


bool BaseScene::removeKeyboardEvents(int id){
	for (std::vector<KeyboardEventsFunc>::iterator it = _keyboardEvents.begin() ;it != _keyboardEvents.end(); ++it)
	{
		if(it->id == id){
			_keyboardEvents.erase(it);
			return (true);
		}
	}
	return false;
};


void BaseScene::putEmitter(Vec2 pos){
	m_emitterCreated ++;

	auto _emitter = ParticleSystemQuad::createWithTotalParticles(100);
    //_emitter->retain();
	_emitter->setTag(m_emitterCreated);

    this->addChild(_emitter, 10000);
    ////_emitter->release();    // win32 : Remove this line
    _emitter->setTexture( Director::getInstance()->getTextureCache()->addImage("ui/ball_outer.png") );

	_emitter->setAngleVar(360);

    // duration
    _emitter->setDuration(-1);

    // gravity
    _emitter->setGravity(Vec2::ZERO);

    // speed of particles
    _emitter->setSpeed(160);
    _emitter->setSpeedVar(20);

    // radial
    _emitter->setRadialAccel(-30);
    _emitter->setRadialAccelVar(-10);

    // tagential
    _emitter->setTangentialAccel(30);
    _emitter->setTangentialAccelVar(0);

    // emitter position
    _emitter->setPosition(pos);
    _emitter->setPosVar(Vec2::ZERO);

    // life of particles
    _emitter->setLife(0.8f);
    _emitter->setLifeVar(0.4f);

    // color of particles
	_emitter->setStartColor(C4F_(E::P.C500, 0.7f));
    _emitter->setStartColorVar(Color4F(0.1f, 0.1f, 0.1f, 0.2f));
    _emitter->setEndColor(C4F_(E::P.C300, 0.15f));
    _emitter->setEndColorVar(Color4F(0.1f, 0.1f, 0.1f, 0.15f));

    // size, in pixels
    _emitter->setStartSize(16.0f);
    _emitter->setStartSizeVar(1.0f);
    _emitter->setEndSize(ParticleSystem::START_SIZE_EQUAL_TO_END_SIZE);

    // emits per second
    _emitter->setEmissionRate(_emitter->getTotalParticles()/_emitter->getLife());

    // additive

    _emitter->setBlendAdditive(false);
	auto cbStopEmitter = CallFunc::create([this](){m_emitterStopped++; ((ParticleSystemQuad*)this->getChildByTag(m_emitterStopped))->stopSystem();});
	auto cbRemoveEmitter = CallFunc::create([this](){m_emitterReleased++; this->getChildByTag(m_emitterReleased)->removeFromParentAndCleanup(true);});
	_emitter->runAction(Sequence::create(DelayTime::create(0.3f), cbStopEmitter, DelayTime::create(2.0f), cbRemoveEmitter, nullptr));

}

void BaseScene::putEmitter2(Vec2 pos){
	m_emitterCreated ++;

	auto _emitter = ParticleSystemQuad::createWithTotalParticles(100);
    //_emitter->retain();
	_emitter->setTag(m_emitterCreated);

    this->addChild(_emitter, 10000);
    ////_emitter->release();    // win32 : Remove this line
    _emitter->setTexture( Director::getInstance()->getTextureCache()->addImage("target.png") );

	_emitter->setAngleVar(360);

    // duration
    _emitter->setDuration(-1);

    // gravity
    _emitter->setGravity(Vec2::ZERO);

    // speed of particles
    _emitter->setSpeed(160);
    _emitter->setSpeedVar(20);

    // radial
    _emitter->setRadialAccel(-30);
    _emitter->setRadialAccelVar(-10);

    // tagential
    _emitter->setTangentialAccel(30);
    _emitter->setTangentialAccelVar(0);

    // emitter position
    _emitter->setPosition(pos);
    _emitter->setPosVar(Vec2::ZERO);

    // life of particles
    _emitter->setLife(1.6f);
    _emitter->setLifeVar(0.6f);

	// spin of particles
    _emitter->setStartSpin(0);
    _emitter->setStartSpinVar(30);
    _emitter->setEndSpin(360);
    _emitter->setEndSpinVar(360);

    // color of particles
	_emitter->setStartColor(C4F_(E::P.C700, 0.7f));
    _emitter->setStartColorVar(Color4F(0.1f, 0.1f, 0.1f, 0.2f));
    _emitter->setEndColor(C4F_(E::P.C700, 0.15f));
    _emitter->setEndColorVar(Color4F(0.1f, 0.1f, 0.1f, 0.15f));

    // size, in pixels
    _emitter->setStartSize(28.0f);
    _emitter->setStartSizeVar(4.0f);
    _emitter->setEndSize(ParticleSystem::START_SIZE_EQUAL_TO_END_SIZE);

    // emits per second
    _emitter->setEmissionRate(_emitter->getTotalParticles()/_emitter->getLife());

    // additive

    _emitter->setBlendAdditive(false);
	auto cbStopEmitter = CallFunc::create([this](){m_emitterStopped++; ((ParticleSystemQuad*)this->getChildByTag(m_emitterStopped))->stopSystem();});
	auto cbRemoveEmitter = CallFunc::create([this](){m_emitterReleased++; this->getChildByTag(m_emitterReleased)->removeFromParentAndCleanup(true);});
	_emitter->runAction(Sequence::create(DelayTime::create(0.3f), cbStopEmitter, DelayTime::create(2.0f), cbRemoveEmitter, nullptr));

}

void BaseScene::setTouchEmitterEnabled(bool enabled){
	m_touchEmitter = enabled;
}


#ifndef NDEBUG //if DEBUG
void BaseScene::debugPrint(std::string output){
	static Label* label = nullptr;
	static BaseScene *thisScene = nullptr;
	if(label == nullptr || thisScene != getCurrentScene()){
		label = Label::createWithSystemFont(output, "Arial", 24, 
			Size(E::visibleWidth, 48), TextHAlignment::LEFT, TextVAlignment::BOTTOM);
		label->setPosition(24, 24);
		label->setAnchorPoint(Vec2(0, 0));
		label->enableShadow(Color4B(0, 0, 0, 128), Size(1, -1));
		getCurrentScene()->addChild(label, 10000);
		thisScene = getCurrentScene();
	}
	label->setString(output);
};
#endif
