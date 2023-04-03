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
#include "HighScore.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

//float timeSincePause = 0.0f;
AEGfxTexture* LevelBG;
Level level;
int startingWave = 0;
#define LEVEL_BG_SCALE_X 1600.f
#define LEVEL_BG_SCALE_Y 900.f
#define LEVEL_BG_HEIGHT 1.f
#define LEVEL_BG_WIDTH 1.f
#define LEVEL_BG_ROTATION 0.f

namespace {
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

	Init_ShrinePool(shrinePool);
	Init_ExplosionPool(explosionPool);
	Init_Player(&player, bulletPool);
	Init_Enemies(samPool, archPool, cPool, ninPool, startingWave);
	Init_PauseMenu();
	PlayerInfo_Init(&playerinfo);
	LevelBG = AEGfxTextureLoad("Assets/GameBG1.png");
	Create_QuadMesh(1.f,1.f,Color(1,1,1), levelMesh);
	level.transform.texture = &LevelBG;
	level.transform.position = { 0.0f,0.0f };
	level.transform.scale = { LEVEL_BG_SCALE_X,-LEVEL_BG_SCALE_Y };
	level.transform.height = LEVEL_BG_HEIGHT;
	level.transform.width = LEVEL_BG_WIDTH;
	level.transform.rotation = LEVEL_BG_ROTATION;
	level.transform.mesh = &levelMesh;

	Reset_TimeMan();
	Reset_HighScore();
	Init_HealthBar(barPool, &health);
	Init_VoidPool(voidPool);
	AEAudioPlay(mainsceneSong, mainsceneAudioGroup, 0.2f, 1.f, -1);

}

void Update_Scene() {

	AEAudioResumeGroup(mainsceneAudioGroup);
	Update_TimeMan();
	Set_QuadPoints(player.transform, true);

	Update_Shrine(shrinePool,samPool, archPool, ninPool, player, playerinfo, explosionPool, voidPool, cPool);

	Update_Explosion( explosionPool,  archPool,  cPool,  ninPool);

	Update_Void( voidPool, samPool,archPool,cPool);

	Update_Enemies(samPool, archPool, cPool, ninPool, player, playerinfo);

	

	Update_PauseMenu(playerinfo);


	// Player bullets collision with samurais
	for (int i = 0; i < samPool.activeSize; ++i) {
		//Update AABB position of samurai
		Set_QuadPoints(samPool.activeSamurais[i]->transform);

		for (int u = 0; u < bulletPool.activeSize; ++u) {
			//Update AABB position of bullets
			Set_QuadPoints(bulletPool.activeBullets[u]->transform, true);
			if (Col_StaticQuadQuad(bulletPool.activeBullets[u]->transform, samPool.activeSamurais[i]->transform)) {
				Dmg_Samurai(samPool, playerinfo, i);
				Remove_Bullet(u, bulletPool);
			}
		}
	}

	// Player bullets collision with archers
	for (int i = 0; i < archPool.activeSize; ++i) {
		//Update AABB position of archers
		Set_QuadPoints(archPool.activeArchers[i]->transform);

		for (int u = 0; u < bulletPool.activeSize; ++u) {
			//Update AABB position of bullets
			Set_QuadPoints(bulletPool.activeBullets[u]->transform, true);
			if (Col_StaticQuadQuad(bulletPool.activeBullets[u]->transform, archPool.activeArchers[i]->transform)) {
				Dmg_Archer(archPool, playerinfo, i);
				Remove_Bullet(u, bulletPool);
			}
		}
	}

	//	Player bullets collision with cannoneers
	for (int i = 0; i < cPool.activeSize; ++i) {
		//Update AABB position of cannoneers
		Set_QuadPoints(cPool.activeCannoneers[i]->transform);

		for (int u = 0; u < bulletPool.activeSize; ++u) {
			//Update AABB position of bullets
			Set_QuadPoints(bulletPool.activeBullets[u]->transform, true);
			if (Col_StaticQuadQuad(bulletPool.activeBullets[u]->transform, cPool.activeCannoneers[i]->transform)) {
				Dmg_Cannoneer(cPool, playerinfo, i);
				Remove_Bullet(u, bulletPool);
			}
		}
	}

	//	Player bullets collision with ninja
	for (int i = 0; i < ninPool.activeSize; ++i) {
		//Update AABB position of ninjas
		Set_QuadPoints(ninPool.activeNinjas[i]->transform);

		for (int u = 0; u < bulletPool.activeSize; ++u) {
			//Update AABB position of bullets
			Set_QuadPoints(bulletPool.activeBullets[u]->transform, true);
			if (Col_StaticQuadQuad(bulletPool.activeBullets[u]->transform, ninPool.activeNinjas[i]->transform)) {
				Dmg_Ninja(ninPool, playerinfo, player, i);
				Remove_Bullet(u, bulletPool);
			}
			
		}
	}

	Update_Player(&player, bulletPool);

	HealthBar_Update(barPool, &health, playerinfo, &player, samPool, archPool, ninPool, cPool);
	
	
}



void Draw_Scene() {

	// Set the background 
	AEGfxSetBackgroundColor(0.0f, 0.6f, 0.8f);
	Draw_Mesh(&level.transform);
	Draw_Enemies(samPool, archPool, cPool, ninPool);
	Draw_Shrine( shrinePool);
	Draw_Explosions(explosionPool);
	HealthBar_Draw(barPool, &health, samPool, archPool, ninPool, cPool);
	Draw_Void(voidPool);
	Draw_Player(&player, bulletPool);
	Draw_PauseMenu(playerinfo);
}

void Free_Scene() {
	
	Free_PauseMenu();
	Free_Bullet();
	Free_Shrines();
	Free_Player();
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
	
	//If game was not ended by player killing all enemies in all waves (player died)
	if (!gameEnded) {
		Finalize_HighScore(true);
	}
}

void Set_StartingWave(int waveNum) {
	startingWave = waveNum;
}

