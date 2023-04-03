/*
\copyright
		All content(C) 2023 DigiPen Institute of Technology Singapore.All rights
		reserved.Reproduction or disclosure of this file or its contents without the prior
		written consent of DigiPen Institute of Technology is prohibited.
*/
/*!
@file		HealthBar.cpp
@author		Vance Tay
@Email		junfengvance.t@digipen.edu
@course		CSD 1451
@section	Section A
@date		3 March 2023
@brief		This file contains code for the credit screen.
*//*______________________________________________________________________*/
#include "PlayerInfo.h"
#include "HealthBar.h"
#include "Graphics.h"
#include "Player.h"
#include <iostream>

void Init_HealthBar(BarPool& barPool, Health* health) { 
	Create_QuadMesh(HEALTH_WIDTH, HEALTH_HEIGHT, Color(0, 1.0f, 0, 1.0f), healthMesh);
	health->playerBar.mesh = &healthMesh;

	Create_QuadMesh(HEALTH_WIDTH, HEALTH_HEIGHT, Color(1.0f, 0, 0, 1.0f), samMesh);
	for (int i = 0; i < SAMURAI_COUNT; i++) {
		barPool.samurais[i].samBar.mesh = &samMesh;
	}

	Create_QuadMesh(HEALTH_WIDTH, HEALTH_HEIGHT, Color(1.0f, 0, 0, 1.0f), archMesh);
	for (int i = 0; i < ARCHER_COUNT; i++) {
		barPool.archers[i].archBar.mesh = &archMesh;
	}

	Create_QuadMesh(HEALTH_WIDTH, HEALTH_HEIGHT, Color(1.0f, 0, 0, 1.0f), ninMesh);
	for (int i = 0; i < NINJA_COUNT; i++) {
		barPool.ninjas[i].ninBar.mesh = &ninMesh;
	}

	Create_QuadMesh(HEALTH_WIDTH, HEALTH_HEIGHT, Color(1.0f, 0, 0, 1.0f), canMesh);
	for (int i = 0; i < CANNONEER_COUNT; i++) {
		barPool.cannon[i].canBar.mesh = &canMesh;
	}
}

void HealthBar_Update(BarPool& barPool, Health* health, PlayerInfo& playerinfo, Player* player, SamuraiPool& samPool, ArcherPool& archPool, NinjaPool& ninPool, CannoneerPool& canPool) {
	//player health bar
	health->playerBar.position = player->transform.position + Vector2(HEALTH_X, HEALTH_Y);
	float CurrentPlayerHealthScale = (float)playerinfo.health / ENEMY_HEALTH * 1.0f;
	health->playerBar.scale = Vector2 (CurrentPlayerHealthScale, BAR_SCALE_Y);

	//samurai health bar
	for (int i = 0; i < samPool.activeSize; i++) {
		barPool.samurais[i].samBar.position = samPool.activeSamurais[i]->transform.position + Vector2(HEALTH_X, HEALTH_Y);
		float CurrentSamHealthScale = (float)samPool.activeSamurais[i]->health / ENEMY_HEALTH * 1.0f;
		barPool.samurais[i].samBar.scale = Vector2(CurrentSamHealthScale, BAR_SCALE_Y);
	}

	//archer health bar
	for (int i = 0; i < archPool.activeSize; i++) {
		barPool.archers[i].archBar.position = archPool.activeArchers[i]->transform.position + Vector2(HEALTH_X, HEALTH_Y);
		float CurrentArchHealthScale = (float)archPool.activeArchers[i]->health / ENEMY_HEALTH * 1.0f;
		barPool.archers[i].archBar.scale = Vector2(CurrentArchHealthScale, BAR_SCALE_Y);
	}

	//ninja health bar
	for (int i = 0; i < ninPool.activeSize; i++) {
		barPool.ninjas[i].ninBar.position = ninPool.activeNinjas[i]->transform.position + Vector2(HEALTH_X, HEALTH_Y);
		float CurrentNinjaHealthScale = (float)ninPool.activeNinjas[i]->health / ENEMY_HEALTH * 1.0f;
		barPool.ninjas[i].ninBar.scale = Vector2(CurrentNinjaHealthScale, BAR_SCALE_Y);
	}

	//cannoneer health bar
	for (int i = 0; i < canPool.activeSize; i++) {
		barPool.cannon[i].canBar.position = canPool.activeCannoneers[i]->transform.position + Vector2(HEALTH_X, HEALTH_Y);
		float CurrentCanHealthScale = (float)canPool.activeCannoneers[i]->health / ENEMY_HEALTH * 1.0f;
		barPool.cannon[i].canBar.scale = Vector2(CurrentCanHealthScale, BAR_SCALE_Y);
	}
}

void HealthBar_Draw(BarPool& barPool, Health* health, SamuraiPool& samPool, ArcherPool& archPool, NinjaPool& ninPool, CannoneerPool& canPool) {
	Draw_Mesh(&health->playerBar);
	
	for (int i = 0; i < samPool.activeSize; i++) {
		Draw_Mesh(&barPool.samurais[i].samBar);
	}

	for (int i = 0; i < archPool.activeSize; i++) {
		Draw_Mesh(&barPool.archers[i].archBar);
	}

	for (int i = 0; i < ninPool.activeSize; i++) {
		Draw_Mesh(&barPool.ninjas[i].ninBar);
	}
	
	for (int i = 0; i < canPool.activeSize; i++) {
		Draw_Mesh(&barPool.cannon[i].canBar);
	}
}

void HealthBar_Free() {
	AEGfxMeshFree(healthMesh);
	AEGfxMeshFree(samMesh);
	AEGfxMeshFree(archMesh);
	AEGfxMeshFree(ninMesh);
	AEGfxMeshFree(canMesh);
}