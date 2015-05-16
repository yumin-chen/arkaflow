#ifndef __LEVEL_20_H__
#define __LEVEL_20_H__

#include "EngineHelper.h"
#include "BaseLevel.h"
#include "../Element/Target.h"
#include "../Element/Ring.h"

class Level20 : public BaseLevel
{
public:
    virtual bool init();  
	virtual void restart();
	virtual void update(float);
	virtual int getLevel(){return 20;};
    CREATE_FUNC(Level20); 
private:
};

#endif // __LEVEL_20_H__
