#ifndef __LEVEL_10_H__
#define __LEVEL_10_H__

#include "EngineHelper.h"
#include "BaseLevel.h"
#include "Element/Target.h"

class Level10 : public BaseLevel
{
public:
    virtual bool init();  
	virtual void restart();
	virtual void update(float);
	virtual int getLevel(){return 10;};
    CREATE_FUNC(Level10); 
private:
};

#endif // __LEVEL_10_H__
