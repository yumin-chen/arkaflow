#ifndef __LEVEL_7_H__
#define __LEVEL_7_H__

#include "EngineHelper.h"
#include "BaseLevel.h"
#include "Element/Ring.h"

class Level7 : public BaseLevel
{
public:
    virtual bool init();  
	virtual void restart();
	virtual void update(float);
	virtual int getLevel(){return 7;};
    CREATE_FUNC(Level7); 
private:
	Ring* ring;
};

#endif // __LEVEL_7_H__
