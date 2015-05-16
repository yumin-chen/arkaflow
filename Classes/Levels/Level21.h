#ifndef __LEVEL_21_H__
#define __LEVEL_21_H__

#include "EngineHelper.h"
#include "BaseLevel.h"
#include "../Element/Target.h"
#include "../Element/Ring.h"

class Level21 : public BaseLevel
{
public:
    virtual bool init();  
	virtual void restart();
	virtual void update(float);
	virtual int getLevel(){return 21;};
    CREATE_FUNC(Level21); 
private:
	Ring* ring1;
	Ring* ring2;
	Ring* ring3;
	Ring* ring4;
	
	Ring* ring21;
	Ring* ring22;
	Ring* ring23;
	Ring* ring24;
};

#endif // __LEVEL_21_H__
