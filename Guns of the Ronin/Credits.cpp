#include "Credits.h"
#include "MainMenu.h"

AEGfxTexture* creditsBGTexture;
Credits creditsBG;

AEGfxTexture* creditsQuitButtonSprite;
Credits quitButton;

// BUTTON
#define backButtonX -650.0f
#define backButtonY -350.0f
#define backButtonScaleX 200.0f
#define backButtonScaleY -100.0f

// CREDITS
#define MAXHEIGHT 800.0f
#define SPEED 100.0f
#define IMAGE_STARTING_Y -900.0f
#define meshX 1600.0f
#define meshY -900.0f

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
	CreateQuadMesh(meshX, meshY, Color(0, 0, 0), CreditsBGMesh);
	creditsBG.transform.texture = &creditsBGTexture;
	creditsBG.transform.position = { 0.0f, -800.0f };
	creditsBG.transform.height = 1.0f;
	creditsBG.transform.width = 1.0f;
	creditsBG.transform.rotation = 0.0f;
	creditsBG.transform.mesh = &CreditsBGMesh;

	/*     QUIT BUTTON     */
	creditsQuitButtonSprite = AEGfxTextureLoad("Assets/buttonspritesheet.png");
	CreateQuadMesh(1.f, 1.f, Color(1, 1, 1), backMesh, 1.0f / 10.0f, 1.0f);
	quitButton.transform.texture = &creditsQuitButtonSprite;
	quitButton.transform.position = { backButtonX,backButtonY };
	quitButton.transform.scale = { backButtonScaleX,backButtonScaleY };
	quitButton.transform.height = 1.0f;
	quitButton.transform.width = 10.0f;
	quitButton.transform.rotation = 0.0f;
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
	*Credits_MouseX = *Credits_MouseX - 800;
	*Credits_MouseY = (*Credits_MouseY - 450) * -1;
	isLeftClicked = AEInputCheckReleased(AEVK_LBUTTON);

	if (IsButtonHover(backButtonX, backButtonY, backButtonScaleX, backButtonScaleY, Credits_MouseX, Credits_MouseY)) {
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