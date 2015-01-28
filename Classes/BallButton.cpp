#include "stdafx.h"
#include "BallButton.h"
#include "EngineHelper.h"

#define NORMAL 0
#define SELECTED 1

static std::vector<BallButton*> v;

BallButton::BallButton() {v.push_back(this);}

BallButton::~BallButton() {
	cocos2d::Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
	std::vector<BallButton*>::iterator it;
	for (it = v.begin(); it != v.end(); it++){
		if(*it == this){
			v.erase(it);
			return;
		}
	}
}

BallButton* BallButton::create(const int* normalColor, const int* selectedColor, const cocos2d::ccMenuCallback& callback)
{
	BallButton* pSprite = new BallButton();

	if (pSprite->initWithFile("ball.png"))
	{
		pSprite->autorelease();
		pSprite->normalColor = normalColor;
		pSprite->selectedColor = selectedColor;
		pSprite->m_callback = callback;
		pSprite->setColor(cocos2d::C3B(*pSprite->normalColor));
		pSprite->state = NORMAL;
		if(selectedColor != nullptr || callback != nullptr){
			pSprite->addEvents();
		}
		return pSprite;
	}

	CC_SAFE_DELETE(pSprite);
	return NULL;
}



void BallButton::addEvents()
{
	listener = cocos2d::EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = [&](cocos2d::Touch* touch, cocos2d::Event* event)
	{   
		cocos2d::Vec2 p = touch->getLocation();
		cocos2d::Rect rect = this->getBoundingBox();
		rect.origin.x *= E::scale;
		rect.origin.y *= E::scale;
		rect.size.width *= E::scale;
		rect.size.height *= E::scale;

		if(rect.containsPoint(p))
		{
			this->state = SELECTED;
			_updateColor();
			return true; // to indicate that we have consumed it.
		}

		return false; // we did not consume this event, pass thru.
	};

	listener->onTouchEnded = [=](cocos2d::Touch* touch, cocos2d::Event* event)
	{
		this->state = NORMAL;
		_updateColor();
		if( m_callback )
		{
			m_callback(this);
		}
	};

	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 30);
}

void BallButton::_updateColor(){
	if(this->state == NORMAL){
		this->setColor(cocos2d::C3B(*this->normalColor));
	}
	else{
		this->setColor(cocos2d::C3B(*this->selectedColor));
	}
}

void BallButton::s_updateColors(){
	std::vector<BallButton*>::iterator it;
	for (it = v.begin(); it != v.end(); it++){
		(*it)->_updateColor();
	}
}