#ifndef __LEVEL_15_H__
#define __LEVEL_15_H__

#include "EngineHelper.h"
#include "BaseLevel.h"

class Level15 : public BaseLevel
{
public:
    virtual bool init();  
	virtual void restart();
	virtual void update(float);
	virtual int getLevel(){return 15;};
    CREATE_FUNC(Level15); 
};

#endif // __LEVEL_15_H__
