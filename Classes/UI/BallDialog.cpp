#include "stdafx.h"
#include "EngineHelper.h"
#include "../Scene/BaseScene.h"
#include "BallDialog.h"
#include "BallButton.h"

USING_NS_CC;

#define TAG_OK			0
#define TAG_CANCEL		1

BallDialog::BallDialog() {
	m_referencer = nullptr;
}

BallDialog::~BallDialog() {
}

BallDialog* BallDialog::create(const std::string content, const std::function<void(void)>& callbackOK, const std::function<void(void)>& callbackCancel, const std::string ok_sprite, const std::string cancel_sprite)
{
	BallDialog *sprite = new (std::nothrow) BallDialog();
	if (sprite && sprite->initWithTexture(Director::getInstance()->getTextureCache()->addImage("ui/dialog_o.png")))
    {
        sprite->autorelease();
		sprite->m_contentLabel = Label::createWithTTF(content, FONT_MAIN, 60, 
			Size(sprite->getContentSize().width * 0.75f, sprite->getContentSize().height), TextHAlignment::CENTER, TextVAlignment::CENTER);
		sprite->initOpt(ok_sprite, cancel_sprite);
		sprite->runAnimations(false);
		sprite->m_callbackOK = callbackOK;
		sprite->m_callbackCancel = callbackCancel;
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

void BallDialog::initOpt(const std::string ok_sprite, const std::string cancel_sprite){
	setPosition(E::visibleWidth / 2, E::visibleHeight / 2);
	setColor(C3B(E::P.C600));
	m_innerSprite = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->addImage("ui/dialog_i.png"));
	m_innerSprite->setColor(C3B(E::P.C50));
	m_innerSprite->setAnchorPoint(Vec2(0, 0));
	//m_contentLabel->setAnchorPoint(Vec2(0, 0));
	m_contentLabel->setPosition(m_innerSprite->getContentSize().width / 2, m_innerSprite->getContentSize().height / 2 + 32);
	m_contentLabel->setColor(C3B(E::P.C900));
	m_innerSprite->addChild(m_contentLabel);
	addChild(m_innerSprite);

	auto sOkIcon = Sprite::create(ok_sprite);
	sOkIcon->setColor(C3B(E::P.C50));
	sOkIcon->setAnchorPoint(Vec2(0, 0));

	auto sCancelIcon = Sprite::create(cancel_sprite);
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

void BallDialog::onEnter(){
	Sprite::onEnter();
	if(m_listenerId != -1)
	{
		BaseScene::getCurrentScene()->removeKeyboardEvents(m_listenerId);
		m_listenerId = -1;
	}
	addEvents();
}

void BallDialog::onExit(){
	Sprite::onExit();
	if(m_listenerId != -1)
	{
		BaseScene::getCurrentScene()->removeKeyboardEvents(m_listenerId);
		m_listenerId = -1;
	}
}

void BallDialog::addEvents()
{
	KeyboardEventsFunc listener;
	listener.onKeyPressed = nullptr;
	listener.onKeyReleased = CC_CALLBACK_2(BallDialog::onKeyReleased, this);
	m_listenerId = BaseScene::getCurrentScene()->addKeyboardEvents(listener);
}


bool BallDialog::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event){
	// Back button pressed
	if (keyCode == EventKeyboard::KeyCode::KEY_BACK || keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {
		m_resultTag = TAG_CANCEL;
		runAnimations(true);
		return true; // event consumed
	}
	// Enter key pressed
	else if (keyCode == EventKeyboard::KeyCode::KEY_KP_ENTER || keyCode == EventKeyboard::KeyCode::KEY_ENTER) {
		m_resultTag = TAG_OK;
		runAnimations(true);
		return true; // event consumed
	}
	return false; // event pass through
}

void BallDialog::runAnimations(bool bReverse){
	this->runAction(bReverse? ScaleBy::create(0.4f, 1 / 6.0f): ScaleBy::create(0.4f, 6.0f));
	cocos2d::Action* fade;
	if(bReverse){fade = FadeOut::create(0.4f);}
	else{fade = FadeIn::create(0.4f);}
	this->runAction(fade);
	m_menu->runAction(fade->clone());
	m_menu->runAction(bReverse? ScaleBy::create(0.4f, 0.1f): ScaleBy::create(0.4f, 10.0f));
	m_menu->runAction(MoveBy::create(0.4f, Vec2(0, (128 + 64) * (int(bReverse) * 2 - 1))));
	m_innerSprite->runAction(fade->clone());
	m_contentLabel->runAction(fade->clone());
	if(bReverse){
		auto callback =	CallFunc::create([this](){
			switch(m_resultTag)
			{
			case TAG_OK:
				{
					if(m_callbackOK)
					{
						E::playEffect("da");
						m_callbackOK();
					}
					break;
				}

			case TAG_CANCEL:
				{
					if(m_callbackCancel)
					{
						E::playEffect("da");
						m_callbackCancel();
					}
					break;
				}
			default:
				{
					break;
				}
			}
			this->removeFromParentAndCleanup(true);
			if(m_referencer != nullptr && *m_referencer != nullptr){
				*m_referencer = nullptr;
				m_referencer = nullptr;
			}
		});
		auto seq = Sequence::create(DelayTime::create(0.4f), callback, nullptr);
		this->runAction(seq);
	}
}

void BallDialog::menuCallback(Ref* pSender)
{
	auto pMenuItem = (MenuItem*)pSender;
	m_resultTag = pMenuItem->getTag();
	runAnimations(true);
}
