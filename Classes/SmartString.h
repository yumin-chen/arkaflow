#ifndef _SMARTSTRING_H_
#define _SMARTSTRING_H_

#include "cocos2d.h"
#include "MainBall.h"
using namespace cocos2d;

#define SS_SPEEDRATIO 4
#define SS_ANI_MOVING 20.0f
class SmartString : public cocos2d::Sprite
{
    public:
        SmartString();
        ~SmartString();
        static SmartString* create();
		void go();
		void _update();
		virtual void setPosition(const Vec2& pos);
		virtual void setPositionY(float y);
		void setStartingPoint(const Vec2& p);
		void setEndingPoint(const Vec2& p);
		void setWidth(int w);
		void setColors(int color);
		void setOpacity(GLubyte opacity);
		float getRadius();
		float getMaxWidth();
		float getSpeed();
		float getWidth();
		bool isEnemy;
		Vec2 m_startingPoint;
		int checkCollision(MainBall *wheel);

    private:
		cocos2d::Sprite* m_middle;
		cocos2d::Sprite* m_right;
		void initOpt();
		void _updatePosition();
		bool m_isGoing;
		long m_tick;
		int m_width;
		float m_speed;

};

#endif // _SMARTSTRING_H_
