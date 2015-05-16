#ifndef __LEVEL_14_H__
#define __LEVEL_14_H__

#include "EngineHelper.h"
#include "BaseLevel.h"
#include "../Element/Ring.h"

class Level14 : public BaseLevel
{
public:
    virtual bool init();  
	virtual void restart();
	virtual void update(float);
	virtual int getLevel(){return 14;};
    CREATE_FUNC(Level14); 
private:
	Ring* ring1;
	Ring* ring2;
	Ring* ring3;
	Ring* ring4;
};

#endif // __LEVEL_14_H__
