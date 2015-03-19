#ifndef _EDGEDBALLBUTTON_H_
#define _EDGEDBALLBUTTON_H_

#include "cocos2d.h"

class EdgedBallButton : public cocos2d::Sprite
{
    public:
        EdgedBallButton();
        ~EdgedBallButton();
        static EdgedBallButton* create(const cocos2d::ccMenuCallback& callback = nullptr);
		void setVisible(bool visibility);
		void runAnimations();
		void updateColors();

    private:
		void addEvents();
		void initOpt();
		bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
		void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
		void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
		void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event);
		int m_state;
		bool m_isEnabled;
		cocos2d::Sprite* m_innerSprite;
		cocos2d::ccMenuCallback m_callback;

};

#endif // _EDGEDBALLBUTTON_H_
