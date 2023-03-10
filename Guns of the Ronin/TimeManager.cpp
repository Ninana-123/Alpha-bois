
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