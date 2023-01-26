// ---------------------------------------------------------------------------
// includes

#include <iostream>
#include "AEEngine.h"
#include "Physics.h"
#include "Graphics.h"
#include "TimeManager.h"
#include "DummyPlayer.h"
#include "Shop.h"
#include "Player.h"
#include "draw_shrine.h"
#include "EnemyController.h"
#include "PlayerInfo.h"


namespace {
	DummyPlayer dummyPlayer;
	Player player;
	Shrine Shrines, loading;
	Shop shop;
	SamuraiPool samPool;
	PlayerInfo playerinfo;
}

void Init_Scene() {

	// Changing the window title
	AESysSetWindowTitle("My New Demo!");
	// reset the system modules
	AESysReset();

	//initiate Graphics
	G_Init();

	DummyPlayer_Init(&dummyPlayer);
	Player_Init(&player);
	Draw_Shrine_Init(&Shrines, &loading);
	Init_Enemies(samPool);
	Shop_Init(&shop);
	PlayerInfo_Init(&playerinfo);
}

void Update_Scene() {
	char testCh[] = "TeStInG";

	G_DrawText(testCh, -200, 200, 1.0f);


	Update_Time();

	DummyPlayer_Update(&dummyPlayer);

	Player_Update(&player);

	Draw_Shrine_Update(&Shrines, &player, &loading);

	Update_Enemies(samPool, dummyPlayer.transform.position);

	Shop_Update(&shop, &playerinfo);

}

void Draw_Scene() {
	// Set the background
	AEGfxSetBackgroundColor(0.0f, 0.6f, 0.8f);

	Draw_Enemies(samPool);
	Draw_Shrine(&Shrines, &loading);
}

void Free_Scene() {
	G_DestroyFont();
	AEGfxTextureUnload(dummyPlayer.transform.texture);
	AEGfxMeshFree(dummyPlayer.transform.mesh);


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

	Init_Scene();
	

	// Game Loop
	while (gGameRunning)
	{
		// Informing the system about the loop's start
		AESysFrameStart();

		// Handling Input
		AEInputUpdate();

		Draw_Scene();

		Update_Scene();	// Leave update to the last, so shop overlaps the gameplay

		// Informing the system about the loop's end
		AESysFrameEnd();

		// check if forcing the application to quit
		if (AEInputCheckTriggered(AEVK_ESCAPE) || 0 == AESysDoesWindowExist())
			gGameRunning = 0;
	}

	Free_Scene();

	// free the system
	AESysExit();
}