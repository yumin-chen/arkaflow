#ifndef __MAIN_GAME_SCENE_H__
#define __MAIN_GAME_SCENE_H__

#include "EngineHelper.h"

struct WheelAttr{
	cocos2d::Sprite* sprite;
	float speed; // the absolute speed
	float angle; // the moving direction angle
	float rotate; // used to calculate the rotated angle, this value is best between (-4, 4)
	float rotatedAngle; // influence the direction angle
};

class S_MainGame : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();  
    
    void update( float dt );

	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
    
    CREATE_FUNC(S_MainGame);

private:
	inline float angleMinus90(float angle);

	inline float anglePlus90(float angle);

	WheelAttr m_wheel; 
};

#endif // __MAIN_GAME_SCENE_H__
