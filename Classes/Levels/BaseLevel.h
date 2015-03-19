#ifndef __BASE_LEVEL_H__
#define __BASE_LEVEL_H__

#include "EngineHelper.h"

class BaseLevel : public cocos2d::LayerColor
{
public:
    virtual bool init(); 
    virtual void setOpacity(GLubyte opacity);
	virtual void update(float) = 0;
};

#endif // __BASE_LEVEL_H__
