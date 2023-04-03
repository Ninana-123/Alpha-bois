/*
\copyright
		All content(C) 2023 DigiPen Institute of Technology Singapore.All rights
		reserved.Reproduction or disclosure of this file or its contents without the prior
		written consent of DigiPen Institute of Technology is prohibited.
*/
/*!
@file GSMList.h
@author Kai Alexander Van Adrichem Boogaert
@Email kaialexander.v@digipen.edu
@course CSD 1451
@section Section A
@date 31 January 2023
@brief This file contains enums for GSM List
*//*______________________________________________________________________*/
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
	GS_CREDITS,
	GS_HIGHSCORES,

	// special game state. Do not change
	GS_RESTART,
	GS_QUIT
};

// ---------------------------------------------------------------------------

#endif