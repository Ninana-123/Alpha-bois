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
#include "Shrine.h"
#include "Explosion.h"
#include "EnemyController.h"
#include "PlayerInfo.h"
#include "bullets.h"
#include "Abilities.h"
#include "Archer.h"
#include "ArcherArrow.h"
#include "NinjaShuriken.h"
#include "MainScene.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

//float timeSincePause = 0.0f;
AEGfxTexture* LevelBG;
Level level;
namespace {
	DummyPlayer dummyPlayer;
	Player player;
	ShrinePool shrinePool;
	ExplosionPool explosionPool;
	Shop shop;
	Samurai samurai;
	SamuraiPool samPool;
	ArcherPool archPool;
	CannoneerPool cPool;
	PlayerInfo playerinfo;
	BulletPool bulletPool;
	Vector2 vector;
	Abilities ability;
	ArrowPool arrow;
	NinjaPool ninPool;
	ShurikenPool shuriken;

	
}

void Init_Scene() {


	//initiate Graphics
	//G_Init();

	//DummyPlayer_Init(&dummyPlayer);
	Shrinepool_Init(shrinePool);
	Explosionpool_Init(explosionPool);
	Player_Init(&player, bulletPool);
	Init_Enemies(samPool, archPool, cPool, ninPool);
	Shop_Init(&shop);
	PlayerInfo_Init(&playerinfo);
	Abilities_Init(&playerinfo);
	LevelBG = AEGfxTextureLoad("Assets/GameBG1.png");
	CreateSpriteMesh(&level.transform, levelMesh);
	level.transform.texture = &LevelBG;
	level.transform.position = { 0.0f,0.0f };
	level.transform.scale = { 1600.0f,900.0f };
	level.transform.height = 1.0f;
	level.transform.width = 1.0f;
	level.transform.rotation = 0.0f;
	level.transform.mesh = &levelMesh;

	Reset_TimeMan();
}

void Update_Scene() {

	Update_Time();
	SetQuadPoints(player.transform, 50, 50);

	//DummyPlayer_Update(&dummyPlayer);

	Shrine_Update(shrinePool,samPool, archPool, ninPool, player, playerinfo, explosionPool);

	Explosion_Update( explosionPool, samPool);


	Update_Enemies(samPool, archPool, cPool, ninPool, player, playerinfo);

	Shop_Update(&shop, &playerinfo);

	Abilities_Update(&player, &playerinfo, vector, &ability);

	// Player bullets collision with samurais
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

	// Player bullets collision with archers
	for (int i = 0; i < archPool.activeSize; ++i) {
		SetQuadPoints(archPool.activeArchers[i]->transform, 20, 20);

		for (int u = 0; u < bulletPool.activeSize; ++u) {
			SetQuadPoints(bulletPool.activeBullets[u]->transform, 15, 15);
			if (StaticCol_QuadQuad(bulletPool.activeBullets[u]->transform, archPool.activeArchers[i]->transform)) {
				Dmg_Archer(archPool, playerinfo, i);
				BulletRemove(u, bulletPool);
			}
		}
	}

	//	Player bullets collision with cannoneers
	for (int i = 0; i < cPool.activeSize; ++i) {
		SetQuadPoints(cPool.activeCannoneers[i]->transform, 20, 20);

		for (int u = 0; u < bulletPool.activeSize; ++u) {
			SetQuadPoints(bulletPool.activeBullets[u]->transform, 15, 15);
			if (StaticCol_QuadQuad(bulletPool.activeBullets[u]->transform, cPool.activeCannoneers[i]->transform)) {
				Dmg_Cannoneer(cPool, playerinfo, i);
				BulletRemove(u, bulletPool);
			}
		}
	}

	//	Player bullets collision with ninja
	for (int i = 0; i < ninPool.activeSize; ++i) {
		SetQuadPoints(ninPool.activeNinjas[i]->transform, 20, 20);

		for (int u = 0; u < bulletPool.activeSize; ++u) {
			SetQuadPoints(bulletPool.activeBullets[u]->transform, 15, 15);
			if (StaticCol_QuadQuad(bulletPool.activeBullets[u]->transform, ninPool.activeNinjas[i]->transform)) {
				if (ninPool.activeNinjas[i]->isHit == false) {
					ninPool.activeNinjas[i]->transform.position = RandomPoint_OutsideSqaure(NINJA_MIN_SPAWNDIST, NINJA_MAX_SPAWNDIST, player.transform.position);
					//printf("teleport");
					BulletRemove(u, bulletPool);
					ninPool.activeNinjas[i]->isHit = true;
				}
				else {
					Dmg_Ninja(ninPool, playerinfo, i);
					BulletRemove(u, bulletPool);
				}
			}
		}
	}

	//std::cout << playerinfo.health << std::endl;
	//wind sweep
	//if (AEInputCheckTriggered(AEVK_T)) {
	//	Push_Enemies(samPool, archPool, HORIZONTAL, -500, ninPool);
	//}

	//heal player
	if (AEInputCheckTriggered(AEVK_H)) {
		Heal_player(playerinfo);
		std::cout << playerinfo.health << std::endl;
	}

	//timeSincePause += deltaTime;

	//time freeze for enemy
	if (AEInputCheckTriggered(AEVK_P)) {
		//TimePauseEnemy();
		//timeSincePause = 0.0f;
	}

	/*if (timeSincePause >= 2.0f) {
		TimeEnemyResume();
	}*/


	Player_Update(&player, bulletPool);

	
	
}



void Draw_Scene() {
	// Set the background 
	AEGfxSetBackgroundColor(0.0f, 0.6f, 0.8f);
	int index = 0;
	DrawSprite(&level.transform, index);
	Draw_Enemies(samPool, archPool, cPool, ninPool);
	Draw_Shrine( shrinePool);
	Draw_Explosions(explosionPool);
	Draw_Player(&player, bulletPool);
	
	if (playerinfo.playerDead) {
		TimePause();
		char dead[] = "DEAD";
		G_DrawText(dead, -50.0f, 0.f, 2.0f, Color(0, 0, 0));
	}
	Draw_Shop(&shop, &playerinfo);
}

void Free_Scene() {
	
	G_DestroyFont();
	
	//AEGfxMeshFree(dummyPlayer.transform.mesh);

	Free_Bullet();
	Free_Shop();
	Free_Shrines();
	Free_Player();
	//Free_Dummy();
	Free_Samurai(); 
	Free_Archer();
	Free_Cannoneer();
	Free_Explosions();
	AEGfxMeshFree(levelMesh);
	AEGfxTextureUnload(LevelBG);
}



//// ---------------------------------------------------------------------------
//// main
//
//int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
//	_In_opt_ HINSTANCE hPrevInstance,
//	_In_ LPWSTR    lpCmdLine,
//	_In_ int       nCmdShow)
//{
//
//	SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
//
//	UNREFERENCED_PARAMETER(hPrevInstance);
//	UNREFERENCED_PARAMETER(lpCmdLine);
//
//	srand(static_cast<unsigned>(time(0)));
//
//	int gGameRunning = 1;
//
//	// Initialization of your own variables go here
//
//	// Using custom window procedure
//	AESysInit(hInstance, nCmdShow, 1600, 900, 1, 60, true, NULL);
//
//	Init_Scene();
//	
//
//	// Game Loop
//	while (gGameRunning)
//	{
//		// Informing the system about the loop's start
//		AESysFrameStart();
//
//		// Handling Input
//		AEInputUpdate();
//
//
//		Update_Scene();	
//
//		
//		Draw_Scene();
//
//
//		// Informing the system about the loop's end
//		AESysFrameEnd();
//
//		// check if forcing the application to quit
//		if (AEInputCheckTriggered(AEVK_ESCAPE) || 0 == AESysDoesWindowExist())
//			gGameRunning = 0;
//	}
//
//	Free_Scene();
//
//
//	// free the system
//	AESysExit();
//	_CrtDumpMemoryLeaks();
//}