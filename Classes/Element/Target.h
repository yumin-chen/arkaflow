#ifndef _TARGET_H_
#define _TARGET_H_

#include "EngineHelper.h"
#include "Brick.h"

class Target: public cocos2d::Sprite
{
    public:
        Target();
        ~Target();
		static Target* create();
		void beHit();
		void initBody();
		void playAnim(int);
		void initProtector(float width = 128);
		virtual void setPosition(float x, float y);
		SETOPACITY_FUNC(Sprite);
		static int targetNum;
		bool bAlreadyHit;
		void enableArtificialIntelligence();
    private:
		void initOpt();
		void _updateProtectorPosition();
		void _updateAI();
		Brick* block1;
		Brick* block2;
		Brick* block3;
		
};

#endif // _TARGET_H_
