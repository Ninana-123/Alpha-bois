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
int quitButtonSpriteIndex = 0;

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

float buttonsX = 0.f;
float resumeY = 15.0f;
float restartY = resumeY - 110.0f;
float mainMenuY = restartY - 110.0f;

void Init_PauseMenu() {

	pauseMenuBG = AEGfxTextureLoad("Assets/pauseMenu.png");
	deadMenuBG = AEGfxTextureLoad("Assets/pauseMenuNoResume.png");
	pauseMenuWinBG = AEGfxTextureLoad("Assets/pauseMenuWin.png");
	
	CreateQuadMesh(1.f, 1.f, Color(1, 1, 1), pauseMesh);
	pauseMenu.transform.texture = &pauseMenuBG;
	pauseMenu.transform.position = { 0.0f,0.0f };
	pauseMenu.transform.scale = { 1600.0f,-900.0f };
	pauseMenu.transform.rotation = 0.0f;
	pauseMenu.transform.height = 1.0f;
	pauseMenu.transform.width = 1.0f;
	//pauseMenu.spriteIndex = 0;
	pauseMenu.transform.mesh = &pauseMesh;

	pauseQuitButtonTexture = AEGfxTextureLoad("Assets/buttonspritesheet.png");
	CreateQuadMesh(1.f, 1.f, Color(1, 1, 1), pauseQuitButtonMesh, 1.0f / 10.0f, 1.0f);
	pauseQuitButton.texture = &pauseQuitButtonTexture;
	pauseQuitButton.position = { PAUSE_QUIT_BUTTON_X_POS, PAUSE_QUIT_BUTTON_Y_POS };
	pauseQuitButton.scale = { PAUSE_QUIT_BUTTON_X_SCALE, PAUSE_QUIT_BUTTON_Y_SCALE };
	pauseQuitButton.height = PAUSE_QUIT_BUTTON_HEIGHT;
	pauseQuitButton.width = PAUSE_QUIT_BUTTON_WIDTH;
	pauseQuitButton.mesh = &pauseQuitButtonMesh;
	pauseQuitButton.rotation = 0.0f;

}

void Update_PauseMenu(PlayerInfo const& playerInfo) {

	pauseMenu.esc_pressed = AEInputCheckTriggered(AEVK_ESCAPE);
	if (pauseMenu.esc_pressed) {
		if (!IsTime_Paused()) {
			TimePause();
		}
		else {
			TimeResume();
		}

	}


	if (!IsTime_Paused()) {
		return;
	}

	// Getting mouse position
	AEInputGetCursorPosition(Paused_MouseX, Paused_MouseY);
	*Paused_MouseX = *Paused_MouseX - 800;
	*Paused_MouseY = (*Paused_MouseY - 450) * -1;
	leftClick = AEInputCheckReleased(AEVK_LBUTTON);


	//Only check for clicking of resume button when player is not dead
	if (!playerInfo.playerDead) {
		// Resume
		if (IsButtonHover(buttonsX, resumeY, 300.f, -100.f, Paused_MouseX, Paused_MouseY)) {
			//playButton.spriteIndex = 1;
			if (leftClick) {
				TimeResume();
				leftClick = false;
			}
		}
	}
	
	// Restart
	if (IsButtonHover(buttonsX, restartY, 300.f, -100.f, Paused_MouseX, Paused_MouseY)) {
		if (leftClick) {
			gGameStateNext = GS_RESTART;
			TimeResume();
			leftClick = false;
		}
	}

	// Main Menu
	if (IsButtonHover(buttonsX, mainMenuY, 300.f, -100.f, Paused_MouseX, Paused_MouseY)) {
		if (leftClick) {
			gGameStateNext = GS_MAINMENU;
			TimeResume();
			leftClick = false;
		}
	}

	if (IsButtonHover(PAUSE_QUIT_BUTTON_X_POS, PAUSE_QUIT_BUTTON_Y_POS, PAUSE_QUIT_BUTTON_X_SCALE, PAUSE_QUIT_BUTTON_Y_SCALE, Paused_MouseX, Paused_MouseY)) {
		quitButtonSpriteIndex = 3;
		if (AEInputCheckReleased(AEVK_LBUTTON)) {
			gGameStateNext = GS_MAINMENU;
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

	if (IsTime_Paused()) {		
		DrawMesh(&pauseMenu.transform);
	}

	char strBuffer[1024];
	if (playerInfo.playerDead && !gameEnded) {
		sprintf_s(strBuffer, "DEAD");
		AEGfxPrint(font, strBuffer, -0.16f, 0.32f, 2.2f, 1, 0, 0);
		//G_DrawText(dead, -50.0f, 0.f, 2.0f, Color(0, 0, 0));
	}
	if (gameEnded) {
		DrawStaticSprite(&pauseQuitButton, quitButtonSpriteIndex);
		sprintf_s(strBuffer, "YOU");
		AEGfxPrint(font, strBuffer, -0.14f, -0.15f, 2.2f, 1, 1, 0);
		sprintf_s(strBuffer, "WIN!!");
		AEGfxPrint(font, strBuffer, -0.145f, -0.45f, 2.2f, 1, 1, 0);
	}
	sprintf_s(strBuffer, "Score: %d", curHighScore);
	AEGfxPrint(font, strBuffer, -0.98f, 0.90f, 0.8f, 1, 1, 1);
}

void Free_PauseMenu() {
	AEGfxMeshFree(pauseMesh);
	AEGfxTextureUnload(pauseMenuBG);
	AEGfxTextureUnload(deadMenuBG);
	AEGfxTextureUnload(pauseMenuWinBG);
	AEGfxMeshFree(pauseQuitButtonMesh);
	AEGfxTextureUnload(pauseQuitButtonTexture);
}
