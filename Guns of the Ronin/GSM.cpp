/*
\copyright
		All content(C) 2023 DigiPen Institute of Technology Singapore.All rights
		reserved.Reproduction or disclosure of this file or its contents without the prior
		written consent of DigiPen Institute of Technology is prohibited.
*/
/*!
@file		GSM.cpp
@author		Kai Alexander Van Adrichem Boogaert
@Email		kaialexander.v@digipen.edu
@course		CSD 1451
@section	Section A
@date		31 January 2023
@brief		This file contains the GSM.
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

void Init_GameStateMgr(unsigned int gameStateInit)
{
	// set the initial game state
	gGameStateInit = gameStateInit;

	// reset the current, previoud and next game
	gGameStateCurr = gameStateInit;
	gGameStatePrev = gameStateInit;
	gGameStateNext = gGameStateInit;

	// call the update to set the function pointers
	Update_GameStateMgr();
}

void Update_GameStateMgr()
{
	if ((gGameStateCurr == GS_RESTART) || (gGameStateCurr == GS_QUIT))
		return;

	switch (gGameStateCurr)
	{
	case GS_MAIN_MENU:
		GameStateInit = Init_Menu;
		GameStateUpdate = Update_Menu;
		GameStateDraw = Draw_Menu;
		GameStateFree = Free_Menu;
		break;
	case GS_LEVEL_1:
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
	case GS_HIGH_SCORES:
		GameStateInit = Init_HighScoreScreen;
		GameStateUpdate = Update_HighScoreScreen;
		GameStateDraw = Draw_HighScoreScreen;
		GameStateFree = Free_HighScoreScreen;
		break;
	default:
		break;
	}
}