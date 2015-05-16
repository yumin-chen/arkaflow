#ifndef __LEVEL_3_H__
#define __LEVEL_3_H__

#include "EngineHelper.h"
#include "BaseLevel.h"
#include "../Element/Target.h"
#include "../Element/Ring.h"

class Level3 : public BaseLevel
{
public:
    virtual bool init();  
	virtual void restart();
	virtual void update(float);
	virtual int getLevel(){return 3;};
    CREATE_FUNC(Level3); 
private:
	Ring* ring1;
	Ring* ring2;
	float angle;
};

#endif // __LEVEL_3_H__
