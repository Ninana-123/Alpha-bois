#pragma once

#ifndef TIMEMANAGER_H
#define TIMEMANAGER_H
#include <AEEngine.h>

extern float deltaTime;
float curGameTime = 0;


namespace {
	bool isPaused = false;
	bool enemypause = false;
	bool explosiontrigger = false;
}

void Reset_TimeMan();
void Update_Time();
void TimePause();
void TimeResume();
void TimePauseEnemy();
void TimeEnemyResume();
void ExplosionYes();
void ExplosionNo();
bool IsTime_Paused();
bool IsTime_Paused_Enemy();
bool IsExplosionTriggered();

#endif // !TIMEMANAGER_H
