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
#include "bullets.h"


namespace {
	DummyPlayer dummyPlayer;
	Player player;
	ShrinePool shrinePool;
	Shop shop;
	SamuraiPool samPool;
	PlayerInfo playerinfo;
	BulletPool bulletPool;
}

void Init_Scene() {

	// Changing the window title
	AESysSetWindowTitle("Guns of the Ronin");
	// reset the system modules
	AESysReset();

	//initiate Graphics
	G_Init();

	DummyPlayer_Init(&dummyPlayer);
	Shrinepool_Init(shrinePool);
	Player_Init(&player, bulletPool);
	Init_Enemies(samPool);
	Shop_Init(&shop);
	PlayerInfo_Init(&playerinfo);
	
}

void Update_Scene() {
	char testCh[] = "TeStInG";

	G_DrawText(testCh, -200, 200, 1.0f);


	Update_Time();

	DummyPlayer_Update(&dummyPlayer);

	Shrine_Update( shrinePool,  player);

	

	Update_Enemies(samPool, player, playerinfo);

	Shop_Update(&shop, &playerinfo);

	
	SetQuadPoints(player.transform, 50, 50);
	for (int i = 0; i < samPool.activeSize; ++i) {
		SetQuadPoints(samPool.activeSamurais[i]->transform, 20, 20);

		for (int u = 0; u < bulletPool.activeSize; ++u) {
			SetQuadPoints(bulletPool.activeBullets[u]->transform, 15, 15);
			if (StaticCol_QuadQuad(bulletPool.activeBullets[u]->transform, samPool.activeSamurais[i]->transform)) {
				Dmg_Samurai(samPool, playerinfo, i);
				BulletRemove(u, bulletPool);
			}
		}				
	}

	//std::cout << playerinfo.health << std::endl;

	if (AEInputCheckTriggered(AEVK_T)) {
		Push_Enemies(samPool, HORIZONTAL, -500);
	}

	Player_Update(&player, bulletPool);

	
}

void Draw_Scene() {
	// Set the background 
	AEGfxSetBackgroundColor(0.0f, 0.6f, 0.8f);

	Draw_Enemies(samPool);
	Draw_Shrine( shrinePool);
	Draw_Player(&player, bulletPool);
	
	if (playerinfo.playerDead) {
		TimePause();
		char dead[] = "DEAD";
		G_DrawText(dead, 0.f, 0.f, 1.0f, Color(0, 0, 0));
	}
	Draw_Shop(&shop, &playerinfo);
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


		Update_Scene();	// Leave update to the last, so shop overlaps the gameplay

		
		Draw_Scene();


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