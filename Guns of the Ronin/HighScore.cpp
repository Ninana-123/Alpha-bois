/*
\copyright
		All content(C) 2023 DigiPen Institute of Technology Singapore.All rights
		reserved.Reproduction or disclosure of this file or its contents without the prior
		written consent of DigiPen Institute of Technology is prohibited.
*/
/*!
@file			HighScore.cpp
@author			Zeng ZhiCheng
@Email			z.zhicheng@digipen.edu
@course			CSD 1451
@section		Section A
@date			2 April 2023
@brief			This file contains definition of functions and variables related to high scores
*//*______________________________________________________________________*/
#include "HighScore.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include "Graphics.h"
#include "MainMenu.h"

int curHighScore = 0;
bool curGameEnded = false;

//The max amount of time the player needs to finish all 10 waves by
//in order to earn bonus score from time 20min * 60s
#define MAX_TIME_FOR_BONUS 1200.0f
#define TIME_TO_SCORE_MULTIPLIER 10.0f

std::vector<int> highscores;
AEGfxVertexList* highScoreBGMesh = 0;
AEGfxVertexList* quitButtonMesh = 0;
Transform highScoreWindow, quitButton;
AEGfxTexture* quitButtonTexture = 0;


bool showHighScore = false;
#define HIGH_SCORE_X_POS -0.175f
#define HIGH_SCORE_TOP_Y_POS 0.9f
#define HIGH_SCORE_Y_OFFSET -0.14f
#define QUIT_BUTTON_X_POS -650
#define QUIT_BUTTON_Y_POS -350
#define QUIT_BUTTON_WIDTH 10.f
#define QUIT_BUTTON_HEIGHT 1.0f
#define QUIT_BUTTON_X_SCALE 200.f
#define QUIT_BUTTON_Y_SCALE -100.0f
#define HALF_WIN_HEIGHT 450
#define HALF_WIN_WIDTH 800


int mouseXPos = 0;
int mouseYPos = 0;
int spriteIndex = 0;

//reset the current high score
void Reset_HighScore() {
	curHighScore = 0;
	curGameEnded = false;
}

//Add score of val to the current high score
void Add_Score(int val) {
	curHighScore += val;
}

//To update into the list of high scores
void Finalize_HighScore(bool playerDead) {
	//If the current high score is 0 dont add it into the list of high score
	if (curHighScore == 0) {
		return;
	}
	//the bonus score from time, only playthroughs that cleared all waves will recieve it
	if (!playerDead && curGameTime < MAX_TIME_FOR_BONUS) {
		//it is equal to maxTimeBonus * 10(make number bigger) - (time took to complete all 10 waves) * 10
		curHighScore += static_cast<int>(MAX_TIME_FOR_BONUS * TIME_TO_SCORE_MULTIPLIER - (curGameTime * TIME_TO_SCORE_MULTIPLIER));
	}
	highscores.push_back(curHighScore);
	Sort_HighScores();
}


//Load the highscores from the highscore file
void Load_HighScoreFile() {
	//std::ifstream file{ "../Assets/highscore.txt" };
	std::fstream file;
	file.open("Assets/highscore.txt", std::ios_base::in);// , std::ifstream::in);
	
	if (!file) {
		std::cout << "Error opening highscore.txt";
		return;
	}

	highscores.clear();
	int curScore = 0;
	char buffer[256];

	highscores.reserve(NUM_OF_HIGH_SCORES);
	int count = 0;
	while (file.getline(buffer, 256) && count++ < NUM_OF_HIGH_SCORES) {
		sscanf_s(buffer, "%d", &curScore);
		highscores.push_back(curScore);
	}
	//sort the high scores
	Sort_HighScores();
	highscores.erase(std::unique(highscores.begin(), highscores.end()), highscores.end());

	file.close();
}

void Sort_HighScores() {
	std::sort(highscores.begin(), highscores.end(), std::greater<>());
}

//Write the current new highscore into the highscore file
void Update_HighScoreFile() {
	//Add the current highscore into the vecotor
	highscores.push_back(curHighScore);
	//Sort the high scores
	Sort_HighScores();
	highscores.erase(std::unique(highscores.begin(), highscores.end()), highscores.end());

	std::ofstream file;
	file.open("Assets/highscore.txt", std::ios::trunc);

	if (!file) {
		std::cout << "Error opening highscore.txt";
	}

	//Write highscore to file 
	int numOfHighScores = static_cast<int>(highscores.size()) < NUM_OF_HIGH_SCORES ? static_cast<int>(highscores.size()) : NUM_OF_HIGH_SCORES;
	for (int i = 0; i < numOfHighScores; ++i) {
		file << highscores[i] << "\n";
	}

	file.close();
}

//Initialize the high score screen
void Init_HighScoreScreen() {

	/*     QUIT BUTTON     */
	quitButtonTexture = AEGfxTextureLoad("Assets/buttonspritesheet.png");
	Create_QuadMesh(1.f, 1.f, Color(1, 1, 1), quitButtonMesh, 1.0f / 10.0f, 1.0f);
	quitButton.texture = &quitButtonTexture;
	quitButton.position = { QUIT_BUTTON_X_POS, QUIT_BUTTON_Y_POS };
	quitButton.scale = { QUIT_BUTTON_X_SCALE, QUIT_BUTTON_Y_SCALE };
	quitButton.height = QUIT_BUTTON_HEIGHT;
	quitButton.width = QUIT_BUTTON_WIDTH;
	quitButton.mesh = &quitButtonMesh;
	quitButton.rotation = 0.0f;


	Create_QuadMesh(1.0f, 1.0f, Color(0, 0, 0), highScoreBGMesh);
	highScoreWindow.mesh = &highScoreBGMesh;
	highScoreWindow.height = 900;
	highScoreWindow.width = 1600;
	highScoreWindow.scale = { 1600,900 };
}

//Update the high score screen
void Update_HighScoreScreen() {
	AEInputGetCursorPosition(&mouseXPos, &mouseYPos);
	mouseXPos = mouseXPos - HALF_WIN_WIDTH;
	mouseYPos = (mouseYPos - HALF_WIN_HEIGHT) * -1;

	if (Is_ButtonHover(QUIT_BUTTON_X_POS, QUIT_BUTTON_Y_POS, QUIT_BUTTON_X_SCALE, QUIT_BUTTON_Y_SCALE, &mouseXPos, &mouseYPos)) {
		spriteIndex = 3;
		if (AEInputCheckReleased(AEVK_LBUTTON)) {
			gGameStateNext = GS_MAINMENU;
		}
	}
	else spriteIndex = 2;
}

//Draw the high score screen
void Draw_HighScoreScreen() {

	Draw_Mesh(&highScoreWindow);
	char strBuffer[2048];
	float curYPos = HIGH_SCORE_TOP_Y_POS;
	sprintf_s(strBuffer, "High Scores:");
	AEGfxPrint(font, strBuffer, HIGH_SCORE_X_POS, curYPos += HIGH_SCORE_Y_OFFSET, 1.0f, 1.0f, 1.0f, 0);
	Sort_HighScores();
	int numOfHighScores = static_cast<int>(highscores.size()) < NUM_OF_HIGH_SCORES ? static_cast<int>(highscores.size()) : NUM_OF_HIGH_SCORES;
	for (int i = 0; i < numOfHighScores; ++i) {
		sprintf_s(strBuffer, "%d", highscores[i]);
		AEGfxPrint(font, strBuffer, HIGH_SCORE_X_POS, curYPos += HIGH_SCORE_Y_OFFSET, 1.0f, 1.0f, 1.0f, 1.0f);
	}


	Draw_StaticSprite(&quitButton, spriteIndex);
}

//free the high score screen
void Free_HighScoreScreen() {
	AEGfxMeshFree(highScoreBGMesh);
	AEGfxMeshFree(quitButtonMesh);
	AEGfxTextureUnload(quitButtonTexture);
}