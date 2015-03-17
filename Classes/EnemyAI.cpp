#include "stdafx.h"
#include "Scene/MainGameScene.h"
#include "UI/TitleBar.h"

USING_NS_CC;

#define ANI_STRINGING 15.0f

static bool ai_bActionStarted;
static long ai_tick = 0;
static long ai_tick_m = 0;
static float ai_width = 0;
static float ai_ox;
void S_MainGame::updateEnemyAI(){
	ai_tick_m ++;
	static MainBall* tempWheel = new MainBall;
	if(!ai_bActionStarted){
		if(ai_tick_m % 20 != 0)
			return;
		*tempWheel = *m_wheel; 
		tempWheel->isReal = false;
		for(int i = 0; i < ANI_STRINGING + SS_ANI_MOVING; i++){
			checkCollision(tempWheel);
		}
		if(tempWheel->position.y + (SS_ANI_MOVING) * SS_SPEEDRATIO > (E::visibleHeight-TITLEBAR_HEIGHT) * 0.7){
			ai_width = m_smartstring_enemy->getMaxWidth() * (rand() % 50 + 50) / 100.0f;
			ai_width = rand() % 2 == 0? ai_width: -ai_width;
			ai_ox = ai_width * (rand() % 10) / 100.0f;
			ai_ox = rand() % 2 == 0? ai_ox: -ai_ox;
			ai_ox = 0;
			float ty = tempWheel->position.y + SS_ANI_MOVING * SS_SPEEDRATIO;
			ty = ty > (E::visibleHeight-TITLEBAR_HEIGHT) -  16? (E::visibleHeight-TITLEBAR_HEIGHT) - 16: ty;
			m_smartstring_enemy->setStartingPoint(Vec2(ai_ox + tempWheel->position.x -  ai_width/2, ty));
			ai_bActionStarted = true;
			ai_tick = 0;
		}
	}else{
		if(ai_tick >= 0){
			ai_tick ++;
			if(ai_tick <= ANI_STRINGING){
				m_smartstring_enemy->setEndingPoint(Vec2(m_smartstring_enemy->m_startingPoint.x
					+ ai_width * (ai_tick/ANI_STRINGING), m_smartstring_enemy->m_startingPoint.y));
	
			}
			if(ai_tick == ANI_STRINGING){
				m_smartstring_enemy->go();	
				ai_tick = -1;
			}
		}
	}

	

	

}


#define BORDER_WIDTH 0
void S_MainGame::checkCollision(MainBall* wheel){
	if(m_isGameOver)
		return;
	//wheel->sprite->setRotation(tick *6);
	wheel->setPosition(wheel->position.x + wheel->speed / 2 * sin(wheel->angle) + wheel->speed * sin(wheel->rotatedAngle),
		wheel->position.y + wheel->speed / 2 * cos(wheel->angle) + wheel->speed * cos(wheel->rotatedAngle));
	wheel->rotatedAngle += wheel->rotate*wheel->speed*PI / 180.0f;

	// colision
	float borderPosition;
	// colision right side
	borderPosition = E::visibleWidth - BORDER_WIDTH - MAIN_BALL_RADIUS;
	if(wheel->position.x > borderPosition){ 
		wheel->angle = -wheel->angle;
		wheel->rotatedAngle = wheel->angle;
		/*
		wheel->rotate++;
		if(wheel->rotate == 3){
		wheel->rotate = -2;
		}
		*/
		wheel->setPositionX(borderPosition);

		if(wheel->isReal){
#ifndef NDEBUG
		m_bPaused = true;
#endif
			collidingWithBorder();
			addScore(1);
		}
	}
	// colision left side
	borderPosition = BORDER_WIDTH + MAIN_BALL_RADIUS;
	if(wheel->position.x < borderPosition){ 
		wheel->angle = -wheel->angle;
		wheel->rotatedAngle = wheel->angle;
		/*
		wheel->rotate--;
		if(wheel->rotate == -3){
		wheel->rotate = 2;
		}
		*/
		wheel->setPositionX(borderPosition);

		if(wheel->isReal){
#ifndef NDEBUG
		m_bPaused = true;
#endif
			collidingWithBorder();
			addScore(1);
		}
	}
	float angle_ = angleMinus90(wheel->angle);

	//colision top side
	borderPosition = E::visibleHeight - MAIN_BALL_RADIUS - TITLEBAR_HEIGHT;
	if(wheel->position.y > borderPosition){ 
		wheel->angle = anglePlus90(-angle_);
		wheel->rotatedAngle = wheel->angle;
		wheel->setPositionY(borderPosition);
		
		if(wheel->isReal){
#ifndef NDEBUG
		m_bPaused = true;
#endif
			collidingWithBorder();
			addScore(100);
		}
	
	}

	//colision bottom side
	borderPosition = BORDER_WIDTH + MAIN_BALL_RADIUS;
	if(wheel->position.y < borderPosition && !m_isGameOver){ 
		/*
		wheel->angle = anglePlus90(-angle_);
		wheel->rotatedAngle = wheel->angle;
		*/
		wheel->setPositionY(borderPosition);
		if(wheel->isReal){
			gameOver();
			E::playEffect("beng");
			
		}
	}

	//smart string colision 
	/*
	switch(m_smartstring->checkCollision(wheel->sprite->getPosition(), getWheelRadius())){
	case 1:
		wheel->angle = -wheel->angle;
		wheel->rotatedAngle = wheel->angle;
		wheel->speed = wheel->speed*0.5+m_smartstring->getSpeed() ;
		break;
	case 2:
		wheel->angle = -wheel->angle;
		wheel->rotatedAngle = wheel->angle;
		wheel->speed = wheel->speed*0.5+m_smartstring->getSpeed();
		break;
	case 3:
		wheel->angle = anglePlus90(-angle_);
		wheel->rotatedAngle = wheel->angle;
		wheel->speed =wheel->speed*0.5+m_smartstring->getSpeed();
		break;
	}
	*/
	if(m_smartstring->checkCollision(wheel) > 0){
		if(wheel->isReal && ai_tick == -1)
			ai_bActionStarted = false;
		if(wheel->isReal){
			addScore(m_smartstring->getSpeed());
#ifndef NDEBUG
		m_bPaused = true;
#endif		
			E::playEffect("di");
			//CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/di" AEX);
		}
	}
	if(m_smartstring_enemy->checkCollision(wheel) > 0){
		if(wheel->isReal && ai_tick == -1)
			ai_bActionStarted = false;
		if(wheel->isReal){
			addScore(m_smartstring_enemy->getSpeed() * 2);
#ifndef NDEBUG
		m_bPaused = true;
#endif
			E::playEffect("di");
			//CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/di" AEX);
		}
	}

}

void S_MainGame::collidingWithBorder(){
	E::playEffect("da");
	//CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/da" AEX);
}

void S_MainGame::addScore(int score){
	m_score += score;
	m_titleBar->setString(stdp::to_string(m_score));
}
