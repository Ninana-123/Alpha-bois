
#include "GSMList.h"
#include "MainMenu.h"
#include "MainScene.h"
#include "GSM.h"

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
	default:
		break;
	}
}