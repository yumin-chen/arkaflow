#ifndef _DIAMOND_H_
#define _DIAMOND_H_

#include "EngineHelper.h"

class Diamond: public cocos2d::Sprite
{
    public:
        Diamond();
        ~Diamond();
		static Diamond* create();
		SETOPACITY_FUNC(Sprite);
		void initBody();
    private:
		void initOpt();
		
};

#endif // _DIAMOND_H_
