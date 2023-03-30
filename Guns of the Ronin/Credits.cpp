#include "Credits.h"
#include "MainMenu.h"

AEGfxTexture* creditsBGTexture;
Credits creditsBG;

AEGfxTexture* creditsQuitButtonSprite;
Credits quitButton;

/*	VARIABLES	*/
float creditsY;
float titleY = -1;	// initial position of first line of text
float lastLineY;

/*  Y POSITION OF TEXT  */
float firstLine;
float nameOffset = 0.2f;


/*  CONST VARIABLES*/
#define headerScale 0.75f
#define nameScale 0.6f

// BUTTON
#define backButtonX -650.0f
#define backButtonY -350.0f
#define backButtonScaleX 200.0f
#define backButtonScaleY -100.0f

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
	firstLine = titleY + creditsY;
	lastLineY = firstLine - (nameOffset * 20);

	if (lastLineY > 1.0f) {
		// Quit to main menu when credits finish rolling
		// gGameStateNext = GS_MAINMENU;

		// Loop the credits
		firstLine = titleY;	// restart position to initial position
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
	AEGfxPrint(font, strBuffer, -0.3f, firstLine, 1, 1, 1, 1);

	sprintf_s(strBuffer, "Produced By");
	AEGfxPrint(font, strBuffer, -0.15f, firstLine - (nameOffset * 2), headerScale, 1, 1, 1);

	sprintf_s(strBuffer, "KAI ALEXANDER        SEAN ANG        TEO SHEEN YEOH");
	AEGfxPrint(font, strBuffer, -0.45f, firstLine - (nameOffset * 3), nameScale, 1, 1, 0);

	sprintf_s(strBuffer, "ZENG ZHICHENG               VANCE TAY");
	AEGfxPrint(font, strBuffer, -0.35f, firstLine - (nameOffset * 4), nameScale, 1, 1, 0);

	sprintf_s(strBuffer, "Faculty and Advisors");
	AEGfxPrint(font, strBuffer, -0.2f, firstLine - (nameOffset * 6) , headerScale, 1, 1, 1);

	sprintf_s(strBuffer, "DING XIANG CHENG     GERALD WONG");
	AEGfxPrint(font, strBuffer, -0.35f, firstLine - (nameOffset * 7), nameScale, 1, 1, 0);

	sprintf_s(strBuffer, "PRASANNA GHALI     RONALD KOH     ELIE HOSRY");
	AEGfxPrint(font, strBuffer, -0.45f, firstLine - (nameOffset * 8), nameScale, 1, 1, 0);

	sprintf_s(strBuffer, "Created at");
	AEGfxPrint(font, strBuffer, -0.1f, firstLine - (nameOffset * 10), headerScale, 1, 1, 1);

	sprintf_s(strBuffer, "DigiPen Institute of Technology Singapore");
	AEGfxPrint(font, strBuffer, -0.42f, firstLine - (nameOffset * 11), headerScale, 1, 1, 1);

	sprintf_s(strBuffer, "PRESIDENT");
	AEGfxPrint(font, strBuffer, -0.1f, firstLine - (nameOffset * 13), headerScale, 1, 1, 1);

	sprintf_s(strBuffer, "CLAUDE COMAIR");
	AEGfxPrint(font, strBuffer, -0.125f, firstLine - (nameOffset * 14), nameScale, 1, 1, 0);

	sprintf_s(strBuffer, "EXECUTIVES");
	AEGfxPrint(font, strBuffer, -0.1f, firstLine - (nameOffset * 16), headerScale, 1, 1, 1);

	sprintf_s(strBuffer, "JASON CHU     SAMIR ABOU SAMRA     MICHELE COMAIR");
	AEGfxPrint(font, strBuffer, -0.45f, firstLine - (nameOffset * 17), nameScale, 1, 1, 0);
	
	sprintf_s(strBuffer, "ANGELA KUGLER     DR ERIK MOHRMANN     CHRISTOPHER COMAIR");
	AEGfxPrint(font, strBuffer, -0.55f, firstLine - (nameOffset * 18), nameScale, 1, 1, 0);

	sprintf_s(strBuffer, "BENJAMIN ELLINGER     MELVIN GONSALVEZ     MICHAEL GATS");
	AEGfxPrint(font, strBuffer, -0.5f, firstLine - (nameOffset * 19), nameScale, 1, 1, 0);

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