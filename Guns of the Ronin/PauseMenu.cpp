#include "PauseMenu.h"

AEGfxTexture* PauseMenuBG;

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

void Init_PauseMenu() {

	PauseMenuBG = AEGfxTextureLoad("Assets/pauseMenu.png");

	CreateQuadMesh(1.f, 1.f, Color(1, 1, 1), pauseMesh, 1.f, 1.0f);
	pauseMenu.transform.texture = &PauseMenuBG;
	pauseMenu.transform.position = { 0.0f,0.0f };
	pauseMenu.transform.scale = { 1600.0f,-900.0f };
	pauseMenu.transform.rotation = 0.0f;
	//pauseMenu.spriteIndex = 0;
	pauseMenu.transform.mesh = &pauseMesh;

}

void Update_PauseMenu() {

	AEInputGetCursorPosition(Paused_MouseX, Paused_MouseY);
	*Paused_MouseX = *Paused_MouseX - 800;
	*Paused_MouseY = (*Paused_MouseY - 450) * -1;
	leftClick = AEInputCheckTriggered(AEVK_LBUTTON);


}

void Draw_PauseMenu() {
	pauseMenu.c_pressed = AEInputCheckTriggered(AEVK_C);

	if (pauseMenu.c_pressed) {
		if (checkPaused == false) {
			checkPaused = true;
		}
		else {
			checkPaused = false;
			TimeResume();
		}

	}

	if (checkPaused == true) {
		TimePause();
		DrawMesh(&pauseMenu.transform);
	}
}

void Free_PauseMenu() {
	AEGfxMeshFree(pauseMesh);
	AEGfxTextureUnload(PauseMenuBG);
}
