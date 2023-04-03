/*
\copyright
		All content(C) 2023 DigiPen Institute of Technology Singapore.All rights
		reserved.Reproduction or disclosure of this file or its contents without the prior
		written consent of DigiPen Institute of Technology is prohibited.
*/
/*!
@file			TimeManager.cpp
@author			Zeng ZhiCheng
@Email			z.zhicheng@digipen.edu
@course			CSD 1451
@section		Section A
@date			2 April 2023
@brief			This file contains definition of functions and variables related to time in the game
*//*______________________________________________________________________*/
#include "TimeManager.h"
#include "HighScore.h"

float deltaTime = 0;
float curGameTime = 0;	
bool gameEnded = false;


//Reset the time manager
void Reset_TimeMan() {
	curGameTime = 0;
	deltaTime = 0;
}

//Update the deltaTime of the time manager
void Update_TimeMan() {

	if (!isPaused) {
		deltaTime = (float)AEFrameRateControllerGetFrameTime();
		curGameTime += deltaTime;
	}

}

//Pause the time
void Pause_Time() {
	isPaused = true;
}

//Resume the time
void Resume_Time() {
	isPaused = false;
}

//Pause time for the enemies
void Pause_EnemyTime() {
	enemypause = true;
}

//Resume time for the enemies
void Resume_EnemyTime() {
	enemypause = false;
}

//is time currently paused?
bool Is_TimePaused() {
	return isPaused;
}

//is enemies' time currently paused?
bool Is_EnemyTimePaused() {
	return enemypause;
}
