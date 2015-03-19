#ifndef __LEVELS_H__
#define __LEVELS_H__

#include "EngineHelper.h"
#include "BaseLevel.h"

class Levels 
{
public:
    static BaseLevel* createLevel(int level); 
};

#endif // __LEVELS_H__
