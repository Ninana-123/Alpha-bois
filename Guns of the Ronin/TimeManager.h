#pragma once

#ifndef TIMEMANAGER_H
#define TIMEMANAGER_H
#include <AEEngine.h>

extern float deltaTime;


namespace {
	bool isPaused = false;
	bool enemypause = false;
}

void Update_Time();
void TimePause();
void TimeResume();
void TimePauseEnemy();
void TimeEnemyResume();
bool IsTime_Paused();
bool IsTime_Paused_Enemy();

#endif // !TIMEMANAGER_H
