#ifndef _RING_H_
#define _RING_H_

#include "EngineHelper.h"

class Ring: public cocos2d::Sprite
{
    public:
        Ring();
        ~Ring();
		static Ring* create();
		SETOPACITY_FUNC(Sprite);
    private:
		void initOpt();
		
};

#endif // _RING_H_
