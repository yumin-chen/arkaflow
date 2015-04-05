#ifndef __LEVEL_24_H__
#define __LEVEL_24_H__

#include "EngineHelper.h"
#include "BaseLevel.h"
#include "Element/Target.h"
#include "Element/Ring.h"

class Level24 : public BaseLevel
{
public:
    virtual bool init();  
	virtual void restart();
	virtual void update(float);
	virtual int getLevel(){return 24;};
    CREATE_FUNC(Level24); 
private:
};

#endif // __LEVEL_24_H__
