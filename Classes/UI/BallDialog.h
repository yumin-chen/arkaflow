#ifndef _BALLDIALOG_H_
#define _BALLDIALOG_H_

#include "cocos2d.h"

class BallDialog : public cocos2d::Sprite
{
    public:
        BallDialog();
        ~BallDialog();
        static BallDialog* create(const std::string = "", const cocos2d::ccMenuCallback& callbackOK = nullptr, const cocos2d::ccMenuCallback& callbackCancel = nullptr);
		void runAnimations();

    private:
		cocos2d::Label* m_contentLabel;
		cocos2d::Sprite* m_innerSprite;
		cocos2d::Menu* m_menu;
		cocos2d::ccMenuCallback m_callbackOK;
		cocos2d::ccMenuCallback m_callbackCancel;
		void initOpt();
		void menuCallback(cocos2d::Ref* pSender);

};

#endif // _BALLDIALOG_H_
