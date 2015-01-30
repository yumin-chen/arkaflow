#include "stdafx.h"
#include "MainGameScene.h"
#include "BallButton.h"

USING_NS_CC;
#define PI 3.141592653589793238462643383279502884197169399375105820974944592307816406286
#define BORDER_WIDTH 12;


Scene* S_MainGame::createScene()
{
	auto scene = Scene::create();

	auto layer = S_MainGame::create();

	scene->addChild(layer);

	return scene;
}

// on "init" you need to initialize your instance
bool S_MainGame::init()
{
	m_close = 0;
	m_tick = 0;
	// super init 

	if ( !LayerColor::initWithColor(C4B(E::C200)) )
	{
		return false;
	}


	this->setScale(E::scale);
	this->setContentSize(Size(E::visibleWidth, E::visibleHeight));
	this->setAnchorPoint(Vec2(0, 0));

	initAnim();

	auto label = LabelTTF::create("Slippery Wheels", "Arial", 24);

	// position the label on the center of the screen
	label->setPosition(Vec2(E::visibleWidth/2,
		E::visibleHeight - label->getContentSize().height));

	label->setTag(32);

	// add the label as a child to this layer
	this->addChild(label, 10);

	// create the spinning wheel
	auto wheel = Sprite::create("wheel.png");
	E::setRandomColor(wheel);
	wheel->setScale(0.15f);
	// add the wheel to the layer
	this->addChild(wheel, 10);

	m_wheel.sprite = wheel;
	restartGame();

	m_smartstring = SmartString::create();
	this->addChild(m_smartstring);

	auto listener = cocos2d::EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(S_MainGame::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(S_MainGame::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(S_MainGame::onTouchEnded, this);

	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	// set up the scheduled callbacks
	this->scheduleUpdate();

	return true;
}

inline float S_MainGame::angleMinus90(float angle){
	return (int(angle*180/PI + 270)%360*PI/180);
}

inline float S_MainGame::anglePlus90(float angle){
	return (int(angle*180/PI + 90)%360*PI/180);
}


void S_MainGame::update( float dt )
{
	updateAnim();

	m_smartstring->_update();

	//m_wheel.sprite->setRotation(tick *6);
	m_wheel.sprite->setPosition(m_wheel.sprite->getPositionX() + m_wheel.speed / 2 * sin(m_wheel.angle) + m_wheel.speed * sin(m_wheel.rotatedAngle),
		m_wheel.sprite->getPositionY() + m_wheel.speed / 2 * cos(m_wheel.angle) + m_wheel.speed * cos(m_wheel.rotatedAngle));
	m_wheel.rotatedAngle += m_wheel.rotate*m_wheel.speed*PI/180;

	// colision
	float borderPosition;
	// colision right side
	borderPosition = E::visibleWidth - BORDER_WIDTH - m_wheel.sprite->getBoundingBox().size.width * 0.5 * 0.775;
	if(m_wheel.sprite->getPositionX() > borderPosition){ 
		((LabelTTF*)this->getChildByTag(32))->setString("r_"+std::to_string(m_wheel.angle));
		m_wheel.angle = -m_wheel.angle;
		m_wheel.rotatedAngle = m_wheel.angle;
		/*
		m_wheel.rotate++;
		if(m_wheel.rotate == 3){
		m_wheel.rotate = -2;
		}
		*/
		m_wheel.sprite->setPositionX(borderPosition);
		E::setRandomColor(m_wheel.sprite);
	}
	// colision left side
	borderPosition = BORDER_WIDTH + m_wheel.sprite->getBoundingBox().size.width * 0.5 * 0.775;
	if(m_wheel.sprite->getPositionX() < borderPosition){ 
		((LabelTTF*)this->getChildByTag(32))->setString("l_"+std::to_string(m_wheel.angle));
		m_wheel.angle = -m_wheel.angle;
		m_wheel.rotatedAngle = m_wheel.angle;
		/*
		m_wheel.rotate--;
		if(m_wheel.rotate == -3){
		m_wheel.rotate = 2;
		}
		*/
		m_wheel.sprite->setPositionX(borderPosition);
		E::setRandomColor(m_wheel.sprite);
	}
	float angle_ = angleMinus90(m_wheel.angle);
	//colision top side
	borderPosition = E::visibleHeight - BORDER_WIDTH - m_wheel.sprite->getBoundingBox().size.width * 0.5 * 0.775;
	if(m_wheel.sprite->getPositionY() > borderPosition){ 
		((LabelTTF*)this->getChildByTag(32))->setString("t_"+std::to_string(-angle_));
		m_wheel.angle = anglePlus90(-angle_);
		m_wheel.rotatedAngle = m_wheel.angle;
		m_wheel.sprite->setPositionY(borderPosition);
		E::setRandomColor(m_wheel.sprite);
	}
	//colision bottom side
	borderPosition = BORDER_WIDTH + m_wheel.sprite->getBoundingBox().size.width * 0.5 * 0.775;
	if(m_wheel.sprite->getPositionY() < borderPosition && !m_isGameOver){ 
		/*
		((LabelTTF*)this->getChildByTag(32))->setString("b_"+std::to_string(-angle_));
		m_wheel.angle = anglePlus90(-angle_);
		m_wheel.rotatedAngle = m_wheel.angle;
		m_wheel.sprite->setPositionY(borderPosition);
		E::setRandomColor(m_wheel.sprite);
		*/
		m_isGameOver=true;
		m_tick2=0;
	}

	//smart string colision 
	/*
	switch(m_smartstring->checkCollision(m_wheel.sprite->getPosition(), getWheelRadius())){
	case 1:
		((LabelTTF*)this->getChildByTag(32))->setString("left");
		m_wheel.angle = -m_wheel.angle;
		m_wheel.rotatedAngle = m_wheel.angle;
		m_wheel.speed = m_wheel.speed*0.5+m_smartstring->getSpeed() ;
		E::setRandomColor(m_wheel.sprite);
		break;
	case 2:
		((LabelTTF*)this->getChildByTag(32))->setString("right");
		m_wheel.angle = -m_wheel.angle;
		m_wheel.rotatedAngle = m_wheel.angle;
		m_wheel.speed = m_wheel.speed*0.5+m_smartstring->getSpeed();
		E::setRandomColor(m_wheel.sprite);
		break;
	case 3:
		((LabelTTF*)this->getChildByTag(32))->setString("up");
		m_wheel.angle = anglePlus90(-angle_);
		m_wheel.rotatedAngle = m_wheel.angle;
		m_wheel.speed =m_wheel.speed*0.5+m_smartstring->getSpeed();
		E::setRandomColor(m_wheel.sprite);
		break;
	}
	*/
	if(m_smartstring->checkCollision(m_wheel.sprite->getPosition(), getWheelRadius())){
		//anglePlus90(-angle_);
		/*
		if(m_wheel.sprite->getPositionX() - (m_smartstring->getPositionX()+m_smartstring->getRadius()+m_smartstring->getWidth()/2)>0){
			m_wheel.angle += 10*PI/180;
		}else{
			m_wheel.angle -= 10*PI/180;
		}
		*/
		m_wheel.angle = 0;
		if(m_smartstring->getWidth()>1)
			m_wheel.angle =(m_wheel.sprite->getPositionX() - 
				(m_smartstring->getPositionX()+m_smartstring->getRadius()+m_smartstring->getWidth()/2)
				)/m_smartstring->getWidth() * 90 *PI/180;
		m_wheel.rotatedAngle = m_wheel.angle;
		m_wheel.speed =m_wheel.speed*0.5+m_smartstring->getSpeed();
		E::setRandomColor(m_wheel.sprite);
	}
}

void S_MainGame::onKeyReleased(EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
	// Back button pressed
	if (keyCode == EventKeyboard::KeyCode::KEY_BACKSPACE) {
		m_wheel.sprite->setPosition(E::visibleWidth/2,  E::visibleHeight/2);
		m_wheel.angle += 30 * PI / 180.0;
		m_wheel.rotatedAngle = m_wheel.angle;
	}


}


bool S_MainGame::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{   
	cocos2d::Vec2 p = touch->getLocation();

	if(Rect(0, 0, E::visibleWidth*E::scale, E::visibleHeight*0.3f*E::scale).containsPoint(p))
	{
		m_smartstring->setStartingPoint(p);
		return true; // event consumed
	}

	return false; // event past thru
}

void S_MainGame::onTouchMoved(Touch* touch, Event* event){
	//this->ccTouchBegan(touch, event);
	m_smartstring->setEndingPoint(touch->getLocation());
}

void S_MainGame::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event){
	m_smartstring->setEndingPoint(touch->getLocation());
	m_smartstring->go();
}

float S_MainGame::getWheelRadius(){
	return m_wheel.sprite->getContentSize().width * m_wheel.sprite->getScale() /2;
}
 ;
void S_MainGame::restartGame(){
	m_isGameOver = false;
	m_isRestarting = false;
	m_wheel.speed = 0;
	m_wheel.rotate = 0;//60*PI/180.0;
	m_wheel.angle = 180*PI/180.0;
	m_wheel.rotatedAngle = m_wheel.angle;
	m_wheel.sprite->setPosition(E::visibleWidth/2, E::visibleHeight*0.20f);
}