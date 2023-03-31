/*
\copyright
		All content(C) 2023 DigiPen Institute of Technology Singapore.All rights
		reserved.Reproduction or disclosure of this file or its contents without the prior
		written consent of DigiPen Institute of Technology is prohibited.
*/
/*!
@file void.cpp
@author Teo Sheen Yeoh
@Email t.sheenyeoh@digipen.edu
@course CSD 1450
@section Section A
@date 3 March 2023
@brief This file contains code for the credit screen.
*//*______________________________________________________________________*/
#include "TimeManager.h"
#include "HighScore.h"

float deltaTime = 0;
float curGameTime = 0;	

void Reset_TimeMan() {
	curGameTime = 0;
	deltaTime = 0;
	Reset_HighScore();
}

void Update_Time() {

	if (!isPaused) {
		deltaTime = (float)AEFrameRateControllerGetFrameTime();
		curGameTime += deltaTime;
	}

}

void TimePause() {
	isPaused = true;
}

void TimeResume() {
	isPaused = false;
}

void TimePauseEnemy() {
	enemypause = true;
}

void TimeEnemyResume() {
	enemypause = false;
}

void ExplosionYes() {
	explosiontrigger = true;
}

void ExplosionNo() {
	explosiontrigger = false;
}

bool IsTime_Paused() {
	return isPaused;
}

bool IsTime_Paused_Enemy() {
	return enemypause;
}

bool IsExplosionTriggered() {
	return explosiontrigger;
}