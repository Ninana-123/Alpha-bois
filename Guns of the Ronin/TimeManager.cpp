
#include "TimeManager.h"

float deltaTime = 0;

void Update_Time() {

	if (!isPaused) {
		deltaTime += (float)AEFrameRateControllerGetFrameTime();
	}

}

void TimePause() {
	isPaused = true;
}

void TimeResume() {
	isPaused = false;
}