#ifndef __LEVEL_17_H__
#define __LEVEL_17_H__

#include "EngineHelper.h"
#include "BaseLevel.h"
#include "../Element/Target.h"
#include "../Element/Ring.h"

class Level17 : public BaseLevel
{
public:
    virtual bool init();  
	virtual void restart();
	virtual void update(float);
	virtual int getLevel(){return 17;};
    CREATE_FUNC(Level17); 
private:
};

#endif // __LEVEL_17_H__
