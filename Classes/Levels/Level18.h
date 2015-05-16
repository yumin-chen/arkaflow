#ifndef __LEVEL_18_H__
#define __LEVEL_18_H__

#include "EngineHelper.h"
#include "BaseLevel.h"
#include "../Element/Target.h"
#include "../Element/Ring.h"

class Level18 : public BaseLevel
{
public:
    virtual bool init();  
	virtual void restart();
	virtual void update(float);
	virtual int getLevel(){return 18;};
    CREATE_FUNC(Level18); 
private:
};

#endif // __LEVEL_18_H__
