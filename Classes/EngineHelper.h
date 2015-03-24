#ifndef  _ENGINE_HELPER_H_
#define  _ENGINE_HELPER_H_

#include "cocos2d.h"
#include <SimpleAudioEngine.h>

#define VERSION "1.0"

#define PI 3.141592653589793238462643383279502884197169399375105820974944592307816406286

#define DESIGNED_WIDTH 480
#define DESIGNED_HEIGHT 800

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
#define C_RANDOM		16

#define C4B(color) Color4B((color & 0xFF0000) >> 16, (color & 0x00FF00) >> 8, color & 0x0000FF, 255)
#define C4B_(color, alpha) Color4B((color & 0xFF0000) >> 16, (color & 0x00FF00) >> 8, color & 0x0000FF, alpha)
#define C4F(color) Color4F(((color & 0xFF0000) >> 16)/255.0f, ((color & 0x00FF00) >> 8)/255.0f, (color & 0x0000FF)/255.0f, 1.0f)
#define C4F_(color, alpha) Color4F(((color & 0xFF0000) >> 16)/255.0f, ((color & 0x00FF00) >> 8)/255.0f, (color & 0x0000FF)/255.0f, alpha)
#define C3B(color) Color3B((color & 0xFF0000) >> 16, (color & 0x00FF00) >> 8, color & 0x0000FF)

struct sys_settings{
	int colorAccent;
	int musicVolume;
	int soundVolume;
	bool musicEnabled;
	bool soundEnabled;
	int currentLevel;
	int unlockedLevel;
};
#define UD_COLOR_ACCENT "q"
#define UD_MUSIC_VOLUME "w"
#define UD_SOUND_VOLUME "e"
#define UD_MUSIC_ENABLED "r"
#define UD_SOUND_ENABLED "t"
#define UD_CURRENT_LEVEL "y"
#define UD_UNLOCKED_LEVEL "u"


typedef struct{
	int C50;
	int C100;
	int C200;
	int C300;
	int C400;
	int C500;
	int C600;
	int C700;
	int C800;
	int C900;
	int A100;
	int A200;
	int A400;
	int A700;
} ColorPalette;

class E
{
public:
	static float scale;
	static float visibleWidth;
	static float visibleHeight;
	static float originX;
	static float originY;
	static int language;
	static void calculateScreen();
	static void setRandomColor(cocos2d::Node *n);
	static void playEffect(const char* pszFilePath);
	static void playBgMusic();

	static struct sys_settings settings;


	// For Color Palette
	static void setColorAccent(int ID);
	static void getColorPaletteFromID(ColorPalette&, int ID);
	static ColorPalette P;
	static ColorPalette P2;
};

typedef struct{
	int id;
	std::function<bool(cocos2d::Touch*, cocos2d::Event*)> onTouchBegan;
    std::function<void(cocos2d::Touch*, cocos2d::Event*)> onTouchMoved;
    std::function<void(cocos2d::Touch*, cocos2d::Event*)> onTouchEnded;
    std::function<void(cocos2d::Touch*, cocos2d::Event*)> onTouchCancelled;
} TouchEventsFunc;


typedef struct{
	int id;
	std::function<bool(cocos2d::EventKeyboard::KeyCode, cocos2d::Event*)> onKeyPressed;
    std::function<bool(cocos2d::EventKeyboard::KeyCode, cocos2d::Event*)> onKeyReleased;
} KeyboardEventsFunc;


namespace stdPatchForMinGW
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

// define audio extension
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#define AEX ".ogg"
#define stdp stdPatchForMinGW
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#define AEX ".wav"
#define stdp std
#else
#define AEX ".mp3"
#define stdp std
#endif

#define S(english,chinese) E::language==0? english: chinese

#define GAME_TITLE S("Ching Chong Ping Pong", "乾坤弹球")

//#define FONT_MAIN S("Arial", "微软雅黑")
#define FONT_MAIN S("fonts/SF Theramin Gothic Condensed.ttf", "fonts/Chinese Font.ttf")
#define FONT_BOLD S("fonts/SF Theramin Gothic Bold.ttf", "fonts/Chinese Font.ttf")

#define SMOOTH_MATERIAL PhysicsMaterial(0.0f, 1.0f, 0.0f)

#define _LEVEL(l) Level##l


#define SETOPACITY_FUNC(__PARENT__) \
virtual void setOpacity(GLubyte opacity) \
{ \
	__PARENT__::setOpacity(opacity); \
	auto children = this->getChildren(); \
	for (cocos2d::Vector<cocos2d::Node*>::iterator it = children.begin() ; it != children.end(); ++it) \
	{ \
		(*it)->setOpacity(opacity); \
	} \
}

#endif // _ENGINE_HELPER_H_ 

