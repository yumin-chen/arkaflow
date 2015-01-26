#ifndef __MAIN_GAME_SCENE_H__
#define __MAIN_GAME_SCENE_H__

#include "EngineHelper.h"

#define MAIN_MARGIN_SCALE (24/128.0)

// these are tags for elements in this scene
#define	TAG_BTM_BG	1000

struct WheelAttr{
	cocos2d::Sprite* sprite;
	float speed; // the absolute speed
	float angle; // the moving direction angle
	float rotate; // used to calculate the rotated angle, this value is best between (-4, 4)
	float rotatedAngle; // influence the direction angle
};

class MainGame : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();  
    
    void update( float dt );

	virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags);

	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
    
    CREATE_FUNC(MainGame);

private:
	inline float angleMinus90(float angle);

	inline float anglePlus90(float angle);

    void onDrawPrimitives(const cocos2d::Mat4 &transform, uint32_t flags);

    cocos2d::CustomCommand m_drawPrimitives;

	WheelAttr m_wheel; 
};

#endif // __MAIN_GAME_SCENE_H__
