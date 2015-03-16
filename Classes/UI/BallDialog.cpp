#include "stdafx.h"
#include "EngineHelper.h"
#include "BallDialog.h"
#include "BallButton.h"

USING_NS_CC;

#define TAG_OK			0
#define TAG_CANCEL		1

BallDialog::BallDialog() {
}

BallDialog::~BallDialog() {
}

BallDialog* BallDialog::create(const std::string content, const cocos2d::ccMenuCallback& callbackOK, const cocos2d::ccMenuCallback& callbackCancel)
{
	BallDialog *sprite = new (std::nothrow) BallDialog();
    if (sprite && sprite->initWithFile("ui/dialog_o.png"))
    {
        sprite->autorelease();
		sprite->m_contentLabel = Label::createWithTTF(content, FONT_MAIN, 60, 
			Size(sprite->getContentSize().width * 0.75f, sprite->getContentSize().height), TextHAlignment::CENTER, TextVAlignment::CENTER);
		sprite->initOpt();
		sprite->runAnimations();
		sprite->m_callbackOK = callbackOK;
		sprite->m_callbackCancel = callbackCancel;
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

void BallDialog::initOpt(){
	setColor(C3B(E::P.C600));
	m_innerSprite = Sprite::create("ui/dialog_i.png");
	m_innerSprite->setColor(C3B(E::P.C50));
	m_innerSprite->setAnchorPoint(Vec2(0, 0));
	//m_contentLabel->setAnchorPoint(Vec2(0, 0));
	m_contentLabel->setPosition(m_innerSprite->getContentSize().width / 2, m_innerSprite->getContentSize().height / 2);
	m_contentLabel->setColor(C3B(E::P.C900));
	m_innerSprite->addChild(m_contentLabel);
	addChild(m_innerSprite);

	auto sOkIcon = Sprite::create("b_ok.png");
	sOkIcon->setColor(C3B(E::P.C50));
	sOkIcon->setAnchorPoint(Vec2(0, 0));

	auto sCancelIcon = Sprite::create("b_cancel.png");
	sCancelIcon->setColor(C3B(E::P.C50));
	sCancelIcon->setAnchorPoint(Vec2(0, 0));

	auto OkItem = MenuItemSprite::create(
		BallButton::create(E::P.C700),
		BallButton::create(E::P2.C500),
		CC_CALLBACK_1(BallDialog::menuCallback, this));

	OkItem->setScale(0.8f);
	OkItem->setTag(TAG_OK);
	OkItem->addChild(sOkIcon);

	auto cancelItem = MenuItemSprite::create(
		BallButton::create(E::P.C700),
		BallButton::create(E::P2.C500),
		CC_CALLBACK_1(BallDialog::menuCallback, this));

	cancelItem->setScale(0.8f);
	cancelItem->setTag(TAG_CANCEL);
	cancelItem->addChild(sCancelIcon);


	// create menu
	m_menu = Menu::create(OkItem, cancelItem, NULL);
	m_menu->setPosition(Vec2(m_innerSprite->getContentSize().width / 2, m_innerSprite->getContentSize().height / 2));
	m_menu->setAnchorPoint(Vec2(0, 0));
	m_menu->alignItemsHorizontallyWithPadding(128 + 64);
	m_menu->setScale(0.1f);
	this->addChild(m_menu, 1);
	
	this->setScale(0.1f);
	this->setOpacity(0);
	m_menu->setOpacity(0);
	m_innerSprite->setOpacity(0);
	m_contentLabel->setOpacity(0);
}

void BallDialog::runAnimations(){
	this->runAction(ScaleBy::create(0.4f, 6.0f));
	this->runAction(FadeIn::create(0.4f));
	m_menu->runAction(FadeIn::create(0.4f));
	m_menu->runAction(ScaleBy::create(0.4f, 10.0f));
	m_menu->runAction(MoveBy::create(0.4f, Vec2(0,  - 128 - 64)));
	m_innerSprite->runAction(FadeIn::create(0.4f));
	m_contentLabel->runAction(FadeIn::create(0.4f));
}

void BallDialog::menuCallback(Ref* pSender)
{
	auto pMenuItem = (MenuItem*)pSender;
	auto tag = pMenuItem->getTag();
	switch(tag)
	{
	case TAG_OK:
		{
			if(m_callbackOK)
			{
				E::playEffect("da");
				m_callbackOK(this);
			}
			this->removeFromParentAndCleanup(true);
			break;
		}

	case TAG_CANCEL:
		{
			if(m_callbackCancel)
			{
				E::playEffect("da");
				m_callbackCancel(this);
			}
			this->removeFromParentAndCleanup(true);
			break;
		}
	}

}