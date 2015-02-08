#ifndef  _ENGINE_HELPER_H_
#define  _ENGINE_HELPER_H_

#include "cocos2d.h"

#define PI 3.141592653589793238462643383279502884197169399375105820974944592307816406286

#define DESIGNED_WIDTH 480
#define DESIGNED_HEIGHT 640

#define FONT_MAIN "Arial"

#define C_RED			0
#define C_PINK			1
#define C_PURPLE		2
#define C_DEEPPURPLE	3
#define C_INDIGO		4
#define C_BLUE			5
#define C_LIGHTBLUE		6
#define C_CYAN			7
#define C_TEAL			8
#define C_GREEN			9
#define C_LIGHTGREEN	10
#define C_LIME			11
#define C_YELLOW		12
#define C_AMBER			13
#define C_ORANGE		14
#define C_DEEPORANGE	15

#define C4B(color) Color4B((color & 0xFF0000) >> 16, (color & 0x00FF00) >> 8, color & 0x0000FF, 255)
#define C4F(color) Color4F(((color & 0xFF0000) >> 16)/255.0f, ((color & 0x00FF00) >> 8)/255.0f, (color & 0x0000FF)/255.0f, 1.0f)
#define C3B(color) Color3B((color & 0xFF0000) >> 16, (color & 0x00FF00) >> 8, color & 0x0000FF)

struct sys_settings{
	int colorAccent;
};

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

	static struct sys_settings settings;


	// For Color Palette
	static void setColorAccent(int ID);
	static int C50;
	static int C100;
	static int C200;
	static int C300;
	static int C400;
	static int C500;
	static int C600;
	static int C700;
	static int C800;
	static int C900;
	static int A100;
	static int A200;
	static int A400;
	static int A700;
};


inline float angleMinus90(float angle){
	return float((int(angle*180/PI + 270)%360*PI/180));
}

inline float anglePlus90(float angle){
	return float((int(angle*180/PI + 90)%360*PI/180));
}

#endif // _ENGINE_HELPER_H_

