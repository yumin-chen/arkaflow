#ifndef _TARGET_H_
#define _TARGET_H_

#include "EngineHelper.h"

class Target: public cocos2d::Sprite
{
    public:
        Target();
        ~Target();
		static Target* create();
		void beHit();
		void initBody();
		void playAnim(int);
		SETOPACITY_FUNC(Sprite);
		static int targetNum;
    private:
		bool bAlreadyHit;
		void initOpt();
		
};

#endif // _TARGET_H_
