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


#ifndef HIGHSCORE_H	
#define HIGHSCORE_H

#include "TimeManager.h"
#include <vector>

extern int curHighScore;
extern std::vector<int> highscores;
extern bool curGameEnded;

void Reset_HighScore();

void Add_Score(int val);

void Finalize_HighScore();

void Load_HighScoreFile();

void Update_HighScoreFile();

#endif // !1
