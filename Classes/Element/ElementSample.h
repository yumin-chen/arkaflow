#ifndef _RING_H_
#define _RING_H_

#include "EngineHelper.h"

class Ring: public cocos2d::Sprite
{
    public:
        Ring();
        ~Ring();
		static Ring* create();
		void setOpacity(GLubyte);
    private:
		void initOpt();
		
};

#endif // _RING_H_
