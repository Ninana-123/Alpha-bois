#include "Credits.h"
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
	if (AEInputCheckCurr(AEVK_J)) {
		creditsBG.j_pressed = true;
	}

	if (creditsBG.j_pressed == true) {
		DrawMesh(&creditsBG.transform);
	}
	
	
}
void Free_Credits() {

}