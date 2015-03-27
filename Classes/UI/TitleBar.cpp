#include "stdafx.h"
#include "EngineHelper.h"
#include "TitleBar.h"

USING_NS_CC;


TitleBar::TitleBar() {
}

TitleBar::~TitleBar() {
}

TitleBar* TitleBar::create(const std::string title)
{
    TitleBar * layer = new (std::nothrow) TitleBar();
    if(layer && layer->initWithColor(C4B(E::P.C500)))
    {
        layer->autorelease();
		layer->m_titleLabel = nullptr;
		layer->setContentSize(Size(E::visibleWidth, TITLEBAR_HEIGHT));
		layer->setPosition(0, E::visibleHeight);

		// create the shadow
		auto shadow = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->addImage("ui/shadow.png"));
		//shadow->setScale(1.0f);
		shadow->setAnchorPoint(Vec2(0, 1));
		shadow->setScaleX(E::visibleWidth / DESIGNED_WIDTH);
		shadow->setScaleY(0.5f);
		shadow->setOpacity(192);
		layer->addChild(shadow, 0);

		// create title label
		if(!title.empty()){
			layer->initLabel(title);
		}

		auto moveTo = MoveTo::create(0.4f , Vec2(0, E::visibleHeight - TITLEBAR_HEIGHT));
			layer->runAction(moveTo);

		/*
			auto fadeIn = FadeIn::create(2.0f);
			shadow->runAction(fadeIn);
			*/
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
}

void TitleBar::updateColors(){
	this->setColor(C3B(E::P.C500));
	//m_titleLabel->setColor(C3B(E::P.C50));
}

void TitleBar::fadeOut(){
	auto moveTo = MoveTo::create(0.4f , Vec2(0, E::visibleHeight));
	this->runAction(moveTo);
}

void TitleBar::setString(const std::string string){
	if(!m_titleLabel){initLabel(string);}
	else{m_titleLabel->setString(string);}
}

void TitleBar::initLabel(const std::string title){
	
			m_titleLabel = Label::createWithTTF(title, FONT_BOLD, 40, 
				Size(E::visibleWidth, TITLEBAR_HEIGHT), TextHAlignment::CENTER, TextVAlignment::CENTER);
			m_titleLabel->setPosition(0, TITLEBAR_HEIGHT/2);
			m_titleLabel->setAnchorPoint(Vec2(0, 0.5));
			//m_titleLabel->enableOutline(Color4B(255, 255, 255, 255), 8);
			//m_titleLabel->enableOutline(C4B(E::P.C900), 1);
			//m_titleLabel->setString(title);
			m_titleLabel->enableShadow(Color4B(0, 0, 0, 128), Size(2, -2));
			m_titleLabel->setColor(Color3B(255, 255, 255));
			//m_titleLabel->addChild( m_titleLabel->createStroke(lbl, 0.4, lbl->getColor(), 255) );
			addChild(m_titleLabel, 1);
}
