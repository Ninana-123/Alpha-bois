#include "PlayerInfo.h"
#include "HealthBar.h"
#include "Graphics.h"
#include "Player.h"
#include <iostream>

void HealthBar_Init(BarPool& barPool, Health* health, PlayerInfo& playerinfo, SamuraiPool& samPool, ArcherPool& archPool, NinjaPool& ninPool, CannoneerPool& canPool) {
	CreateQuadMesh(100.0f, 10.0f, Color(0, 1.0f, 0, 1.0f), healthMesh);
	health->playerBar.mesh = &healthMesh;

	CreateQuadMesh(100.0f, 10.0f, Color(1.0f, 0, 0, 1.0f), samMesh);
	for (int i = 0; i < SAMURAI_COUNT; i++) {
		barPool.samurais[i].samBar.mesh = &samMesh;
	}

	CreateQuadMesh(100.0f, 10.0f, Color(1.0f, 0, 0, 1.0f), archMesh);
	for (int i = 0; i < ARCHER_COUNT; i++) {
		barPool.archers[i].archBar.mesh = &archMesh;
	}

	CreateQuadMesh(100.0f, 10.0f, Color(1.0f, 0, 0, 1.0f), ninMesh);
	for (int i = 0; i < NINJA_COUNT; i++) {
		barPool.ninjas[i].ninBar.mesh = &ninMesh;
	}

	CreateQuadMesh(100.0f, 10.0f, Color(1.0f, 0, 0, 1.0f), canMesh);
	for (int i = 0; i < CANNONEER_COUNT; i++) {
		barPool.cannon[i].canBar.mesh = &canMesh;
	}
}

void HealthBar_Update(BarPool& barPool, Health* health, PlayerInfo& playerinfo, Player* player, SamuraiPool& samPool, ArcherPool& archPool, NinjaPool& ninPool, CannoneerPool& canPool) {
	//player health bar
	health->playerBar.position = player->transform.position + Vector2(15, 50);
	float CurrentPlayerHealthScale = (float)playerinfo.health / 100.0f * 1.0f;
	health->playerBar.scale = Vector2 (CurrentPlayerHealthScale, 1.0f);

	//samurai health bar
	for (int i = 0; i < samPool.activeSize; i++) {
		barPool.samurais[i].samBar.position = samPool.activeSamurais[i]->transform.position + Vector2(15, 50);
		float CurrentSamHealthScale = (float)samPool.activeSamurais[i]->health / 100.0f * 1.0f;
		barPool.samurais[i].samBar.scale = Vector2(CurrentSamHealthScale, 1.0f);
	}

	//archer health bar
	for (int i = 0; i < archPool.activeSize; i++) {
		barPool.archers[i].archBar.position = archPool.activeArchers[i]->transform.position + Vector2(15, 50);
		float CurrentArchHealthScale = (float)archPool.activeArchers[i]->health / 100.0f * 1.0f;
		barPool.archers[i].archBar.scale = Vector2(CurrentArchHealthScale, 1.0f);
	}

	//ninja health bar
	for (int i = 0; i < ninPool.activeSize; i++) {
		barPool.ninjas[i].ninBar.position = ninPool.activeNinjas[i]->transform.position + Vector2(15, 50);
		float CurrentNinjaHealthScale = (float)ninPool.activeNinjas[i]->health / 100.0f * 1.0f;
		barPool.ninjas[i].ninBar.scale = Vector2(CurrentNinjaHealthScale, 1.0f);
	}

	//cannoneer health bar
	for (int i = 0; i < canPool.activeSize; i++) {
		barPool.cannon[i].canBar.position = canPool.activeCannoneers[i]->transform.position + Vector2(15, 50);
		float CurrentCanHealthScale = (float)canPool.activeCannoneers[i]->health / 100.0f * 1.0f;
		barPool.cannon[i].canBar.scale = Vector2(CurrentCanHealthScale, 1.0f);
	}
}

void HealthBar_Draw(BarPool& barPool, Health* health, SamuraiPool& samPool, ArcherPool& archPool, NinjaPool& ninPool, CannoneerPool& canPool) {
	DrawMesh(&health->playerBar);
	
	for (int i = 0; i < samPool.activeSize; i++) {
		DrawMesh(&barPool.samurais[i].samBar);
	}

	for (int i = 0; i < archPool.activeSize; i++) {
		DrawMesh(&barPool.archers[i].archBar);
	}

	for (int i = 0; i < ninPool.activeSize; i++) {
		DrawMesh(&barPool.ninjas[i].ninBar);
	}
	
	for (int i = 0; i < canPool.activeSize; i++) {
		DrawMesh(&barPool.cannon[i].canBar);
	}
}

void HealthBar_Free() {
	AEGfxMeshFree(healthMesh);
	AEGfxMeshFree(samMesh);
	AEGfxMeshFree(archMesh);
	AEGfxMeshFree(ninMesh);
	AEGfxMeshFree(canMesh);
}