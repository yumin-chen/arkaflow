#ifndef  _ENGINE_HELPER_H_
#define  _ENGINE_HELPER_H_

#include "cocos2d.h"
#include "Palette.h"

#define DESIGNED_WIDTH 480
#define DESIGNED_HEIGHT 640

class E
{
public:
	static float scale;
	static float visibleWidth;
	static float visibleHeight;
	static float originX;
	static float originY;
	static void calculateScreen();
	static void setRandomColor(cocos2d::Node *n);
};


#endif // _ENGINE_HELPER_H_