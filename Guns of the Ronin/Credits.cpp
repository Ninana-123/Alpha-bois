/*
\copyright
		All content(C) 2023 DigiPen Institute of Technology Singapore.All rights
		reserved.Reproduction or disclosure of this file or its contents without the prior
		written consent of DigiPen Institute of Technology is prohibited.
*/
/*!
@file Credits.cpp
@author Sean Ang JiaBao
@Email ang.s@digipen.edu
@course CSD 1451
@section Section A
@date 3 March 2023
@brief This file contains code for the credit screen.
*//*______________________________________________________________________*/

#include "Credits.h"
#include "MainMenu.h"

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
s32 Credits_MousePosX;
s32 Credits_MousePosY;

s32* Credits_MouseX = &Credits_MousePosX;
s32* Credits_MouseY = &Credits_MousePosY;



void Init_Credits() {
	/*     CREDITS SCENE     */
	AEGfxSetBackgroundColor(0, 0, 0);
	creditsBGTexture = AEGfxTextureLoad("Assets/CREDITS.png");
	CreateQuadMesh(AEGetWindowWidth(), -AEGetWindowHeight(), Color(0, 0, 0), CreditsBGMesh);
	creditsBG.transform.texture = &creditsBGTexture;
	creditsBG.transform.position = { 0.0f, -AEGetWindowWidth() / 2.0f};
	creditsBG.transform.height = CREDITS_HEIGHT;
	creditsBG.transform.width = CREDITS_HEIGHT;
	creditsBG.transform.rotation = CREDITS_ROTATION;
	creditsBG.transform.mesh = &CreditsBGMesh;

	/*     QUIT BUTTON     */
	creditsQuitButtonSprite = AEGfxTextureLoad("Assets/buttonspritesheet.png");
	CreateQuadMesh(1.f, 1.f, Color(1, 1, 1), backMesh, 1.0f / 10.0f, 1.0f);
	quitButton.transform.texture = &creditsQuitButtonSprite;
	quitButton.transform.position = { BACK_BUTTON_X, BACK_BUTTON_Y };
	quitButton.transform.scale = { BACK_BUTTON_SCALE_X,BACK_BUTTON_SCALE_Y };
	quitButton.transform.height = CREDITS_HEIGHT;
	quitButton.transform.width = QUIT_BUTTON_WIDTH;
	quitButton.transform.rotation = CREDITS_ROTATION;
	quitButton.transform.mesh = &backMesh;
}

void Update_Credits() {

	/*     AUTO ROLL CREDITS SCENE     */

	creditsBG.transform.position.y += deltaTime * SPEED;

	if (creditsBG.transform.position.y > MAXHEIGHT) {
		creditsBG.transform.position.y = IMAGE_STARTING_Y;
	}

	/*     QUIT BUTTON     */
	AEInputGetCursorPosition(Credits_MouseX, Credits_MouseY);
	*Credits_MouseX = *Credits_MouseX - AEGetWindowWidth() / 2.0f;
	*Credits_MouseY = -(*Credits_MouseY - AEGetWindowHeight() / 2.0f);
	isLeftClicked = AEInputCheckReleased(AEVK_LBUTTON);

	if (IsButtonHover(BACK_BUTTON_X, BACK_BUTTON_Y, BACK_BUTTON_SCALE_X, BACK_BUTTON_SCALE_Y, Credits_MouseX, Credits_MouseY)) {
		quitButton.spriteIndex = 3;
		if (isLeftClicked) {
			gGameStateNext = GS_MAINMENU;
		}
	}
	else quitButton.spriteIndex = 2;
}

void Draw_Credits() {
	
	// Credits text mesh
	DrawMesh(&creditsBG.transform);

	/*     QUIT BUTTON     */
	DrawStaticSprite(&quitButton.transform, quitButton.spriteIndex);

}
void Free_Credits() {
	AEGfxMeshFree(CreditsBGMesh);
	AEGfxMeshFree(backMesh);

	AEGfxTextureUnload(creditsQuitButtonSprite);
	AEGfxTextureUnload(creditsBGTexture);
}