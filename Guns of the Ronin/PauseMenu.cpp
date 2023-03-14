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
float resumeY = 6.f;
float restartY = -95.f;
float mainMenuY = -209.f;

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

	// Getting mouse position
	AEInputGetCursorPosition(Paused_MouseX, Paused_MouseY);
	*Paused_MouseX = *Paused_MouseX - 800;
	*Paused_MouseY = (*Paused_MouseY - 450) * -1;
	leftClick = AEInputCheckTriggered(AEVK_LBUTTON);

	// Resume
	if (IsButtonHover(buttonsX, resumeY, 250.f, -125.f, Paused_MouseX, Paused_MouseY)) {
		//playButton.spriteIndex = 1;
		if (leftClick) {
			checkPaused = false;
			TimeResume();
		}
	}

	// Restart
	if (IsButtonHover(buttonsX, restartY, 250.f, -125.f, Paused_MouseX, Paused_MouseY)) {
		if (leftClick) {
			gGameStateNext = GS_RESTART;
		}
	}

	// Main Menu
	if (IsButtonHover(buttonsX, mainMenuY, 250.f, -125.f, Paused_MouseX, Paused_MouseY)) {
		if (leftClick) {
			//gGameStateCurr = GS_MAINMENU;
		}
	}
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
