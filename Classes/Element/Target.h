#ifndef _TARGET_H_
#define _TARGET_H_

#include "EngineHelper.h"
#include "Block.h"

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
    private:
		void initOpt();
		void _updateProtectorPosition();
		Block* block1;
		Block* block2;
		Block* block3;
		
};

#endif // _TARGET_H_
