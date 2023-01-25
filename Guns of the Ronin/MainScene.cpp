// ---------------------------------------------------------------------------
// includes

#include <iostream>
#include "AEEngine.h"
#include "Physics.h"
#include "Graphics.h"
#include "DummyPlayer.h"
#include "Shop.h"
#include "Player.h"

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


	int gGameRunning = 1;

	// Initialization of your own variables go here

	// Using custom window procedure
	AESysInit(hInstance, nCmdShow, 1600, 900, 1, 60, true, NULL);

	// Changing the window title
	AESysSetWindowTitle("My New Demo!");

	// reset the system modules
	AESysReset();

	//initiate Graphics
	G_Init();

	DummyPlayer dummyPlayer;
	DummyPlayer_Init(&dummyPlayer);
	
	Player player;
	Player_Init(&player);

	Shrine Shrines;
	Draw_Shrine_Init(&Shrines);

	Shop shop;
	LoadShop(&shop);

	// Game Loop
	while (gGameRunning)
	{
		// Informing the system about the loop's start
		AESysFrameStart();

		// Set the background
		AEGfxSetBackgroundColor(0.0f, 0.6f, 0.8f);



		char testCh[] = "TeStInG";
		
		G_DrawText(testCh, -200, 200);


		DummyPlayer_Update(&dummyPlayer);

		Player_Update(&player);

		Draw_Shrine_Update(&Shrines);

		

		// Handling Input
		AEInputUpdate();

		// Your own update logic goes here
		

		// Your own rendering logic goes here


		// Informing the system about the loop's end
		AESysFrameEnd();

		// check if forcing the application to quit
		if (AEInputCheckTriggered(AEVK_ESCAPE) || 0 == AESysDoesWindowExist())
			gGameRunning = 0;
	}

	G_DestroyFont();
	AEGfxTextureUnload(dummyPlayer.transform.texture);
	AEGfxMeshFree(dummyPlayer.transform.mesh);

	// free the system
	AESysExit();
}