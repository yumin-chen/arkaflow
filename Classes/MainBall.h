#ifndef _MAINBALL_H_
#define _MAINBALL_H_

#include "cocos2d.h"

class MainBall
{
    public:
        MainBall();
        ~MainBall();
		cocos2d::Sprite* sprite;
		float speed; // the absolute speed
		float angle; // the moving direction angle
		float rotate; // used to calculate the rotated angle, this value is best between (-4, 4)
		float rotatedAngle; // influence the direction angle
		bool isReal; // determine if this is the real ball or just for AI calculation
		cocos2d::Vec2 position;
		void setPosition(float x, float y);
		void setPositionX(float x);
		void setPositionY(float y);
		float getRadius();
    private:
		
};

#endif // _MAINBALL_H_
