/*
\copyright
		All content(C) 2023 DigiPen Institute of Technology Singapore.All rights
		reserved.Reproduction or disclosure of this file or its contents without the prior
		written consent of DigiPen Institute of Technology is prohibited.
*/
/*!
@file void.cpp
@author Teo Sheen Yeoh
@Email t.sheenyeoh@digipen.edu
@course CSD 1450
@section Section A
@date 3 March 2023
@brief This file contains code for the credit screen.
*//*______________________________________________________________________*/

#include <iostream>
#include "AEEngine.h"
#include "Physics.h"
#include "Graphics.h"
#include "TimeManager.h"
#include "DummyPlayer.h"
#include "Player.h"
#include "Shrine.h"
#include "Explosion.h"
#include "EnemyController.h"
#include "PlayerInfo.h"
#include "Bullets.h"
#include "Archer.h"
#include "ArcherArrow.h"
#include "NinjaShuriken.h"
#include "MainScene.h"
#include "MainMenu.h"
#include "HealthBar.h"
#include "Void.h"
#include "PauseMenu.h"

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
	Samurai samurai;
	SamuraiPool samPool;
	ArcherPool archPool;
	CannoneerPool cPool;
	PlayerInfo playerinfo;
	BulletPool bulletPool;
	Vector2 vector;
	ArrowPool arrow;
	NinjaPool ninPool;
	ShurikenPool shuriken;
	int index;
	Health health;
	BarPool barPool;
	VoidPool voidPool;
	PauseMenu pauseMenu;
}

void Init_Scene() {


	//initiate Graphics
	//G_Init();

	//DummyPlayer_Init(&dummyPlayer);
	Shrinepool_Init(shrinePool);
	Explosionpool_Init(explosionPool);
	Player_Init(&player, bulletPool);
	Init_Enemies(samPool, archPool, cPool, ninPool);
	Init_PauseMenu();
	PlayerInfo_Init(&playerinfo);
	LevelBG = AEGfxTextureLoad("Assets/GameBG1.png");
	CreateQuadMesh(1.f,1.f,Color(1,1,1), levelMesh);
	level.transform.texture = &LevelBG;
	level.transform.position = { 0.0f,0.0f };
	level.transform.scale = { 1600.0f,-900.0f };
	level.transform.height = 1.0f;
	level.transform.width = 1.0f;
	level.transform.rotation = 0.0f;
	level.transform.mesh = &levelMesh;

	Reset_TimeMan();
	HealthBar_Init(barPool, &health, playerinfo, samPool, archPool, ninPool, cPool);
	Voidpool_Init(voidPool);


}

void Update_Scene() {

	
	Update_Time();
	SetQuadPoints(player.transform, true);

	//DummyPlayer_Update(&dummyPlayer);

	Shrine_Update(shrinePool,samPool, archPool, ninPool, player, playerinfo, explosionPool, voidPool, cPool);

	Explosion_Update( explosionPool,  archPool,  cPool,  ninPool);

	Void_Update( voidPool, samPool,archPool,cPool);

	Update_Enemies(samPool, archPool, cPool, ninPool, player, playerinfo);

	

	Update_PauseMenu(playerinfo);


	// Player bullets collision with samurais
	for (int i = 0; i < samPool.activeSize; ++i) {
		//Update AABB position of samurai
		SetQuadPoints(samPool.activeSamurais[i]->transform);

		for (int u = 0; u < bulletPool.activeSize; ++u) {
			//Update AABB position of bullets
			SetQuadPoints(bulletPool.activeBullets[u]->transform, true);
			if (StaticCol_QuadQuad(bulletPool.activeBullets[u]->transform, samPool.activeSamurais[i]->transform)) {
				Dmg_Samurai(samPool, playerinfo, i);
				BulletRemove(u, bulletPool);
			}
		}
	}

	// Player bullets collision with archers
	for (int i = 0; i < archPool.activeSize; ++i) {
		//Update AABB position of archers
		SetQuadPoints(archPool.activeArchers[i]->transform);

		for (int u = 0; u < bulletPool.activeSize; ++u) {
			//Update AABB position of bullets
			SetQuadPoints(bulletPool.activeBullets[u]->transform, true);
			if (StaticCol_QuadQuad(bulletPool.activeBullets[u]->transform, archPool.activeArchers[i]->transform)) {
				Dmg_Archer(archPool, playerinfo, i);
				BulletRemove(u, bulletPool);
			}
		}
	}

	//	Player bullets collision with cannoneers
	for (int i = 0; i < cPool.activeSize; ++i) {
		//Update AABB position of cannoneers
		SetQuadPoints(cPool.activeCannoneers[i]->transform);

		for (int u = 0; u < bulletPool.activeSize; ++u) {
			//Update AABB position of bullets
			SetQuadPoints(bulletPool.activeBullets[u]->transform, true);
			if (StaticCol_QuadQuad(bulletPool.activeBullets[u]->transform, cPool.activeCannoneers[i]->transform)) {
				Dmg_Cannoneer(cPool, playerinfo, i);
				BulletRemove(u, bulletPool);
			}
		}
	}

	//	Player bullets collision with ninja
	for (int i = 0; i < ninPool.activeSize; ++i) {
		//Update AABB position of ninjas
		SetQuadPoints(ninPool.activeNinjas[i]->transform);

		for (int u = 0; u < bulletPool.activeSize; ++u) {
			//Update AABB position of bullets
			SetQuadPoints(bulletPool.activeBullets[u]->transform, true);
			if (StaticCol_QuadQuad(bulletPool.activeBullets[u]->transform, ninPool.activeNinjas[i]->transform)) {
				Dmg_Ninja(ninPool, playerinfo, player, i);
				BulletRemove(u, bulletPool);
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

	HealthBar_Update(barPool, &health, playerinfo, &player, samPool, archPool, ninPool, cPool);
	
	
}



void Draw_Scene() {

	char strBuffer[1024];

	// Set the background 
	AEGfxSetBackgroundColor(0.0f, 0.6f, 0.8f);
	DrawMesh(&level.transform);
	Draw_Enemies(samPool, archPool, cPool, ninPool);
	Draw_Shrine( shrinePool);
	Draw_Explosions(explosionPool);
	Draw_Player(&player, bulletPool);
	HealthBar_Draw(barPool, &health, samPool, archPool, ninPool, cPool);
	Draw_Void(voidPool);
	Draw_PauseMenu(playerinfo);

	if (playerinfo.playerDead) {
		sprintf_s(strBuffer, "DEAD");
		AEGfxPrint(font, strBuffer, -0.18f, -0.1f, 2.4f, 1, 0, 0);
		//G_DrawText(dead, -50.0f, 0.f, 2.0f, Color(0, 0, 0));
	}
}

void Free_Scene() {
	
	//G_DestroyFont();
	
	//AEGfxMeshFree(dummyPlayer.transform.mesh);
	Free_PauseMenu();
	Free_Bullet();
	Free_Shrines();
	Free_Player();
	//Free_Dummy();
	Free_Samurai(); 
	Free_Archer();
	Free_Cannoneer();
	Free_Explosions();
	AEGfxMeshFree(levelMesh);
	AEGfxTextureUnload(LevelBG);
	HealthBar_Free();
	Free_Void();
	Free_Ninja();
	Free_Arrow();
	Free_Shuriken();
	
}



