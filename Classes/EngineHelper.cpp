#include "EngineHelper.h"

	/**
	// this method is similar to the showAll resolution policy, but with this 
	// implementation, elements can be programmatically added to the outside of
	// the designed area. And things will be automatically scaled to fit the 
	// screen size
	*/
	float E::scale;
	float E::visibleWidth;
	float E::visibleHeight;
	float E::originX;
	float E::originY;
void E::calculateScreen(){
		cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
		cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();
		cocos2d::Size frameSize = cocos2d::Director::getInstance()->getOpenGLView()->getFrameSize();
		float scaleX = frameSize.width / DESIGNED_WIDTH;
		float scaleY = frameSize.height / DESIGNED_HEIGHT;
		E::scale = scaleX > scaleY? scaleY: scaleX;
		E::visibleWidth = frameSize.width / E::scale;
		E::visibleHeight = frameSize.height / E::scale;
		E::originX = (E::visibleWidth - DESIGNED_WIDTH)/2;
		E::originY = (E::visibleHeight - DESIGNED_HEIGHT)/2;
}

void E::setRandomColor(cocos2d::Node *n){
	switch(rand() % 14){
	case 0:
		n->setColor(cocos2d::C3B(COLOR_50));
		break;
	case 1:
		n->setColor(cocos2d::C3B(COLOR_100));
		break;
	case 2:
		n->setColor(cocos2d::C3B(COLOR_200));
		break;
	case 3:
		n->setColor(cocos2d::C3B(COLOR_300));
		break;
	case 4:
		n->setColor(cocos2d::C3B(COLOR_400));
		break;
	case 5:
		n->setColor(cocos2d::C3B(COLOR_500));
		break;
	case 6:
		n->setColor(cocos2d::C3B(COLOR_600));
		break;
	case 7:
		n->setColor(cocos2d::C3B(COLOR_700));
		break;
	case 8:
		n->setColor(cocos2d::C3B(COLOR_800));
		break;
	case 9:
		n->setColor(cocos2d::C3B(COLOR_900));
		break;
	case 10:
		n->setColor(cocos2d::C3B(COLOR_A100));
		break;
	case 11:
		n->setColor(cocos2d::C3B(COLOR_A200));
		break;
	case 12:
		n->setColor(cocos2d::C3B(COLOR_A400));
		break;
	case 13:
		n->setColor(cocos2d::C3B(COLOR_A700));
		break;
	}
		
}


