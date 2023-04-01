/*
\copyright
		All content(C) 2023 DigiPen Institute of Technology Singapore.All rights
		reserved.Reproduction or disclosure of this file or its contents without the prior
		written consent of DigiPen Institute of Technology is prohibited.
*/
/*!
@file PauseMenu.cpp
@author Sean Ang JiaBao
@Email ang.s@digipen.edu
@course CSD 1451
@section Section A
@date 3 March 2023
@brief This file contains function definitions for the pause menu
*//*______________________________________________________________________*/

#include "PauseMenu.h"
#include "MainMenu.h"
#include "HighScore.h"


AEGfxTexture* pauseMenuBG;
AEGfxTexture* deadMenuBG;

s32 Paused_MousePosX;
s32 Paused_MousePosY;

s32* Paused_MouseX = &Paused_MousePosX;
s32* Paused_MouseY = &Paused_MousePosY;

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
	
	CreateQuadMesh(1.f, 1.f, Color(1, 1, 1), pauseMesh);
	pauseMenu.transform.texture = &pauseMenuBG;
	pauseMenu.transform.position = { 0.0f,0.0f };
	pauseMenu.transform.scale = { (float)-AEGetWindowWidth(),  (float)AEGetWindowHeight()};
	pauseMenu.transform.height = 1.0f;
	pauseMenu.transform.width = 1.0f;
	pauseMenu.transform.mesh = &pauseMesh;

}

void Update_PauseMenu(PlayerInfo const& playerInfo) {

	pauseMenu.esc_pressed = AEInputCheckTriggered(AEVK_ESCAPE);
	// if esc is pressed
	if (pauseMenu.esc_pressed) {
		if (!IsTime_Paused()) {	
			TimePause();		// pause time if time is not paused
		}
		else {
			TimeResume();		// unpause time
		}

	}

	// if time is paused, do nothing
	if (!IsTime_Paused()) {
		return;
	}

	// Getting mouse position
	AEInputGetCursorPosition(Paused_MouseX, Paused_MouseY);
	*Paused_MouseX = *Paused_MouseX - AEGetWindowWidth() / 2.0f;
	*Paused_MouseY = -(*Paused_MouseY - AEGetWindowHeight() / 2.0f);
	leftClick = AEInputCheckReleased(AEVK_LBUTTON);


	//Only check for clicking of resume button when player is not dead
	if (!playerInfo.playerDead) {
		// Resume
		if (IsButtonHover(BUTTONS_X, RESUME_Y, BUTTONS_WIDTH, BUTTONS_HEIGHT, Paused_MouseX, Paused_MouseY)) {
			//playButton.spriteIndex = 1;
			if (leftClick) {
				TimeResume();
				leftClick = false;
			}
		}
	}
	
	// Restart
	if (IsButtonHover(BUTTONS_X, RESTART_Y, BUTTONS_WIDTH, BUTTONS_HEIGHT, Paused_MouseX, Paused_MouseY)) {
		if (leftClick) {
			gGameStateNext = GS_RESTART;
			TimeResume();
			leftClick = false;
		}
	}

	// Main Menu
	if (IsButtonHover(BUTTONS_X, MAINMENU_Y, BUTTONS_WIDTH, BUTTONS_HEIGHT, Paused_MouseX, Paused_MouseY)) {
		if (leftClick) {
			gGameStateNext = GS_MAINMENU;
			TimeResume();
			leftClick = false;
		}
	}
}

void Draw_PauseMenu(PlayerInfo const& playerInfo) {
	//If player is dead
	if (playerInfo.playerDead) {
		//Draw the pause menu without the resume button
		pauseMenu.transform.texture = &deadMenuBG;
	}

	// If time is paused, draw pause menu
	if (IsTime_Paused()) {		
		DrawMesh(&pauseMenu.transform);
	}

	char strBuffer[1024];
	sprintf_s(strBuffer, "Score: %d", curHighScore);
	AEGfxPrint(font, strBuffer, -0.98f, 0.90f, 0.8f, 1, 1, 1);
}

void Free_PauseMenu() {
	AEGfxMeshFree(pauseMesh);
	AEGfxTextureUnload(pauseMenuBG);
	AEGfxTextureUnload(deadMenuBG);
}
