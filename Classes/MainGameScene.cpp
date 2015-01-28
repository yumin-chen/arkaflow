#include "stdafx.h"
#include "MainGameScene.h"
#include "BallButton.h"

USING_NS_CC;
#define PI 3.141592653589793238462643383279502884197169399375105820974944592307816406286
#define BORDER_WIDTH 24;

#define	TAG_BTM_BG	1000
#define	TAG_SHADOW	1001


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
    // super init 

    if ( !LayerColor::initWithColor(C4B(E::C200)) )
    {
        return false;
    }

	
	this->setScale(E::scale);
	this->setContentSize(Size(E::visibleWidth, E::visibleHeight));
	this->setAnchorPoint(Vec2(0, 0));

	// create solid color background
	auto bg = BallButton::create(&E::C50);
	bg->setScale(0.3f);
	bg->setPosition(E::visibleWidth/2, 128+(-9/15.0f)*128);
	bg->setTag(TAG_BTM_BG);
	// add the wheel to the layer
	this->addChild(bg, 0);

	// create solid color background
	auto bgTop = LayerColor::create(C4B(E::C200));
	bgTop->setContentSize(Size(E::visibleWidth, E::visibleHeight*0.7));
	bgTop->setPosition(0, E::visibleHeight*0.3);
	// add the wheel to the layer
	this->addChild(bgTop, 0);
	
	// create the shadow
    auto shadow = Sprite::create("shadow.png");
    shadow->setScale(1.0f);
	shadow->setAnchorPoint(Vec2(0, 1));
	shadow->setPosition(0, E::visibleHeight * 0.3);
	shadow->setTag(TAG_SHADOW);
	shadow->setOpacity(0);
    this->addChild(shadow, 0);
    
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
	wheel->setPosition(E::visibleWidth/2, E::visibleHeight/2);
    // add the wheel to the layer
    this->addChild(wheel, 10);
	
	m_wheel.sprite = wheel;
	m_wheel.speed = 4;
	m_wheel.rotate = 0;//60*PI/180.0;
	m_wheel.angle =  30*PI/180.0;
	m_wheel.rotatedAngle = m_wheel.angle;
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

#define ANI_SCALING_BG	30.0f
void S_MainGame::update( float dt )
{
	static int tick = 0;
	if(tick <= ANI_SCALING_BG){
		this->getChildByTag(TAG_BTM_BG)->setScale(1 + (tick/ANI_SCALING_BG)*3.0f);
		this->getChildByTag(TAG_SHADOW)->setOpacity((tick/ANI_SCALING_BG)*255);
	}

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
		m_wheel.rotate++;
		if(m_wheel.rotate == 3){
			m_wheel.rotate = -2;
		}
		m_wheel.sprite->setPositionX(borderPosition);
		E::setRandomColor(m_wheel.sprite);
	}
	// colision left side
	borderPosition = BORDER_WIDTH + m_wheel.sprite->getBoundingBox().size.width * 0.5 * 0.775;
	if(m_wheel.sprite->getPositionX() < borderPosition){ 
		((LabelTTF*)this->getChildByTag(32))->setString("l_"+std::to_string(m_wheel.angle));
		m_wheel.angle = -m_wheel.angle;
		m_wheel.rotatedAngle = m_wheel.angle;
		m_wheel.rotate--;
		if(m_wheel.rotate == -3){
			m_wheel.rotate = 2;
		}
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
	if(m_wheel.sprite->getPositionY() < borderPosition){ 
		((LabelTTF*)this->getChildByTag(32))->setString("b_"+std::to_string(-angle_));
		m_wheel.angle = anglePlus90(-angle_);
		m_wheel.rotatedAngle = m_wheel.angle;
		m_wheel.sprite->setPositionY(borderPosition);
		E::setRandomColor(m_wheel.sprite);
	}


	tick ++;
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

