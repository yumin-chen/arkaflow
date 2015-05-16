#ifndef _BRICK_H_
#define _BRICK_H_

#include "EngineHelper.h"

class Brick: public cocos2d::LayerColor
{
    public:
        Brick();
        ~Brick();
		static Brick* create(float width = 320, float height = 16, int color = E::P.C400);
		SETOPACITY_FUNC(LayerColor);
		void initBody();
	protected:
		void initOpt(float width, float height);
    private:
		
};

#endif // _BRICK_H_
