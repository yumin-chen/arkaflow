#ifndef _BALLBUTTON_HPP_
#define _BALLBUTTON_HPP_

#include "cocos2d.h"


class BallButton : public cocos2d::Sprite
{
    public:
        BallButton();
        ~BallButton();
        static BallButton* create(const int normalColor,const int selectedColor = 0, const cocos2d::ccMenuCallback& callback = nullptr);
		void setVisible(bool visibility);

    private:
		void addEvents();
		void _updateColor();
		bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
		void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
		void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
		void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event);
		cocos2d::ccMenuCallback m_callback;
		int m_state;
		bool m_isEnabled;
		int m_normalColor;
		int m_selectedColor;
		//size_t m_listenerIndex;
};

#endif // _BALLBUTTON_HPP_
