#include "stdafx.h"
#include "Levels.h"
#include "Levels/Level1.h"
#include "Levels/Level2.h"

BaseLevel* Levels::createLevel(int level)
{
	switch(level){
	case 1:
		return Level1::create();
	case 2:
		return Level2::create();
	}
	return nullptr;
}
