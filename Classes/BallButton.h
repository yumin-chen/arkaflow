#ifndef _BALLBUTTON_HPP_
#define _BALLBUTTON_HPP_

#include "cocos2d.h"


class BallButton : public cocos2d::Sprite
{
    public:
        BallButton();
        ~BallButton();
        static BallButton* create(const int* normalColor,const int* selectedColor = nullptr, const cocos2d::ccMenuCallback& callback = nullptr);
		const int* normalColor;
		const int* selectedColor;
		int state;
		void _updateColor();
		static void s_updateColors();

    private:

		void addEvents();
		cocos2d::EventListenerTouchOneByOne* listener;
		cocos2d::ccMenuCallback m_callback;
};

#endif // _BALLBUTTON_HPP_