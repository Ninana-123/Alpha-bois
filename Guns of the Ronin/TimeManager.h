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
#pragma once

#ifndef TIMEMANAGER_H
#define TIMEMANAGER_H
#include <AEEngine.h>

extern float deltaTime;
extern float curGameTime;
extern bool gameEnded;

namespace {
	bool isPaused = false;
	bool enemypause = false;
}

void Reset_TimeMan();
void Update_TimeMan();
void Pause_Time();
void Resume_Time();
void Pause_EnemyTime();
void Resume_EnemyTime();
bool Is_TimePaused();
bool Is_EnemyTimePaused();

#endif // !TIMEMANAGER_H
