/*
\copyright
		All content(C) 2023 DigiPen Institute of Technology Singapore.All rights
		reserved.Reproduction or disclosure of this file or its contents without the prior
		written consent of DigiPen Institute of Technology is prohibited.
*/
/*!
@file GSM.h
@author Kai Alexander Van Adrichem Boogaert
@Email kaialexander.v@digipen.edu
@course CSD 1451
@section Section A
@date 31 January 2023
@brief This file contains declaration for GSM.
*//*______________________________________________________________________*/
#pragma once
#ifndef GSM_H
#define GSM_H

// ---------------------------------------------------------------------------

#include "AEEngine.h"

// ---------------------------------------------------------------------------
// include the list of game states

#include "GSMList.h"

// ---------------------------------------------------------------------------
// externs

extern unsigned int gGameStateInit;
extern unsigned int gGameStateCurr;
extern unsigned int gGameStatePrev;
extern unsigned int gGameStateNext;

// ---------------------------------------------------------------------------

extern void (*GameStateInit)();
extern void (*GameStateUpdate)();
extern void (*GameStateDraw)();
extern void (*GameStateFree)();

// ---------------------------------------------------------------------------
// Function prototypes

// call this at the beginning and AFTER all game states are added to the manager
void GameStateMgrInit(unsigned int gameStateInit);

// update is used to set the function pointers
void GameStateMgrUpdate();

// ---------------------------------------------------------------------------

#endif