#ifndef __LEVEL_16_H__
#define __LEVEL_16_H__

#include "EngineHelper.h"
#include "BaseLevel.h"
#include "../Element/Target.h"

class Level16 : public BaseLevel
{
public:
    virtual bool init();  
	virtual void restart();
	virtual void update(float);
	virtual int getLevel(){return 16;};
    CREATE_FUNC(Level16); 
private:
	float angle;
	Target* t1;
	Target* t2;
};

#endif // __LEVEL_16_H__
