#include "stdafx.h"
#include "EngineHelper.h"
#include "EdgedBallButton.h"

USING_NS_CC;

EdgedBallButton::EdgedBallButton() {
}

EdgedBallButton::~EdgedBallButton() {
}

EdgedBallButton* EdgedBallButton::create(const cocos2d::ccMenuCallback& callback)
{
	EdgedBallButton *sprite = new (std::nothrow) EdgedBallButton();
    if (sprite && sprite->initWithFile("ui/dialog_o.png"))
    {
        sprite->autorelease();
		sprite->initOpt();
		sprite->runAnimations();
		sprite->m_callback = callback;
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

void EdgedBallButton::initOpt(){
	setColor(C3B(E::P.C600));
	m_innerSprite = Sprite::create("ui/dialog_i.png");
	m_innerSprite->setColor(C3B(E::P.C50));
	m_innerSprite->setAnchorPoint(Vec2(0, 0));
	addChild(m_innerSprite);

	m_innerSprite->setOpacity(0);
	this->setOpacity(0);
}

void EdgedBallButton::runAnimations(){
	//this->runAction(ScaleBy::create(0.4f, 6.0f));
	this->runAction(FadeIn::create(0.4f));
	m_innerSprite->runAction(FadeIn::create(0.4f));
	//m_innerSprite->runAction(FadeIn::create(0.4f));
}