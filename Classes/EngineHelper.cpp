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
	if(!E::settings.soundEnabled) return;
	char *fp = new char[strlen(pszFilePath) + 10];
	strcpy (fp, "audio/");
	strcat (fp, pszFilePath);
	strcat (fp, AEX);
	CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(E::settings.soundVolume/100.0f);
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(fp);
}

void E::playBgMusic(){
	if(!E::settings.musicEnabled) return;
	std::ostringstream os;
	os << "audio/bgmusic" << 1 + rand() % 2 << AEX;
	CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(E::settings.musicVolume/100.0f);
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(os.str().c_str(), true);
}


ColorPalette E::P;
ColorPalette E::P2;

void E::setColorAccent(int id){
	E::getColorPaletteFromID(E::P, id);
	E::getColorPaletteFromID(E::P2, (id + 2) % 16);
}

void E::getColorPaletteFromID(ColorPalette& p, int id){
	switch(id){
	case C_RED:
		p.C50=0xFFEBEE;
		p.C100=0xFFCDD2;
		p.C200=0xEF9A9A;
		p.C300=0xE57373;
		p.C400=0xEF5350;
		p.C500=0xF44336;
		p.C600=0xE53935;
		p.C700=0xD32F2F;
		p.C800=0xC62828;
		p.C900=0xB71C1C;
		p.A100=0xFF8A80;
		p.A200=0xFF5252;
		p.A400=0xFF1744;
		p.A700=0xD50000;
		break;
	case C_PINK:
		p.C50=0xFCE4EC;
		p.C100=0xF8BBD0;
		p.C200=0xF48FB1;
		p.C300=0xF06292;
		p.C400=0xEC407A;
		p.C500=0xE91E63;
		p.C600=0xD81B60;
		p.C700=0xC2185B;
		p.C800=0xAD1457;
		p.C900=0x880E4F;
		p.A100=0xFF80AB;
		p.A200=0xFF4081;
		p.A400=0xF50057;
		p.A700=0xC51162;
		break;
	case C_PURPLE:
		p.C50=0xF3E5F5;
		p.C100=0xE1BEE7;
		p.C200=0xCE93D8;
		p.C300=0xBA68C8;
		p.C400=0xAB47BC;
		p.C500=0x9C27B0;
		p.C600=0x8E24AA;
		p.C700=0x7B1FA2;
		p.C800=0x6A1B9A;
		p.C900=0x4A148C;
		p.A100=0xEA80FC;
		p.A200=0xE040FB;
		p.A400=0xD500F9;
		p.A700=0xAA00FF;
		break;
	case C_DEEPPURPLE:
		p.C50=0xEDE7F6;
		p.C100=0xD1C4E9;
		p.C200=0xB39DDB;
		p.C300=0x9575CD;
		p.C400=0x7E57C2;
		p.C500=0x673AB7;
		p.C600=0x5E35B1;
		p.C700=0x512DA8;
		p.C800=0x4527A0;
		p.C900=0x311B92;
		p.A100=0xB388FF;
		p.A200=0x7C4DFF;
		p.A400=0x651FFF;
		p.A700=0x6200EA;
		break;
	case C_INDIGO:
		p.C50=0xE8EAF6;
		p.C100=0xC5CAE9;
		p.C200=0x9FA8DA;
		p.C300=0x7986CB;
		p.C400=0x5C6BC0;
		p.C500=0x3F51B5;
		p.C600=0x3949AB;
		p.C700=0x303F9F;
		p.C800=0x283593;
		p.C900=0x1A237E;
		p.A100=0x8C9EFF;
		p.A200=0x536DFE;
		p.A400=0x3D5AFE;
		p.A700=0x304FFE;
		break;
	case C_BLUE:
		p.C50=0xE3F2FD;
		p.C100=0xBBDEFB;
		p.C200=0x90CAF9;
		p.C300=0x64B5F6;
		p.C400=0x42A5F5;
		p.C500=0x2196F3;
		p.C600=0x1E88E5;
		p.C700=0x1976D2;
		p.C800=0x1565C0;
		p.C900=0x0D47A1;
		p.A100=0x82B1FF;
		p.A200=0x448AFF;
		p.A400=0x2979FF;
		p.A700=0x2962FF;
		break;
	case C_LIGHTBLUE:
		p.C50=0xE1F5FE;
		p.C100=0xB3E5FC;
		p.C200=0x81D4FA;
		p.C300=0x4FC3F7;
		p.C400=0x29B6F6;
		p.C500=0x03A9F4;
		p.C600=0x039BE5;
		p.C700=0x0288D1;
		p.C800=0x0277BD;
		p.C900=0x01579B;
		p.A100=0x80D8FF;
		p.A200=0x40C4FF;
		p.A400=0x00B0FF;
		p.A700=0x0091EA;
		break;
	case C_CYAN:
		p.C50=0xE0F7FA;
		p.C100=0xB2EBF2;
		p.C200=0x80DEEA;
		p.C300=0x4DD0E1;
		p.C400=0x26C6DA;
		p.C500=0x00BCD4;
		p.C600=0x00ACC1;
		p.C700=0x0097A7;
		p.C800=0x00838F;
		p.C900=0x006064;
		p.A100=0x84FFFF;
		p.A200=0x18FFFF;
		p.A400=0x00E5FF;
		p.A700=0x00B8D4;
		break;
	case C_TEAL: 
		p.C50	=0xE0F2F1;
		p.C100	=0xB2DFDB;
		p.C200	=0x80CBC4;
		p.C300	=0x4DB6AC;
		p.C400	=0x26A69A;
		p.C500	=0x009688;
		p.C600	=0x00897B;
		p.C700	=0x00796B;
		p.C800	=0x00695C;
		p.C900	=0x004D40;
		p.A100	=0xA7FFEB;
		p.A200	=0x64FFDA;
		p.A400	=0x1DE9B6;
		p.A700	=0x00BFA5;
		break;
	case C_GREEN:
		p.C50=0xE8F5E9;
		p.C100=0xC8E6C9;
		p.C200=0xA5D6A7;
		p.C300=0x81C784;
		p.C400=0x66BB6A;
		p.C500=0x4CAF50;
		p.C600=0x43A047;
		p.C700=0x388E3C;
		p.C800=0x2E7D32;
		p.C900=0x1B5E20;
		p.A100=0xB9F6CA;
		p.A200=0x69F0AE;
		p.A400=0x00E676;
		p.A700=0x00C853;
		break;
	case C_LIGHTGREEN:
		p.C50=0xF1F8E9;
		p.C100=0xDCEDC8;
		p.C200=0xC5E1A5;
		p.C300=0xAED581;
		p.C400=0x9CCC65;
		p.C500=0x8BC34A;
		p.C600=0x7CB342;
		p.C700=0x689F38;
		p.C800=0x558B2F;
		p.C900=0x33691E;
		p.A100=0xCCFF90;
		p.A200=0xB2FF59;
		p.A400=0x76FF03;
		p.A700=0x64DD17;
		break;
	case C_LIME:
		p.C50=0xF9FBE7;
		p.C100=0xF0F4C3;
		p.C200=0xE6EE9C;
		p.C300=0xDCE775;
		p.C400=0xD4E157;
		p.C500=0xCDDC39;
		p.C600=0xC0CA33;
		p.C700=0xAFB42B;
		p.C800=0x9E9D24;
		p.C900=0x827717;
		p.A100=0xF4FF81;
		p.A200=0xEEFF41;
		p.A400=0xC6FF00;
		p.A700=0xAEEA00;
		break;
	case C_YELLOW:
		p.C50=0xFFFDE7;
		p.C100=0xFFF9C4;
		p.C200=0xFFF59D;
		p.C300=0xFFF176;
		p.C400=0xFFEE58;
		p.C500=0xFFEB3B;
		p.C600=0xFDD835;
		p.C700=0xFBC02D;
		p.C800=0xF9A825;
		p.C900=0xF57F17;
		p.A100=0xFFFF8D;
		p.A200=0xFFFF00;
		p.A400=0xFFEA00;
		p.A700=0xFFD600;
		break;
	case C_AMBER:
		p.C50=0xFFF8E1;
		p.C100=0xFFECB3;
		p.C200=0xFFE082;
		p.C300=0xFFD54F;
		p.C400=0xFFCA28;
		p.C500=0xFFC107;
		p.C600=0xFFB300;
		p.C700=0xFFA000;
		p.C800=0xFF8F00;
		p.C900=0xFF6F00;
		p.A100=0xFFE57F;
		p.A200=0xFFD740;
		p.A400=0xFFC400;
		p.A700=0xFFAB00;
		break;
	case C_ORANGE:
		p.C50=0xFFF3E0;
		p.C100=0xFFE0B2;
		p.C200=0xFFCC80;
		p.C300=0xFFB74D;
		p.C400=0xFFA726;
		p.C500=0xFF9800;
		p.C600=0xFB8C00;
		p.C700=0xF57C00;
		p.C800=0xEF6C00;
		p.C900=0xE65100;
		p.A100=0xFFD180;
		p.A200=0xFFAB40;
		p.A400=0xFF9100;
		p.A700=0xFF6D00;
		break;
	case C_DEEPORANGE:
		p.C50=0xFBE9E7;
		p.C100=0xFFCCBC;
		p.C200=0xFFAB91;
		p.C300=0xFF8A65;
		p.C400=0xFF7043;
		p.C500=0xFF5722;
		p.C600=0xF4511E;
		p.C700=0xE64A19;
		p.C800=0xD84315;
		p.C900=0xBF360C;
		p.A100=0xFF9E80;
		p.A200=0xFF6E40;
		p.A400=0xFF3D00;
		p.A700=0xDD2C00;
		break;
	case C_RANDOM:
		{
			ColorPalette tempPalette;
			int r = rand();
			E::getColorPaletteFromID(tempPalette, r % 16);
			p.C50 = tempPalette.C50;
			r++;
			E::getColorPaletteFromID(tempPalette, r % 16);
			p.C100 = tempPalette.C100;
			r++;
			E::getColorPaletteFromID(tempPalette, r % 16);
			p.C200 = tempPalette.C200;
			r++;
			E::getColorPaletteFromID(tempPalette, r % 16);
			p.C300 = tempPalette.C300;
			r++;
			E::getColorPaletteFromID(tempPalette, r % 16);
			p.C400 = tempPalette.C400;
			r++;
			E::getColorPaletteFromID(tempPalette, r % 16);
			p.C500 = tempPalette.C500;
			r++;
			E::getColorPaletteFromID(tempPalette, r % 16);
			p.C600 = tempPalette.C600;
			r++;
			E::getColorPaletteFromID(tempPalette, r % 16);
			p.C700 = tempPalette.C700;
			r++;
			E::getColorPaletteFromID(tempPalette, r % 16);
			p.C800 = tempPalette.C800;
			r++;
			E::getColorPaletteFromID(tempPalette, r % 16);
			p.C900 = tempPalette.C900;
			r++;
			E::getColorPaletteFromID(tempPalette, r % 16);
			p.A100 = tempPalette.A100;
			r++;
			E::getColorPaletteFromID(tempPalette, r % 16);
			p.A200 = tempPalette.A200;
			r++;
			E::getColorPaletteFromID(tempPalette, r % 16);
			p.A400 = tempPalette.A400;
			r++;
			E::getColorPaletteFromID(tempPalette, r % 16);
			p.A700 = tempPalette.A700;
			break;
		}
	}
}

/*
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
*/