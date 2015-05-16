#ifndef __LEVEL_23_H__
#define __LEVEL_23_H__

#include "EngineHelper.h"
#include "BaseLevel.h"

class Level23 : public BaseLevel
{
public:
    virtual bool init();  
	virtual void restart();
	virtual void update(float);
	virtual int getLevel(){return 23;};
    CREATE_FUNC(Level23); 
private:
};

#endif // __LEVEL_23_H__
