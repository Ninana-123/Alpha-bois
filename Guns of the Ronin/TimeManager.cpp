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
bool gameEnded = false;

void Reset_TimeMan() {
	curGameTime = 0;
	deltaTime = 0;
}

void Update_TimeMan() {

	if (!isPaused) {
		deltaTime = (float)AEFrameRateControllerGetFrameTime();
		curGameTime += deltaTime;
	}

}

void Pause_Time() {
	isPaused = true;
}

void Resume_Time() {
	isPaused = false;
}

void Pause_EnemyTime() {
	enemypause = true;
}

void Resume_EnemyTime() {
	enemypause = false;
}

bool Is_TimePaused() {
	return isPaused;
}

bool Is_EnemyTimePaused() {
	return enemypause;
}
