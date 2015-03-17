#ifndef _TITLEBAR_H_
#define _TITLEBAR_H_

#include "cocos2d.h"

#define TITLEBAR_HEIGHT	80

class TitleBar : public cocos2d::LayerColor
{
    public:
        TitleBar();
        ~TitleBar();
        static TitleBar* create(const std::string = "");
		void updateColors();
		void fadeOut();
		void setString(const std::string);

    private:
		void initLabel(const std::string title);
		cocos2d::Label* m_titleLabel;

};

#endif // _TITLEBAR_H_
