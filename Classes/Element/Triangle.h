#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include "EngineHelper.h"

class Triangle: public cocos2d::Sprite
{
    public:
        Triangle();
        ~Triangle();
		static Triangle* create();
		SETOPACITY_FUNC(Sprite);
		void initBody();
    private:
		void initOpt();
		
};

#endif // _TRIANGLE_H_
