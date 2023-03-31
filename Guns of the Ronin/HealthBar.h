#pragma once
#include "Graphics.h"
#include "PlayerInfo.h"
#include "Player.h"
#include "Samurai.h"
#include "Archer.h"
#include "Ninja.h"
#include "Cannoneer.h"

#ifndef HEALTHBAR_H
#define HEALTHBAR_H

float Health_width = 100.0f;
float Health_height = 10.0f;

namespace {
	AEGfxVertexList* healthMesh;
	AEGfxVertexList* samMesh;
	AEGfxVertexList* archMesh;
	AEGfxVertexList* ninMesh;
	AEGfxVertexList* canMesh;
}

class Health {
public:
	Transform transform;
	Transform playerBar;
	Transform samBar;
	Transform archBar;
	Transform ninBar;
	Transform canBar;
};

struct BarPool {
	Health samurais[SAMURAI_COUNT];
	Health archers[ARCHER_COUNT];
	Health ninjas[NINJA_COUNT];
	Health cannon[CANNONEER_COUNT];
};

void HealthBar_Init(BarPool& barPool,Health* health, PlayerInfo& playerinfo, SamuraiPool& samPool, ArcherPool& archPool, NinjaPool& ninPool, CannoneerPool& canPool);
void HealthBar_Update(BarPool& barPool, Health* health, PlayerInfo& playerinfo, Player* player, SamuraiPool& samPool, ArcherPool& archPool, 
	NinjaPool& ninPool, CannoneerPool& canPool);
void HealthBar_Draw(BarPool& barPool, Health* health, SamuraiPool& samPool, ArcherPool& archPool, NinjaPool& ninPool, CannoneerPool& canPool);
void HealthBar_Free();

#endif