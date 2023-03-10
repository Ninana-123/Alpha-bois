#pragma once


#ifndef HIGHSCORE_H	
#define HIGHSCORE_H

#include "TimeManager.h"

int curHighScore;

void Add_Score(int val) {
	curHighScore += val;
}

int Finalize_HighScore() {
	curHighScore += static_cast<int>(curGameTime * 10.0f);
}


#endif // !1
