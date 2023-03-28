#include "Credits.h"
#include "MainMenu.h"

AEGfxTexture* creditsBGTexture;
Credits creditsBG;
float creditsY;
float titleY = 0;
float nameScale = 0.6f;
float headerScale = 0.75f;

void Init_Credits() {
	AEGfxSetBackgroundColor(0, 0, 0);
	creditsBGTexture = AEGfxTextureLoad("Assets/credits1.png");
	CreateQuadMesh(1.f, 1.f, Color(0, 0, 0), CreditsBGMesh);
	creditsBG.transform.texture = &creditsBGTexture;
	creditsBG.transform.position = { 0.0f,0.0f };
	creditsBG.transform.scale = { 1600.0f,-900.0f };
	creditsBG.transform.height = 1.0f;
	creditsBG.transform.width = 1.0f;
	creditsBG.transform.rotation = 0.0f;
	creditsBG.transform.mesh = &CreditsBGMesh;
}

void Update_Credits() {
	creditsBG.transform.position.y += deltaTime * 100;

}

void Draw_Credits() {
	DrawMesh(&creditsBG.transform);


	/*
	char strBuffer[1024];
	sprintf_s(strBuffer, "GUNS OF THE RONIN");
	AEGfxPrint(font, strBuffer, -0.3f, titleY + creditsY, 1, 1, 1, 1);

	sprintf_s(strBuffer, "Produced By");
	AEGfxPrint(font, strBuffer, -0.15f, titleY - 0.4f + creditsY, headerScale, 1, 1, 1);

	sprintf_s(strBuffer, "KAI ALEXANDER          SEAN ANG          SHEEN YEOH");
	AEGfxPrint(font, strBuffer, -0.45f, titleY - 0.6f + creditsY, nameScale, 1, 1, 0);

	sprintf_s(strBuffer, "ZENG ZHICHENG               VANCE TAY");
	AEGfxPrint(font, strBuffer, -0.35f, titleY - 0.8f + creditsY, nameScale, 1, 1, 0);

	sprintf_s(strBuffer, "Faculty and Advisors");
	AEGfxPrint(font, strBuffer, -0.2f, titleY - 1.4 + creditsY, headerScale, 1, 1, 1);

	sprintf_s(strBuffer, "DING XIANG CHENG     GERALD WONG");
	AEGfxPrint(font, strBuffer, -0.35f, titleY - 1.6 + creditsY, nameScale, 1, 1, 0);

	sprintf_s(strBuffer, "PRASANNA GHALI     RONALD KOH");
	AEGfxPrint(font, strBuffer, -0.3f, titleY - 1.8f + creditsY, nameScale, 1, 1, 0);

	sprintf_s(strBuffer, "Created at");
	AEGfxPrint(font, strBuffer, -0.1f, titleY - 2.4f + creditsY, headerScale, 1, 1, 1);

	sprintf_s(strBuffer, "DigiPen Institute of Technology Singapore");
	AEGfxPrint(font, strBuffer, -0.42f, titleY - 2.5f + creditsY, headerScale, 1, 1, 1);

	sprintf_s(strBuffer, "PRESIDENT");
	AEGfxPrint(font, strBuffer, -0.1f, titleY - 2.7f + creditsY, headerScale, 1, 1, 1);

	sprintf_s(strBuffer, "CLAUDE COMAIR");
	AEGfxPrint(font, strBuffer, -0.125f, titleY - 2.8f + creditsY, nameScale, 1, 1, 0);
	*/

}
void Free_Credits() {
	AEGfxMeshFree(CreditsBGMesh);
}