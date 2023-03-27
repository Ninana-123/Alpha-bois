#include "Credits.h"
#include "MainMenu.h"

Credits creditsBG;

void Init_Credits() {
	CreateQuadMesh(1.f, 1.f, Color(0, 0, 0), CreditsBGMesh);
	//creditsBG.transform.texture = &guideBGTexture;
	creditsBG.transform.position = { 0.0f,0.0f };
	creditsBG.transform.scale = { 1600.0f,-900.0f };
	creditsBG.transform.height = 1.0f;
	creditsBG.transform.width = 1.0f;
	creditsBG.transform.rotation = 0.0f;
	creditsBG.transform.mesh = &CreditsBGMesh;
}

void Update_Credits() {

}

void Draw_Credits() {
	DrawMesh(&creditsBG.transform);
	
	char strBuffer[1024];
	sprintf_s(strBuffer, "GUNS OF THE RONIN");
	AEGfxPrint(font, strBuffer, -0.25f, 0.75f, 2, 1, 0, 0);
	
}
void Free_Credits() {
	AEGfxMeshFree(CreditsBGMesh);
}