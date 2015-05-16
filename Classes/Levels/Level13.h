#ifndef __LEVEL_13_H__
#define __LEVEL_13_H__

#include "EngineHelper.h"
#include "BaseLevel.h"
#include "../Element/Target.h"
#include "../Element/Ring.h"

class Level13 : public BaseLevel
{
public:
    virtual bool init();  
	virtual void restart();
	virtual void update(float);
	virtual int getLevel(){return 13;};
    CREATE_FUNC(Level13); 
private:
	Ring* ring1;
	Ring* ring2;
	float angle;
};

#endif // __LEVEL_13_H__
