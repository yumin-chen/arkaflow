#include "stdafx.h"
#include "MainGameScene.h"


#define ANI_STRINGING 15.0f

static bool ai_bActionStarted;
static long ai_tick = 0;
static float ai_width = 0;
static float ai_ox;
void S_MainGame::updateEnemyAI(){
	
	static MainBall* tempWheel = new MainBall;
	if(!ai_bActionStarted){
		*tempWheel = *m_wheel; 
		tempWheel->isReal = false;
		for(int i = 0; i < ANI_STRINGING + SS_ANI_MOVING; i++){
			checkCollision(tempWheel);
		}
		if(tempWheel->position.y + (SS_ANI_MOVING) * SS_SPEEDRATIO > E::visibleHeight * 0.7){
			ai_width = m_smartstring_enemy->getMaxWidth() * (rand() % 50 + 50) / 100.0f;
			ai_width = rand() % 2 == 0? ai_width: -ai_width;
			ai_ox = ai_width * (rand() % 10) / 100.0f;
			ai_ox = rand() % 2 == 0? ai_ox: -ai_ox;
			ai_ox = 0;
			m_smartstring_enemy->setStartingPoint(Vec2(ai_ox + tempWheel->position.x -  ai_width/2, tempWheel->position.y + SS_ANI_MOVING * SS_SPEEDRATIO));
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


#define BORDER_WIDTH 12;
void S_MainGame::checkCollision(MainBall* wheel){
	//wheel->sprite->setRotation(tick *6);
	wheel->setPosition(wheel->position.x + wheel->speed / 2 * sin(wheel->angle) + wheel->speed * sin(wheel->rotatedAngle),
		wheel->position.y + wheel->speed / 2 * cos(wheel->angle) + wheel->speed * cos(wheel->rotatedAngle));
	wheel->rotatedAngle += wheel->rotate*wheel->speed*PI/180.0f;

	// colision
	float borderPosition;
	// colision right side
	borderPosition = E::visibleWidth - BORDER_WIDTH - wheel->sprite->getBoundingBox().size.width * 0.5f * 0.775f;
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
	}
	// colision left side
	borderPosition = BORDER_WIDTH + wheel->sprite->getBoundingBox().size.width * 0.5f * 0.775f;
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
	}
	float angle_ = angleMinus90(wheel->angle);
	//colision top side
	borderPosition = E::visibleHeight - BORDER_WIDTH - wheel->sprite->getBoundingBox().size.width * 0.5 * 0.775;
	if(wheel->position.y > borderPosition){ 
		wheel->angle = anglePlus90(-angle_);
		wheel->rotatedAngle = wheel->angle;
		wheel->setPositionY(borderPosition);
	}
	//colision bottom side
	borderPosition = BORDER_WIDTH + wheel->sprite->getBoundingBox().size.width * 0.5 * 0.775;
	if(wheel->position.y < borderPosition && !m_isGameOver){ 
		/*
		wheel->angle = anglePlus90(-angle_);
		wheel->rotatedAngle = wheel->angle;
		wheel->setPositionY(borderPosition);
		*/
		if(wheel->isReal){
			m_isGameOver=true;
			m_tick2=0;
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
	if(m_smartstring->checkCollision(wheel->position, getWheelRadius(), wheel) > 0){
		if(wheel->isReal && ai_tick == -1)
			ai_bActionStarted = false;
	}
	if(m_smartstring_enemy->checkCollision(wheel->position, getWheelRadius(), wheel) > 0){
		if(wheel->isReal && ai_tick == -1)
			ai_bActionStarted = false;
	}

}
