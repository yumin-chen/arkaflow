#include "stdafx.h"
#include "Levels.h"
#include "Levels/Level1.h"
#include "Levels/Level2.h"
#include "Levels/Level3.h"
#include "Levels/Level4.h"
#include "Levels/Level5.h"
#include "Levels/Level6.h"
#include "Levels/Level7.h"
#include "Levels/Level8.h"
#include "Levels/Level9.h"

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
	case 5:
		return Level5::create();
	case 6:
		return Level6::create();
	case 7:
		return Level7::create();
	case 8:
		return Level8::create();
	case 9:
		return Level9::create();
	}
	return nullptr;
}
