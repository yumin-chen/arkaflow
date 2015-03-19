#ifndef _TARGET_H_
#define _TARGET_H_

#include "EngineHelper.h"

class Target: public cocos2d::Sprite
{
    public:
        Target();
        ~Target();
		static Target* create();
		void setOpacity(GLubyte);
		void beHit();
		void initBody();
    private:
		void initOpt();
		
};

#endif // _TARGET_H_
