#ifndef __LEVEL_19_H__
#define __LEVEL_19_H__

#include "EngineHelper.h"
#include "BaseLevel.h"
#include "Element/Ring.h"

class Level19 : public BaseLevel
{
public:
    virtual bool init();  
	virtual void restart();
	virtual void update(float);
	virtual int getLevel(){return 19;};
    CREATE_FUNC(Level19); 
private:
	Ring* ring;
};

#endif // __LEVEL_19_H__
