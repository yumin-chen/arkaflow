#ifndef __LEVEL_9_H__
#define __LEVEL_9_H__

#include "EngineHelper.h"
#include "BaseLevel.h"
#include "../Element/Target.h"
#include "../Element/Ring.h"

class Level9 : public BaseLevel
{
public:
    virtual bool init();  
	virtual void restart();
	virtual void update(float);
	virtual int getLevel(){return 9;};
    CREATE_FUNC(Level9); 
private:
	Ring* ring1;
	Ring* ring2;
	Ring* ring3;
	Ring* ring4;
};

#endif // __LEVEL_9_H__
