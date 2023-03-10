#pragma once


#ifndef HIGHSCORE_H	
#define HIGHSCORE_H

#include "TimeManager.h"

extern int curHighScore;

void Reset_HighScore();

void Add_Score(int val);

int Finalize_HighScore();


#endif // !1
