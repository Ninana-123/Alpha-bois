/*
\copyright
		All content(C) 2023 DigiPen Institute of Technology Singapore.All rights
		reserved.Reproduction or disclosure of this file or its contents without the prior
		written consent of DigiPen Institute of Technology is prohibited.
*/
/*!
@file		Credits.cpp
@author		Sean Ang JiaBao
@Email		ang.s@digipen.edu
@course		CSD 1451
@section	Section A
@date		3 March 2023
@brief		This file contains code for the credit screen.
*//*______________________________________________________________________*/

#include "Credits.h"
#include "MainMenu.h"
#include "Sound.h"

AEGfxTexture* creditsBGTexture;
Credits creditsBG;

AEGfxTexture* creditsQuitButtonSprite;
Credits quitButton;

// BUTTON
#define BACK_BUTTON_X -650.0f
#define BACK_BUTTON_Y -350.0f
#define BACK_BUTTON_SCALE_X 200.0f
#define BACK_BUTTON_SCALE_Y -100.0f
#define QUIT_BUTTON_WIDTH 10.0f

// CREDITS
#define MAXHEIGHT 800.0f
#define SPEED 100.0f
#define IMAGE_STARTING_Y -900.0f

// SHARED VARIABLES
#define CREDITS_ROTATION 0
#define CREDITS_HEIGHT 1

// MOUSE INPUT
bool isLeftClicked = false;
int creditsMousePosX;
int creditsMousePosY;



void Init_Credits() {
	/*     CREDITS SCENE     */
	AEGfxSetBackgroundColor(0, 0, 0);
	creditsBGTexture = AEGfxTextureLoad("Assets/CREDITS.png");
	Create_QuadMesh((float)AEGetWindowWidth(), -(float)AEGetWindowHeight(), Color(0, 0, 0), CreditsBGMesh);
	creditsBG.transform.texture = &creditsBGTexture;
	creditsBG.transform.position = { 0.0f, -(float)AEGetWindowWidth() / 2.0f};
	creditsBG.transform.height = CREDITS_HEIGHT;
	creditsBG.transform.width = CREDITS_HEIGHT;
	creditsBG.transform.rotation = CREDITS_ROTATION;
	creditsBG.transform.mesh = &CreditsBGMesh;

	/*     QUIT BUTTON     */
	creditsQuitButtonSprite = AEGfxTextureLoad("Assets/buttonspritesheet.png");
	Create_QuadMesh(1.f, 1.f, Color(1, 1, 1), backMesh, 1.0f / 10.0f, 1.0f);
	quitButton.transform.texture = &creditsQuitButtonSprite;
	quitButton.transform.position = { BACK_BUTTON_X, BACK_BUTTON_Y };
	quitButton.transform.scale = { BACK_BUTTON_SCALE_X,BACK_BUTTON_SCALE_Y };
	quitButton.transform.height = CREDITS_HEIGHT;
	quitButton.transform.width = QUIT_BUTTON_WIDTH;
	quitButton.transform.rotation = CREDITS_ROTATION;
	quitButton.transform.mesh = &backMesh;

	AEAudioPlay(creditsSong, creditsAudioGroup, 1.f, 1.f, -1);

}

void Update_Credits() {
	/*Resuming Credits Audio*/
	AEAudioResumeGroup(creditsAudioGroup);

	/*     AUTO ROLL CREDITS SCENE     */

	creditsBG.transform.position.y += deltaTime * SPEED;

	if (creditsBG.transform.position.y > MAXHEIGHT) {
		creditsBG.transform.position.y = IMAGE_STARTING_Y;
	}

	/*     QUIT BUTTON     */
	AEInputGetCursorPosition(&creditsMousePosX, &creditsMousePosY);
	creditsMousePosX = creditsMousePosX - ((int)AEGetWindowWidth() / 2);
	creditsMousePosY = -(creditsMousePosY - ((int)AEGetWindowHeight() / 2));
	isLeftClicked = AEInputCheckReleased(AEVK_LBUTTON);

	if (Is_ButtonHover(BACK_BUTTON_X, BACK_BUTTON_Y, BACK_BUTTON_SCALE_X, BACK_BUTTON_SCALE_Y, &creditsMousePosX, &creditsMousePosY)) {
		quitButton.spriteIndex = 3;
		if (!audioPlayed) {
			AEAudioPlay(buttonHoverSound, buttonsAudioGroup, 1.f, 1.f, 0);
			audioPlayed = true;
		}
		if (isLeftClicked) {
			AEAudioPlay(buttonClickSound, buttonsAudioGroup, 1.f, 1.f, 0);
			AEAudioPauseGroup(creditsAudioGroup);
			gGameStateNext = GS_MAIN_MENU;
		}
	}
	else {
		audioPlayed = false;
		quitButton.spriteIndex = 2;
	}
}

void Draw_Credits() {
	
	// Credits text mesh
	Draw_Mesh(&creditsBG.transform);

	/*     QUIT BUTTON     */
	Draw_StaticSprite(&quitButton.transform, quitButton.spriteIndex);

}
void Free_Credits() {
	AEGfxMeshFree(CreditsBGMesh);
	AEGfxMeshFree(backMesh);

	AEGfxTextureUnload(creditsQuitButtonSprite);
	AEGfxTextureUnload(creditsBGTexture);
}