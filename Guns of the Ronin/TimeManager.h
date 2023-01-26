#pragma once

#ifndef TIMEMANAGER_H
#define TIMEMANAGER_H
#include <AEEngine.h>

extern float deltaTime;


namespace {
	bool isPaused = false;
}

void Update_Time();
void TimePause();
void TimeResume();

#endif // !TIMEMANAGER_H
