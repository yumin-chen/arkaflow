#ifndef __LEVEL_1_H__
#define __LEVEL_1_H__

#include "EngineHelper.h"
#include "BaseLevel.h"
#include "../Element/Target.h"

class Level1 : public BaseLevel
{
public:
    virtual bool init();  
	virtual void restart();
	virtual void update(float);
	virtual int getLevel(){return 1;};
    CREATE_FUNC(Level1); 
private:
};

#endif // __LEVEL_1_H__
