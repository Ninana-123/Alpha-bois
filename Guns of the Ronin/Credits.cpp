#include "Credits.h"
#include "MainMenu.h"

AEGfxTexture* creditsBGTexture;
Credits creditsBG;

AEGfxTexture* creditsQuitButtonSprite;
Credits quitButton;

float creditsY;
float titleY = -1;	// initial position of first line of text
float nameScale = 0.6f;
float headerScale = 0.75f;
float restartLineY = -1.0f;
float lastLineY;

// BUTTON
float backButtonX = -650.0f;
float backButtonY = -350.0f;
float backButtonScaleX = 200.0f;
float backButtonScaleY = -100.0f;

// MOUSE INPUT
bool isLeftClicked = false;
s32 Credits_MousePosX;
s32 Credits_MousePosY;

s32* Credits_MouseX = &Credits_MousePosX;
s32* Credits_MouseY = &Credits_MousePosY;

void Init_Credits() {
	AEGfxSetBackgroundColor(0, 0, 0);
	CreateQuadMesh(1.f, 1.f, Color(0, 0, 0), CreditsBGMesh);
	creditsBG.transform.position = { 0.0f,0.0f };
	creditsBG.transform.scale = { 1600.0f,-900.0f };
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
	creditsY += deltaTime * 0.2f;
	restartLineY = titleY + creditsY;
	lastLineY = restartLineY - 3.4f;

	if (lastLineY > 1.0f) {
		// Quit to main menu when credits finish rolling
		// gGameStateNext = GS_MAINMENU;

		// Loop the credits
		restartLineY = titleY;	// restart position to initial position
		creditsY = 0.0f;	// restart increment
	}



	/*     QUIT BUTTON     */
	//std::cout << *Credits_MouseX << ", " << *Credits_MouseY;
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
	
	// Credits text display
	DrawMesh(&creditsBG.transform);
	
	char strBuffer[1024];
	sprintf_s(strBuffer, "GUNS OF THE RONIN");
	AEGfxPrint(font, strBuffer, -0.3f, restartLineY, 1, 1, 1, 1);

	sprintf_s(strBuffer, "Produced By");
	AEGfxPrint(font, strBuffer, -0.15f, restartLineY - 0.4f , headerScale, 1, 1, 1);

	sprintf_s(strBuffer, "KAI ALEXANDER        SEAN ANG        TEO SHEEN YEOH");
	AEGfxPrint(font, strBuffer, -0.45f, restartLineY - 0.6f, nameScale, 1, 1, 0);

	sprintf_s(strBuffer, "ZENG ZHICHENG               VANCE TAY");
	AEGfxPrint(font, strBuffer, -0.35f, restartLineY - 0.8f, nameScale, 1, 1, 0);

	sprintf_s(strBuffer, "Faculty and Advisors");
	AEGfxPrint(font, strBuffer, -0.2f, restartLineY - 1.4, headerScale, 1, 1, 1);

	sprintf_s(strBuffer, "DING XIANG CHENG     GERALD WONG");
	AEGfxPrint(font, strBuffer, -0.35f, restartLineY - 1.6, nameScale, 1, 1, 0);

	sprintf_s(strBuffer, "PRASANNA GHALI     RONALD KOH     ELIE HOSRY");
	AEGfxPrint(font, strBuffer, -0.45f, restartLineY - 1.8f , nameScale, 1, 1, 0);

	sprintf_s(strBuffer, "Created at");
	AEGfxPrint(font, strBuffer, -0.1f, restartLineY - 2.4f , headerScale, 1, 1, 1);

	sprintf_s(strBuffer, "DigiPen Institute of Technology Singapore");
	AEGfxPrint(font, strBuffer, -0.42f, restartLineY - 2.5f , headerScale, 1, 1, 1);

	sprintf_s(strBuffer, "PRESIDENT");
	AEGfxPrint(font, strBuffer, -0.1f, restartLineY - 2.7f , headerScale, 1, 1, 1);

	sprintf_s(strBuffer, "CLAUDE COMAIR");
	AEGfxPrint(font, strBuffer, -0.125f, restartLineY - 2.8f , nameScale, 1, 1, 0);

	sprintf_s(strBuffer, "EXECUTIVES");
	AEGfxPrint(font, strBuffer, -0.1f, restartLineY - 3.0f , headerScale, 1, 1, 1);

	sprintf_s(strBuffer, "JASON CHU     SAMIR ABOU SAMRA     MICHELE COMAIR");
	AEGfxPrint(font, strBuffer, -0.45f, restartLineY - 3.1f , nameScale, 1, 1, 0);
	
	sprintf_s(strBuffer, "ANGELA KUGLER     DR ERIK MOHRMANN     CHRISTOPHER COMAIR");
	AEGfxPrint(font, strBuffer, -0.55f, restartLineY - 3.2f , nameScale, 1, 1, 0);

	sprintf_s(strBuffer, "BENJAMIN ELLINGER     MELVIN GONSALVEZ     MICHAEL GATS");
	AEGfxPrint(font, strBuffer, -0.5f, restartLineY - 3.3f , nameScale, 1, 1, 0);

	sprintf_s(strBuffer, "RAYMOND YAN     JOHN BAUER     DR CHARLES DUBA     JOHNNY DEEK");
	AEGfxPrint(font, strBuffer, -0.6f, lastLineY , nameScale, 1, 1, 0);



	/*     QUIT BUTTON     */
	DrawStaticSprite(&quitButton.transform, quitButton.spriteIndex);

}
void Free_Credits() {
	AEGfxMeshFree(CreditsBGMesh);
	AEGfxMeshFree(backMesh);

	AEGfxTextureUnload(creditsQuitButtonSprite);
	
}