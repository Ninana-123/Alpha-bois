/*
\copyright
		All content(C) 2023 DigiPen Institute of Technology Singapore.All rights
		reserved.Reproduction or disclosure of this file or its contents without the prior
		written consent of DigiPen Institute of Technology is prohibited.
*/
/*!
@file		PauseMenu.cpp
@author		Sean Ang JiaBao
@Email		ang.s@digipen.edu
@co-author	Zeng ZhiCheng
@email		z.zhicheng@digipen.edu 
@course		CSD 1451
@section	Section A
@date		3 March 2023
@brief		This file contains function definitions for the pause menu
*//*______________________________________________________________________*/

#include "PauseMenu.h"
#include "MainMenu.h"
#include "HighScore.h"
#include <stdio.h>


AEGfxTexture* pauseMenuBG;
AEGfxTexture* deadMenuBG;
AEGfxTexture* pauseMenuWinBG;

AEGfxVertexList* pauseQuitButtonMesh = 0;
Transform pauseQuitButton;
AEGfxTexture* pauseQuitButtonTexture = 0;
#define PAUSE_QUIT_BUTTON_X_POS -650
#define PAUSE_QUIT_BUTTON_Y_POS -350
#define PAUSE_QUIT_BUTTON_WIDTH 10.f
#define PAUSE_QUIT_BUTTON_HEIGHT 1.0f
#define PAUSE_QUIT_BUTTON_X_SCALE 200.f
#define PAUSE_QUIT_BUTTON_Y_SCALE -100.0f

#define DEAD_TEXT_X_POS -0.16f
#define DEAD_TEXT_Y_POS 0.32f
#define DEAD_TEXT_SCALE 2.2f

#define YOU_TEXT_X_POS -0.14f
#define YOU_TEXT_Y_POS -0.15f
#define YOU_TEXT_SCALE 2.2f

#define WIN_TEXT_X_POS -0.145f
#define WIN_TEXT_Y_POS -0.45f
#define WIN_TEXT_SCALE 2.2f

#define CUR_HIGH_SCORE_X_POS -0.98f
#define CUR_HIGH_SCORE_Y_POS 0.9f
#define CUR_HIGH_SCORE_SCALE 0.8f

int quitButtonSpriteIndex = 0;

s32 pausedMouseX;
s32 pausedMouseY;

bool leftClick;
bool checkPaused = false;

PauseMenu pauseMenu;
PauseMenu resumeButton;
PauseMenu restartButton;
PauseMenu mainMenuButton;

#define BUTTONS_X 0.f
#define RESUME_Y 15.0f
#define RESTART_Y (RESUME_Y - 110.0f)
#define MAINMENU_Y (RESTART_Y - 110.0f)
#define BUTTONS_WIDTH 300.0f
#define BUTTONS_HEIGHT -100.0f

void Init_PauseMenu() {

	pauseMenuBG = AEGfxTextureLoad("Assets/pauseMenu.png");
	deadMenuBG = AEGfxTextureLoad("Assets/pauseMenuNoResume.png");
	pauseMenuWinBG = AEGfxTextureLoad("Assets/pauseMenuWin.png");
	
	Create_QuadMesh(1.f, 1.f, Color(1, 1, 1), pauseMesh);
	pauseMenu.transform.texture = &pauseMenuBG;
	pauseMenu.transform.position = { 0.0f,0.0f };
	pauseMenu.transform.scale = { (float)-AEGetWindowWidth(),  (float)AEGetWindowHeight()};
	pauseMenu.transform.height = 1.0f;
	pauseMenu.transform.width = 1.0f;
	pauseMenu.transform.mesh = &pauseMesh;

	pauseQuitButtonTexture = AEGfxTextureLoad("Assets/buttonspritesheet.png");
	Create_QuadMesh(1.f, 1.f, Color(1, 1, 1), pauseQuitButtonMesh, 1.0f / 10.0f, 1.0f);
	pauseQuitButton.texture = &pauseQuitButtonTexture;
	pauseQuitButton.position = { PAUSE_QUIT_BUTTON_X_POS, PAUSE_QUIT_BUTTON_Y_POS };
	pauseQuitButton.scale = { PAUSE_QUIT_BUTTON_X_SCALE, PAUSE_QUIT_BUTTON_Y_SCALE };
	pauseQuitButton.height = PAUSE_QUIT_BUTTON_HEIGHT;
	pauseQuitButton.width = PAUSE_QUIT_BUTTON_WIDTH;
	pauseQuitButton.mesh = &pauseQuitButtonMesh;
	pauseQuitButton.rotation = 0.0f;

}

void Update_PauseMenu(PlayerInfo const& playerInfo) {

	pauseMenu.escPressed = AEInputCheckTriggered(AEVK_ESCAPE);
	// if esc is pressed
	if (pauseMenu.escPressed) {
		AEAudioPauseGroup(mainsceneAudioGroup);
		if (!Is_TimePaused()) {	
			Pause_Time();		// pause time if time is not paused
		}
		else {
			Resume_Time();		// unpause time
		}

	}

	// if time is paused, do nothing
	if (!Is_TimePaused()) {
		return;
	}

	// Getting mouse position
	AEInputGetCursorPosition(&pausedMouseX, &pausedMouseY);
	pausedMouseX = (s32)pausedMouseX - s32(AEGetWindowWidth() / 2.0f);
	pausedMouseY = -((s32)pausedMouseY - s32(AEGetWindowHeight() / 2.0f));
	leftClick = AEInputCheckReleased(AEVK_LBUTTON);


	//Only check for clicking of resume button when player is not dead and game has not been won
	if (!playerInfo.playerDead && !gameEnded) {
		// Resume
		if (Is_ButtonHover(BUTTONS_X, RESUME_Y, BUTTONS_WIDTH, BUTTONS_HEIGHT, &pausedMouseX, &pausedMouseY)) {
			//playButton.spriteIndex = 1;
			if (leftClick) {
				Resume_Time();
				leftClick = false;
			}
		}
	}
	
	// Restart
	if (Is_ButtonHover(BUTTONS_X, RESTART_Y, BUTTONS_WIDTH, BUTTONS_HEIGHT, &pausedMouseX, &pausedMouseY) && !gameEnded) {
		if (leftClick) {
			gGameStateNext = GS_RESTART;
			Resume_Time();
			leftClick = false;
		}
	}

	// Main Menu
	if (Is_ButtonHover(BUTTONS_X, MAINMENU_Y, BUTTONS_WIDTH, BUTTONS_HEIGHT, &pausedMouseX, &pausedMouseY) && !gameEnded) {
		if (leftClick) {
			AEAudioStopGroup(mainsceneAudioGroup);
			gGameStateNext = GS_MAINMENU;
			Resume_Time();
			leftClick = false;
		}
	}

	//Quit button when game won
	if (gameEnded && Is_ButtonHover(PAUSE_QUIT_BUTTON_X_POS, PAUSE_QUIT_BUTTON_Y_POS, PAUSE_QUIT_BUTTON_X_SCALE, PAUSE_QUIT_BUTTON_Y_SCALE, &pausedMouseX, &pausedMouseY)) {
		quitButtonSpriteIndex = 3;
		if (AEInputCheckReleased(AEVK_LBUTTON)) {
			gGameStateNext = GS_MAINMENU;
			Resume_Time();
		}
	}
	else quitButtonSpriteIndex = 2;
}

void Draw_PauseMenu(PlayerInfo const& playerInfo) {

	//If player is dead
	if (playerInfo.playerDead) {
		//Draw the pause menu without the resume button
		pauseMenu.transform.texture = &deadMenuBG;
	}
	else if (gameEnded) {
		pauseMenu.transform.texture = &pauseMenuWinBG;
	}

	// If time is paused, draw pause menu
	if (Is_TimePaused()) {		
		Draw_Mesh(&pauseMenu.transform);
	}

	char strBuffer[1024];
	if (playerInfo.playerDead && !gameEnded) {
		sprintf_s(strBuffer, "DEAD");
		AEGfxPrint(font, strBuffer, DEAD_TEXT_X_POS, DEAD_TEXT_Y_POS, DEAD_TEXT_SCALE, 1, 0, 0);
	}
	if (gameEnded) {
		Draw_StaticSprite(&pauseQuitButton, quitButtonSpriteIndex);
		sprintf_s(strBuffer, "YOU");
		AEGfxPrint(font, strBuffer, YOU_TEXT_X_POS, YOU_TEXT_Y_POS, YOU_TEXT_SCALE, 1, 1, 0);
		sprintf_s(strBuffer, "WIN!!");
		AEGfxPrint(font, strBuffer, WIN_TEXT_X_POS, WIN_TEXT_Y_POS, WIN_TEXT_SCALE, 1, 1, 0);
	}
	sprintf_s(strBuffer, "Score: %d", curHighScore);
	AEGfxPrint(font, strBuffer, CUR_HIGH_SCORE_X_POS, CUR_HIGH_SCORE_Y_POS, CUR_HIGH_SCORE_SCALE, 1, 1, 1);
}

void Free_PauseMenu() {
	AEGfxMeshFree(pauseMesh);
	AEGfxTextureUnload(pauseMenuBG);
	AEGfxTextureUnload(deadMenuBG);
	AEGfxTextureUnload(pauseMenuWinBG); 
	AEGfxMeshFree(pauseQuitButtonMesh);
	AEGfxTextureUnload(pauseQuitButtonTexture);
}
