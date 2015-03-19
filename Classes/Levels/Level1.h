#ifndef __LEVEL_1_H__
#define __LEVEL_1_H__

#include "EngineHelper.h"
#include "BaseLevel.h"

class Level1 : public BaseLevel
{
public:
    virtual bool init();  
	virtual void update(float);
    CREATE_FUNC(Level1); 
};

#endif // __LEVEL_1_H__
