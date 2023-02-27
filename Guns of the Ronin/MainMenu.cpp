#include <iostream>
#include "AEEngine.h"
#include "TimeManager.h"
#include "Graphics.h"
#include "Mainscene.h"
#include "GSM.h"
#include <AEGraphics.h>


AEGfxTexture* MainMenuBG;
AEGfxVertexList* BGMesh;
int BGIndex = 0;

s32 MousePosX;
s32 MousePosY;

s32* MouseX = &MousePosX;
s32* MouseY = &MousePosY;

bool playHover = false;
bool tutHover = false;
bool exitHover = false;
bool left_mouse_pressed;

void Init_Menu() {
	// Changing the window title
	AESysSetWindowTitle("Guns of the Ronin");
	// reset the system modules
	AESysReset();
	MainMenuBG = AEGfxTextureLoad("Assets/MainMenu.png");
	
	float BG_Width = 1.0f / 4.0f;
	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, -0.5f, 0xFFFFFFFF, BGIndex * BG_Width, 1.0f,
		0.5f, -0.5f, 0xFFFFFFFF, (BGIndex + 1) * BG_Width, 1.0f,
		-0.5f, 0.5f, 0xFFFFFFFF, BGIndex * BG_Width, 0.0f
	);
	AEGfxTriAdd(
		0.5f, -0.5f, 0xFFFFFFFF, (BGIndex + 1) * BG_Width, 1.0f,
		0.5f, 0.5f, 0xFFFFFFFF, (BGIndex + 1) * BG_Width, 0.0f,
		-0.5f, 0.5f, 0xFFFFFFFF, BGIndex * BG_Width, 0.0f
	);
	BGMesh = AEGfxMeshEnd();
}

void Update_Menu() {
	Update_Time();
	AEInputGetCursorPosition(MouseX, MouseY);
	*MouseX = *MouseX - 800;
	*MouseY = (*MouseY - 450) * -1;
	left_mouse_pressed = AEInputCheckTriggered(AEVK_LBUTTON);
	std::cout << "Mouse_X: " << *MouseX << std::endl;
	std::cout << "Mouse_Y: " <<*MouseY << std::endl;

	if ((int)*MouseX > -93 && (int)*MouseX < 142 && (int)*MouseY > -205 && (int)*MouseY < -91) {
		playHover = true;
		if (left_mouse_pressed) {
			gGameStateNext = GS_LEVEL1;
		}
	}
	else playHover = false;
	
	if ((int)*MouseX > 176 && (int)*MouseX < 507 && (int)*MouseY > -205 && (int)*MouseY < -91) {
		tutHover = true;
	}
	else tutHover = false;

	if ((int)*MouseX > 546 && (int)*MouseX < 781 && (int)*MouseY > -205 && (int)*MouseY < -91) {
		exitHover = true;
	}
	else exitHover = false;



}

void Draw_Menu(){
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxSetTransparency(1.0f);
	AEGfxTextureSet(MainMenuBG, 0.f, 0.f);

	AEMtx33 scale = { 0 };
	AEMtx33Scale(&scale, 1600.f, 900.f);
	AEMtx33 rotate = { 0 };
	AEMtx33Rot(&rotate, 0);
	AEMtx33 translate = { 0 };
	AEMtx33Trans(&translate, 0.f, 0.f);
	AEMtx33 transform = { 0 };
	AEMtx33Concat(&transform, &rotate, &scale);
	AEMtx33Concat(&transform, &translate, &transform);
	AEGfxSetTransform(transform.m);
	AEGfxMeshDraw(BGMesh, AE_GFX_MDM_TRIANGLES);

	if (playHover == true) {
		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
		AEGfxSetTransparency(1.0f);
		AEGfxTextureSet(MainMenuBG, 1.f/4.f, 0.f);

		AEMtx33 scale = { 0 };
		AEMtx33Scale(&scale, 1600.f, 900.f);
		AEMtx33 rotate = { 0 };
		AEMtx33Rot(&rotate, 0);
		AEMtx33 translate = { 0 };
		AEMtx33Trans(&translate, 0.f, 0.f);
		AEMtx33 transform = { 0 };
		AEMtx33Concat(&transform, &rotate, &scale);
		AEMtx33Concat(&transform, &translate, &transform);
		AEGfxSetTransform(transform.m);
		AEGfxMeshDraw(BGMesh, AE_GFX_MDM_TRIANGLES);
	}
	if (tutHover == true) {
		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
		AEGfxSetTransparency(1.0f);
		AEGfxTextureSet(MainMenuBG, 2.f/4.f, 0.f);

		AEMtx33 scale = { 0 };
		AEMtx33Scale(&scale, 1600.f, 900.f);
		AEMtx33 rotate = { 0 };
		AEMtx33Rot(&rotate, 0);
		AEMtx33 translate = { 0 };
		AEMtx33Trans(&translate, 0.f, 0.f);
		AEMtx33 transform = { 0 };
		AEMtx33Concat(&transform, &rotate, &scale);
		AEMtx33Concat(&transform, &translate, &transform);
		AEGfxSetTransform(transform.m);
		AEGfxMeshDraw(BGMesh, AE_GFX_MDM_TRIANGLES);
	}
	if (exitHover == true) {
		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
		AEGfxSetTransparency(1.0f);
		AEGfxTextureSet(MainMenuBG, 3.f/4.f, 0.f);

		AEMtx33 scale = { 0 };
		AEMtx33Scale(&scale, 1600.f, 900.f);
		AEMtx33 rotate = { 0 };
		AEMtx33Rot(&rotate, 0);
		AEMtx33 translate = { 0 };
		AEMtx33Trans(&translate, 0.f, 0.f);
		AEMtx33 transform = { 0 };
		AEMtx33Concat(&transform, &rotate, &scale);
		AEMtx33Concat(&transform, &translate, &transform);
		AEGfxSetTransform(transform.m);
		AEGfxMeshDraw(BGMesh, AE_GFX_MDM_TRIANGLES);
	}
}

void Free_Menu() {
	AEGfxMeshFree(BGMesh);
	AEGfxTextureUnload(MainMenuBG);
}
// ---------------------------------------------------------------------------
// main

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{

	SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	srand(static_cast<unsigned>(time(0)));

	int gGameRunning = 1;

	// Initialization of your own variables go here

	// Using custom window procedure
	AESysInit(hInstance, nCmdShow, 1600, 900, 1, 60, true, NULL);

	GameStateMgrInit(GS_MAINMENU);

	while (gGameStateCurr != GS_QUIT)
	{
		// reset the system modules
		AESysReset();
		// If not restarting, load the gamestate
		if (gGameStateCurr != GS_RESTART)
		{
			GameStateMgrUpdate();
			GameStateInit();

		}
		else
			gGameStateNext = gGameStateCurr = gGameStatePrev;
		// Initialize the gamestate
		GameStateInit();
		while (gGameStateCurr == gGameStateNext)
		{
			AESysFrameStart();

			AEInputUpdate();

			GameStateUpdate();
			GameStateDraw();
			AESysFrameEnd();

			// check if forcing the application to quit
			if ((AESysDoesWindowExist() == false) || AEInputCheckTriggered(AEVK_ESCAPE))
				gGameStateNext = GS_QUIT;
		}

		GameStateFree();

		if (gGameStateNext != GS_RESTART)
			GameStateFree;

		gGameStatePrev = gGameStateCurr;
		gGameStateCurr = gGameStateNext;
	}

	// free the system
	AESysExit();
}