#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "EngineHelper.h"

class Block: public cocos2d::LayerColor
{
    public:
        Block();
        ~Block();
		static Block* create(float width = 320, float height = 16, int color = E::P.C400);
		SETOPACITY_FUNC(LayerColor);
		void initBody();
    private:
		void initOpt(float width, float height);
		
};

#endif // _BLOCK_H_
