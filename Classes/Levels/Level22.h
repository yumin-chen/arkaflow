#ifndef __LEVEL_22_H__
#define __LEVEL_22_H__

#include "EngineHelper.h"
#include "BaseLevel.h"
#include "Element/Ring.h"

class Level22 : public BaseLevel
{
public:
    virtual bool init();  
	virtual void restart();
	virtual void update(float);
	virtual int getLevel(){return 22;};
    CREATE_FUNC(Level22); 
private:
	Ring* ring;
};

#endif // __LEVEL_22_H__
