#include "stdafx.h"
#include "EngineHelper.h"
#include "Ring.h"

USING_NS_CC;

Ring::Ring() {
}

Ring::~Ring() {
}

Ring* Ring::create() {
	Ring *sprite = new (std::nothrow) Ring();
    if (sprite && sprite->initWithFile("ring_o.png"))
    {
        sprite->autorelease();
		sprite->initOpt();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

void Ring::initOpt() {

}

void Ring::setOpacity(GLubyte o){
	Sprite::setOpacity(o);
	auto children = this->getChildren();
	for (Vector<Node*>::iterator it = children.begin() ; it != children.end(); ++it)
	{
		(*it)->setOpacity(o);
	}
}