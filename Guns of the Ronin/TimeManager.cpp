
#include "TimeManager.h"

float deltaTime = 0;

void Update_Time() {

	if (!isPaused) {
		deltaTime = (float)AEFrameRateControllerGetFrameTime();
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

bool IsTime_Paused() {
	return isPaused;
}

bool IsTime_Paused_Enemy() {
	return enemypause;
}