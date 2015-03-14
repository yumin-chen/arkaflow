#ifndef _BALLSLIDER_HPP_
#define _BALLSLIDER_HPP_

#include "cocos2d.h"
#include "ui/CocosGUI.h"


class BallSlider : public cocos2d::ui::Slider
{
    public:
        BallSlider();
        ~BallSlider();
		static BallSlider* create();
		void initRenderers();
		void updateColors();
		void setWidth(float);

    private:
		void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unusedEvent);

};

#endif // _BALLSLIDER_HPP_
