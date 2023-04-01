#pragma once


#ifndef HIGHSCORE_H	
#define HIGHSCORE_H

#include "TimeManager.h"
#include <vector>

extern int curHighScore;
extern std::vector<int> highscores;
extern bool curGameEnded;
#define NUM_OF_HIGH_SCORES 10

void Reset_HighScore();

void Add_Score(int val);

void Finalize_HighScore();

void Load_HighScoreFile();

void Sort_HighScores();

void Update_HighScoreFile();

#endif // !1
