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
#include "GSMList.h"
#include "MainMenu.h"
#include "MainScene.h"
#include "Guide.h"
#include "GSM.h"
#include "Credits.h"
#include "HighScore.h"

unsigned int	gGameStateInit;
unsigned int	gGameStateCurr;
unsigned int	gGameStatePrev;
unsigned int	gGameStateNext;

// pointer to functions for game state life cycles functions
void (*GameStateInit)() = 0;
void (*GameStateUpdate)() = 0;
void (*GameStateDraw)() = 0;
void (*GameStateFree)() = 0;

void GameStateMgrInit(unsigned int gameStateInit)
{
	// set the initial game state
	gGameStateInit = gameStateInit;

	// reset the current, previoud and next game
	gGameStateCurr = gameStateInit;
	gGameStatePrev = gameStateInit;
	gGameStateNext = gGameStateInit;

	// call the update to set the function pointers
	GameStateMgrUpdate();
}

void GameStateMgrUpdate()
{
	if ((gGameStateCurr == GS_RESTART) || (gGameStateCurr == GS_QUIT))
		return;

	switch (gGameStateCurr)
	{
	case GS_MAINMENU:
		GameStateInit = Init_Menu;
		GameStateUpdate = Update_Menu;
		GameStateDraw = Draw_Menu;
		GameStateFree = Free_Menu;
		break;
	case GS_LEVEL1:
		GameStateInit = Init_Scene;
		GameStateUpdate = Update_Scene;
		GameStateDraw = Draw_Scene;
		GameStateFree = Free_Scene;
		break;
	case GS_GUIDE:
		GameStateInit = Init_Guide;
		GameStateUpdate = Update_Guide;
		GameStateDraw = Draw_Guide;
		GameStateFree = Free_Guide;
		break;
	case GS_CREDITS:
		GameStateInit = Init_Credits;
		GameStateUpdate = Update_Credits;
		GameStateDraw = Draw_Credits;
		GameStateFree = Free_Credits;
		break;
	case GS_HIGHSCORES:
		GameStateInit = Init_HighScoreScreen;
		GameStateUpdate = Update_HighScoreScreen;
		GameStateDraw = Draw_HighScoreScreen;
		GameStateFree = Free_HighScoreScreen;
		break;
	default:
		break;
	}
}