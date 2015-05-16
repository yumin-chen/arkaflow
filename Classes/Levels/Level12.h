#ifndef __LEVEL_12_H__
#define __LEVEL_12_H__

#include "EngineHelper.h"
#include "BaseLevel.h"
#include "../Element/Target.h"

class Level12 : public BaseLevel
{
public:
    virtual bool init();  
	virtual void restart();
	virtual void update(float);
	virtual int getLevel(){return 12;};
    CREATE_FUNC(Level12); 
private:
};

#endif // __LEVEL_12_H__
