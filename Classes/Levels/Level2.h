#ifndef __LEVEL_2_H__
#define __LEVEL_2_H__

#include "EngineHelper.h"
#include "BaseLevel.h"

class Level2 : public BaseLevel
{
public:
    virtual bool init();  
	virtual void update(float);
    CREATE_FUNC(Level2); 
};

#endif // __LEVEL_2_H__
