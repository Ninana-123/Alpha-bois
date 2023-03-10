
#include "HighScore.h"

int curHighScore = 0;

void Reset_HighScore() {
	curHighScore = 0;
}

void Add_Score(int val) {
	curHighScore += val;
}

int Finalize_HighScore() {
	curHighScore += static_cast<int>(curGameTime * 10.0f);
	return curHighScore;
}
