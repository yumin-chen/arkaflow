#ifndef _SMARTSTRING_H_
#define _SMARTSTRING_H_

#include "cocos2d.h"
using namespace cocos2d;

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
		int checkCollision(const Vec2& p, float radius);

    private:
		cocos2d::Sprite* m_middle;
		cocos2d::Sprite* m_right;
		void initOpt();
		void _updatePosition();
		bool m_isGoing;
		long m_tick;
		int m_width;
		float m_speed;
		Vec2 m_startingPoint;

};

#endif // _SMARTSTRING_H_
