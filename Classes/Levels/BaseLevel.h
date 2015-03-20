#ifndef __BASE_LEVEL_H__
#define __BASE_LEVEL_H__

#include "EngineHelper.h"

class BaseLevel : public cocos2d::LayerColor
{
public:
    virtual bool init(); 
	virtual void restart();
	virtual void update(float) = 0;
	virtual int getLevel() = 0;
	SETOPACITY_FUNC(LayerColor);
};

#endif // __BASE_LEVEL_H__
