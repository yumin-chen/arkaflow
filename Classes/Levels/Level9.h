#ifndef __LEVEL_9_H__
#define __LEVEL_9_H__

#include "EngineHelper.h"
#include "BaseLevel.h"
#include "Element/Ring.h"

class Level9 : public BaseLevel
{
public:
    virtual bool init();  
	virtual void restart();
	virtual void update(float);
	virtual int getLevel(){return 9;};
    CREATE_FUNC(Level9); 
private:
};

#endif // __LEVEL_9_H__
