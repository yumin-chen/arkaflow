#ifndef _SMARTSTRING_H_
#define _SMARTSTRING_H_

#include "cocos2d.h"

#define SS_SPEEDRATIO 300
class SmartString : public cocos2d::Sprite
{
    public:
        SmartString();
        ~SmartString();
        static SmartString* create();
		void go();
		void stopGoing();
		void update(float dt);
		void onContactWithBall();
		virtual void setPosition(const cocos2d::Vec2& pos);
		virtual void setPositionY(float y);
		void setStartingPoint(const cocos2d::Vec2& p);
		void setEndingPoint(const cocos2d::Vec2& p);
		void setWidth(int w);
		void setColors(int color);
		void setOpacity(GLubyte opacity);
		float getRadius();
		float getMaxWidth();
		float getSpeed();
		float getWidth();
		cocos2d::Vec2 m_startingPoint;

    private:
		cocos2d::PhysicsBody* m_pBody;
		cocos2d::Sprite* m_middle;
		cocos2d::Sprite* m_right;
		cocos2d::Sprite* m_leftInner;
		cocos2d::Sprite* m_middleInner;
		cocos2d::Sprite* m_rightInner;
		void animFadeOut();
		void initOpt();
		void detachBody();
		void _updatePosition();
		float m_deltaDiff;
		bool m_isGoing;
		int m_width;
		float m_speed;

};

#endif // _SMARTSTRING_H_
