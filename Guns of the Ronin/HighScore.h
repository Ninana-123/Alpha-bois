/*
\copyright
		All content(C) 2023 DigiPen Institute of Technology Singapore.All rights
		reserved.Reproduction or disclosure of this file or its contents without the prior
		written consent of DigiPen Institute of Technology is prohibited.
*/
/*!
@file			Highscore.h
@author			Zeng ZhiCheng
@Email			z.zhicheng@digipen.edu
@course			CSD 1451
@section		Section A
@date			2 April 2023
@brief			This file contains declaration of functions and variables related to high scores
*//*______________________________________________________________________*/
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

void Finalize_HighScore(bool playerDead);

void Load_HighScoreFile();

void Sort_HighScores();

void Update_HighScoreFile();

void Init_HighScoreScreen();

void Update_HighScoreScreen();

void Draw_HighScoreScreen();

void Free_HighScoreScreen();

#endif // !1
