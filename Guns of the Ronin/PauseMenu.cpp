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

float buttonsX = 0.f;
float resumeY = 15.0f;
float restartY = resumeY - 110.0f;
float mainMenuY = restartY - 110.0f;

void Init_PauseMenu() {

	PauseMenuBG = AEGfxTextureLoad("Assets/pauseMenu.png");

	CreateQuadMesh(1.f, 1.f, Color(1, 1, 1), pauseMesh, 1.f, 1.0f);
	pauseMenu.transform.texture = &PauseMenuBG;
	pauseMenu.transform.position = { 0.0f,0.0f };
	pauseMenu.transform.scale = { 1600.0f,-900.0f };
	pauseMenu.transform.rotation = 0.0f;
	pauseMenu.transform.height = 1.0f;
	pauseMenu.transform.width = 1.0f;
	//pauseMenu.spriteIndex = 0;
	pauseMenu.transform.mesh = &pauseMesh;

}

void Update_PauseMenu() {

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


	// Resume
	if (IsButtonHover(buttonsX, resumeY, 300.f, -100.f, Paused_MouseX, Paused_MouseY)) {
		//playButton.spriteIndex = 1;
		if (leftClick) {
			TimeResume();
			leftClick = false;
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
}

void Draw_PauseMenu() {
	if (IsTime_Paused()) {
		DrawMesh(&pauseMenu.transform);
	}
}

void Free_PauseMenu() {
	AEGfxMeshFree(pauseMesh);
	AEGfxTextureUnload(PauseMenuBG);
}
