#ifndef _EDGEDBALLBUTTON_H_
#define _EDGEDBALLBUTTON_H_

#include "cocos2d.h"

class EdgedBallButton : public cocos2d::Sprite
{
    public:
        EdgedBallButton();
        ~EdgedBallButton();
        static EdgedBallButton* create(const cocos2d::ccMenuCallback& callback = nullptr);
		void runAnimations();

    private:
		cocos2d::Sprite* m_innerSprite;
		cocos2d::ccMenuCallback m_callback;
		void initOpt();

};

#endif // _EDGEDBALLBUTTON_H_
