#ifndef __LEVEL_2_H__
#define __LEVEL_2_H__

#include "EngineHelper.h"
#include "BaseLevel.h"

class Level2 : public BaseLevel
{
public:
    virtual bool init();  
	virtual void restart();
	virtual void update(float);
	virtual int getLevel(){return 2;};
    CREATE_FUNC(Level2); 
};

#endif // __LEVEL_2_H__
