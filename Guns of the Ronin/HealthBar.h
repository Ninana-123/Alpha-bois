/*
\copyright
		All content(C) 2023 DigiPen Institute of Technology Singapore.All rights
		reserved.Reproduction or disclosure of this file or its contents without the prior
		written consent of DigiPen Institute of Technology is prohibited.
*/
/*!
@file healthbar.h
@author Vance Tay
@Email junfengvance.t@digipen.edu
@course CSD 1451
@section Section A
@date 3 March 2023
@brief This file contains code for the credit screen.
*//*______________________________________________________________________*/
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

#define HEALTH_WIDTH 100
#define HEALTH_HEIGHT 10
#define HEALTH_X 15
#define HEALTH_Y 50
#define BAR_SCALE_Y 1

namespace {
	AEGfxVertexList* healthMesh;
	AEGfxVertexList* samMesh;
	AEGfxVertexList* archMesh;
	AEGfxVertexList* ninMesh;
	AEGfxVertexList* canMesh;
	float Health_width = 100.0f;
	float Health_height = 10.0f;
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

void HealthBar_Init(BarPool& barPool, Health* health);
void HealthBar_Update(BarPool& barPool, Health* health, PlayerInfo& playerinfo, Player* player, SamuraiPool& samPool, ArcherPool& archPool, 
	NinjaPool& ninPool, CannoneerPool& canPool);
void HealthBar_Draw(BarPool& barPool, Health* health, SamuraiPool& samPool, ArcherPool& archPool, NinjaPool& ninPool, CannoneerPool& canPool);
void HealthBar_Free();

#endif