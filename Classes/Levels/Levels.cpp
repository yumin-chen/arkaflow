#include "stdafx.h"
#include "Levels.h"
#include "Levels/Level1.h"
#include "Levels/Level2.h"
#include "Levels/Level3.h"
#include "Levels/Level4.h"

BaseLevel* Levels::createLevel(int level)
{
	switch(level){
	case 1:
		return Level1::create();
	case 2:
		return Level2::create();
	case 3:
		return Level3::create();
	case 4:
		return Level4::create();
	}
	return nullptr;
}
