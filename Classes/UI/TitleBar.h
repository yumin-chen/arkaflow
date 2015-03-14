#ifndef _TITLEBAR_H_
#define _TITLEBAR_H_

#include "cocos2d.h"

class TitleBar : public cocos2d::LayerColor
{
    public:
        TitleBar();
        ~TitleBar();
        static TitleBar* create(const std::string = "");
		void updateColors();

    private:
		cocos2d::Label* m_titleLabel;

};

#endif // _TITLEBAR_H_
