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