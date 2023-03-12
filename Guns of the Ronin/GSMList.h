#pragma once
#ifndef GAME_STATE_LIST_H_
#define GAME_STATE_LIST_H_

// ---------------------------------------------------------------------------
// game state list

enum
{
	// list of all game states 
	GS_MAINMENU = 0,
	GS_LEVEL1,
	GS_GUIDE,

	// special game state. Do not change
	GS_RESTART,
	GS_QUIT
};

// ---------------------------------------------------------------------------

#endif