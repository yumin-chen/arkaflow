#include "stdafx.h"
#include "EngineHelper.h"
#include "TitleBar.h"

USING_NS_CC;

#define TITLE_HEIGHT	80


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
		layer->setContentSize(Size(E::visibleWidth, TITLE_HEIGHT));
		layer->setPosition(0, E::visibleHeight);

		// create the shadow
		auto shadow = Sprite::create("shadow.png");
		//shadow->setScale(1.0f);
		shadow->setAnchorPoint(Vec2(0, 1));
		shadow->setScaleX(E::visibleWidth / DESIGNED_WIDTH);
		shadow->setScaleY(0.5f);
		shadow->setOpacity(192);
		layer->addChild(shadow, 0);

		// create title label
		if(!title.empty()){
			layer->m_titleLabel = Label::createWithSystemFont(title, FONT_BOLD, 40, 
				Size(E::visibleWidth, TITLE_HEIGHT), TextHAlignment::CENTER, TextVAlignment::CENTER);
			layer->m_titleLabel->setPosition(0, TITLE_HEIGHT/2);
			layer->m_titleLabel->setAnchorPoint(Vec2(0, 0.5));
			//layer->m_titleLabel->enableOutline(Color4B(255, 255, 255, 255), 8);
			//m_titleLabel->enableOutline(C4B(E::P.C900), 1);
			//layer->m_titleLabel->setString(title);
			layer->m_titleLabel->enableShadow(Color4B(0, 0, 0, 128), Size(2, -2));
			layer->m_titleLabel->setColor(Color3B(255, 255, 255));
			//layer->m_titleLabel->addChild( layer->m_titleLabel->createStroke(lbl, 0.4, lbl->getColor(), 255) );
			layer->addChild(layer->m_titleLabel, 1);
		}

		auto moveTo = MoveTo::create(0.4f , Vec2(0, E::visibleHeight - TITLE_HEIGHT));
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