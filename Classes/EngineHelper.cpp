#include "stdafx.h"
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
int E::language = 0;

struct sys_settings	E::settings;

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

void E::playEffect(const char* pszFilePath){
	char *fp = new char[strlen(pszFilePath) + 10];
	strcpy (fp, "audio/");
	strcat (fp, pszFilePath);
	strcat (fp, AEX);
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(fp);
}

void E::playBgMusic(){
	std::ostringstream os;
	os << "audio/bgmusic" << 1 + rand() % 2 << AEX;
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(os.str().c_str(), true);
}


int E::C50;
int E::C100;
int E::C200;
int E::C300;
int E::C400;
int E::C500;
int E::C600;
int E::C700;
int E::C800;
int E::C900;
int E::A100;
int E::A200;
int E::A400;
int E::A700;

void E::setColorAccent(int id){
	switch(id){
	case C_RED:
		E::C50=0xFFEBEE;
		E::C100=0xFFCDD2;
		E::C200=0xEF9A9A;
		E::C300=0xE57373;
		E::C400=0xEF5350;
		E::C500=0xF44336;
		E::C600=0xE53935;
		E::C700=0xD32F2F;
		E::C800=0xC62828;
		E::C900=0xB71C1C;
		E::A100=0xFF8A80;
		E::A200=0xFF5252;
		E::A400=0xFF1744;
		E::A700=0xD50000;
		break;
	case C_PINK:
		E::C50=0xFCE4EC;
		E::C100=0xF8BBD0;
		E::C200=0xF48FB1;
		E::C300=0xF06292;
		E::C400=0xEC407A;
		E::C500=0xE91E63;
		E::C600=0xD81B60;
		E::C700=0xC2185B;
		E::C800=0xAD1457;
		E::C900=0x880E4F;
		E::A100=0xFF80AB;
		E::A200=0xFF4081;
		E::A400=0xF50057;
		E::A700=0xC51162;
		break;
	case C_PURPLE:
		E::C50=0xF3E5F5;
		E::C100=0xE1BEE7;
		E::C200=0xCE93D8;
		E::C300=0xBA68C8;
		E::C400=0xAB47BC;
		E::C500=0x9C27B0;
		E::C600=0x8E24AA;
		E::C700=0x7B1FA2;
		E::C800=0x6A1B9A;
		E::C900=0x4A148C;
		E::A100=0xEA80FC;
		E::A200=0xE040FB;
		E::A400=0xD500F9;
		E::A700=0xAA00FF;
		break;
	case C_DEEPPURPLE:
		E::C50=0xEDE7F6;
		E::C100=0xD1C4E9;
		E::C200=0xB39DDB;
		E::C300=0x9575CD;
		E::C400=0x7E57C2;
		E::C500=0x673AB7;
		E::C600=0x5E35B1;
		E::C700=0x512DA8;
		E::C800=0x4527A0;
		E::C900=0x311B92;
		E::A100=0xB388FF;
		E::A200=0x7C4DFF;
		E::A400=0x651FFF;
		E::A700=0x6200EA;
		break;
	case C_INDIGO:
		E::C50=0xE8EAF6;
		E::C100=0xC5CAE9;
		E::C200=0x9FA8DA;
		E::C300=0x7986CB;
		E::C400=0x5C6BC0;
		E::C500=0x3F51B5;
		E::C600=0x3949AB;
		E::C700=0x303F9F;
		E::C800=0x283593;
		E::C900=0x1A237E;
		E::A100=0x8C9EFF;
		E::A200=0x536DFE;
		E::A400=0x3D5AFE;
		E::A700=0x304FFE;
		break;
	case C_BLUE:
		E::C50=0xE3F2FD;
		E::C100=0xBBDEFB;
		E::C200=0x90CAF9;
		E::C300=0x64B5F6;
		E::C400=0x42A5F5;
		E::C500=0x2196F3;
		E::C600=0x1E88E5;
		E::C700=0x1976D2;
		E::C800=0x1565C0;
		E::C900=0x0D47A1;
		E::A100=0x82B1FF;
		E::A200=0x448AFF;
		E::A400=0x2979FF;
		E::A700=0x2962FF;
		break;
	case C_LIGHTBLUE:
		E::C50=0xE1F5FE;
		E::C100=0xB3E5FC;
		E::C200=0x81D4FA;
		E::C300=0x4FC3F7;
		E::C400=0x29B6F6;
		E::C500=0x03A9F4;
		E::C600=0x039BE5;
		E::C700=0x0288D1;
		E::C800=0x0277BD;
		E::C900=0x01579B;
		E::A100=0x80D8FF;
		E::A200=0x40C4FF;
		E::A400=0x00B0FF;
		E::A700=0x0091EA;
		break;
	case C_CYAN:
		E::C50=0xE0F7FA;
		E::C100=0xB2EBF2;
		E::C200=0x80DEEA;
		E::C300=0x4DD0E1;
		E::C400=0x26C6DA;
		E::C500=0x00BCD4;
		E::C600=0x00ACC1;
		E::C700=0x0097A7;
		E::C800=0x00838F;
		E::C900=0x006064;
		E::A100=0x84FFFF;
		E::A200=0x18FFFF;
		E::A400=0x00E5FF;
		E::A700=0x00B8D4;
		break;
	case C_TEAL: 
		E::C50	=0xE0F2F1;
		E::C100	=0xB2DFDB;
		E::C200	=0x80CBC4;
		E::C300	=0x4DB6AC;
		E::C400	=0x26A69A;
		E::C500	=0x009688;
		E::C600	=0x00897B;
		E::C700	=0x00796B;
		E::C800	=0x00695C;
		E::C900	=0x004D40;
		E::A100	=0xA7FFEB;
		E::A200	=0x64FFDA;
		E::A400	=0x1DE9B6;
		E::A700	=0x00BFA5;
		break;
	case C_GREEN:
		E::C50=0xE8F5E9;
		E::C100=0xC8E6C9;
		E::C200=0xA5D6A7;
		E::C300=0x81C784;
		E::C400=0x66BB6A;
		E::C500=0x4CAF50;
		E::C600=0x43A047;
		E::C700=0x388E3C;
		E::C800=0x2E7D32;
		E::C900=0x1B5E20;
		E::A100=0xB9F6CA;
		E::A200=0x69F0AE;
		E::A400=0x00E676;
		E::A700=0x00C853;
		break;
	case C_LIGHTGREEN:
		E::C50=0xF1F8E9;
		E::C100=0xDCEDC8;
		E::C200=0xC5E1A5;
		E::C300=0xAED581;
		E::C400=0x9CCC65;
		E::C500=0x8BC34A;
		E::C600=0x7CB342;
		E::C700=0x689F38;
		E::C800=0x558B2F;
		E::C900=0x33691E;
		E::A100=0xCCFF90;
		E::A200=0xB2FF59;
		E::A400=0x76FF03;
		E::A700=0x64DD17;
		break;
	case C_LIME:
		E::C50=0xF9FBE7;
		E::C100=0xF0F4C3;
		E::C200=0xE6EE9C;
		E::C300=0xDCE775;
		E::C400=0xD4E157;
		E::C500=0xCDDC39;
		E::C600=0xC0CA33;
		E::C700=0xAFB42B;
		E::C800=0x9E9D24;
		E::C900=0x827717;
		E::A100=0xF4FF81;
		E::A200=0xEEFF41;
		E::A400=0xC6FF00;
		E::A700=0xAEEA00;
		break;
	case C_YELLOW:
		E::C50=0xFFFDE7;
		E::C100=0xFFF9C4;
		E::C200=0xFFF59D;
		E::C300=0xFFF176;
		E::C400=0xFFEE58;
		E::C500=0xFFEB3B;
		E::C600=0xFDD835;
		E::C700=0xFBC02D;
		E::C800=0xF9A825;
		E::C900=0xF57F17;
		E::A100=0xFFFF8D;
		E::A200=0xFFFF00;
		E::A400=0xFFEA00;
		E::A700=0xFFD600;
		break;
	case C_AMBER:
		E::C50=0xFFF8E1;
		E::C100=0xFFECB3;
		E::C200=0xFFE082;
		E::C300=0xFFD54F;
		E::C400=0xFFCA28;
		E::C500=0xFFC107;
		E::C600=0xFFB300;
		E::C700=0xFFA000;
		E::C800=0xFF8F00;
		E::C900=0xFF6F00;
		E::A100=0xFFE57F;
		E::A200=0xFFD740;
		E::A400=0xFFC400;
		E::A700=0xFFAB00;
		break;
	case C_ORANGE:
		E::C50=0xFFF3E0;
		E::C100=0xFFE0B2;
		E::C200=0xFFCC80;
		E::C300=0xFFB74D;
		E::C400=0xFFA726;
		E::C500=0xFF9800;
		E::C600=0xFB8C00;
		E::C700=0xF57C00;
		E::C800=0xEF6C00;
		E::C900=0xE65100;
		E::A100=0xFFD180;
		E::A200=0xFFAB40;
		E::A400=0xFF9100;
		E::A700=0xFF6D00;
		break;
	case C_DEEPORANGE:
		E::C50=0xFBE9E7;
		E::C100=0xFFCCBC;
		E::C200=0xFFAB91;
		E::C300=0xFF8A65;
		E::C400=0xFF7043;
		E::C500=0xFF5722;
		E::C600=0xF4511E;
		E::C700=0xE64A19;
		E::C800=0xD84315;
		E::C900=0xBF360C;
		E::A100=0xFF9E80;
		E::A200=0xFF6E40;
		E::A400=0xFF3D00;
		E::A700=0xDD2C00;
		break;
	}
}


void E::setRandomColor(cocos2d::Node *n){
	switch(rand() % 14){
	case 0:
		n->setColor(cocos2d::C3B(E::C50));
		break;
	case 1:
		n->setColor(cocos2d::C3B(E::C100));
		break;
	case 2:
		n->setColor(cocos2d::C3B(E::C200));
		break;
	case 3:
		n->setColor(cocos2d::C3B(E::C300));
		break;
	case 4:
		n->setColor(cocos2d::C3B(E::C400));
		break;
	case 5:
		n->setColor(cocos2d::C3B(E::C500));
		break;
	case 6:
		n->setColor(cocos2d::C3B(E::C600));
		break;
	case 7:
		n->setColor(cocos2d::C3B(E::C700));
		break;
	case 8:
		n->setColor(cocos2d::C3B(E::C800));
		break;
	case 9:
		n->setColor(cocos2d::C3B(E::C900));
		break;
	case 10:
		n->setColor(cocos2d::C3B(E::A100));
		break;
	case 11:
		n->setColor(cocos2d::C3B(E::A200));
		break;
	case 12:
		n->setColor(cocos2d::C3B(E::A400));
		break;
	case 13:
		n->setColor(cocos2d::C3B(E::A700));
		break;
	}

}
