#ifndef __LEVEL_8_H__
#define __LEVEL_8_H__

#include "EngineHelper.h"
#include "BaseLevel.h"
#include "../Element/Ring.h"

class Level8 : public BaseLevel
{
public:
    virtual bool init();  
	virtual void restart();
	virtual void update(float);
	virtual int getLevel(){return 8;};
    CREATE_FUNC(Level8); 
private:
	Ring* ring;
};

#endif // __LEVEL_8_H__
