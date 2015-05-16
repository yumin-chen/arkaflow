#ifndef __LEVEL_11_H__
#define __LEVEL_11_H__

#include "EngineHelper.h"
#include "BaseLevel.h"
#include "../Element/Target.h"
#include "../Element/Diamond.h"

class Level11 : public BaseLevel
{
public:
    virtual bool init();  
	virtual void restart();
	virtual void update(float);
	virtual int getLevel(){return 11;};
    CREATE_FUNC(Level11); 
private:
	Diamond* diamond;
	float angle;
};

#endif // __LEVEL_11_H__
