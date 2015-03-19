#include "stdafx.h"
#include "BaseLevel.h"
#include "Scene/MainGameScene.h"
#include "UI/TitleBar.h"

USING_NS_CC;

bool BaseLevel::init()
{
	if ( !LayerColor::initWithColor(C4B(E::P.C50)) )
	{
		return false;
	}
	this->setContentSize(Size(E::visibleWidth, E::visibleHeight - GAME_BTM_HEIGHT - TITLEBAR_HEIGHT));
	this->setAnchorPoint(Vec2(0, 0));
	this->setPosition(0, GAME_BTM_HEIGHT);

	return true;
}


void BaseLevel::setOpacity(GLubyte o){
	LayerColor::setOpacity(o);
	auto children = this->getChildren();
	for (Vector<Node*>::iterator it = children.begin() ; it != children.end(); ++it)
	{
		(*it)->setOpacity(o);
	}
}