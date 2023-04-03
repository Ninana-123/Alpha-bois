/*
\copyright
		All content(C) 2023 DigiPen Institute of Technology Singapore.All rights
		reserved.Reproduction or disclosure of this file or its contents without the prior
		written consent of DigiPen Institute of Technology is prohibited.
*/
/*!
@file		EnemyController.cpp
@author		Zeng ZhiCheng
@Email		z.zhicheng@digipen.edu
@course		CSD 1451
@section	Section A
@date		2 April 2023
@brief		This file contains definition of functions responsible for initializing, updating and drawing of enemies
			As well as controlling the spawning of enemies
*//*______________________________________________________________________*/
#pragma once

#ifndef ENEMYCONTROLLER_H
#define ENEMYCONTROLLER_H

#include "Samurai.h"
#include "Archer.h"
#include "Cannoneer.h"
#include "Ninja.h"
#include "EnemyCounter.h"



namespace {

#define NUM_OF_WAVES 10
#define NUM_OF_ENEMY_TYPES 4

#define SPAWN_RATE_SAMURAI 1.5f
#define SPAWN_RATE_ARCHER 3.0f
#define SPAWN_RATE_CANNONEER 4.0f
#define SPAWN_RATE_NINJA 3.5f

	int curWave = 1;
	int spawnTotalCount[NUM_OF_WAVES] = { 0 };
	int curSpawnCounts[NUM_OF_ENEMY_TYPES] = { 0 };


	enum { SAMURAI = 0, ARCHER, CANNON, NINJA };

	//Number of enemies spawned each wave
	constexpr int spawnCounts[NUM_OF_WAVES][NUM_OF_ENEMY_TYPES]{
		/*Wave n    Samurai		 Archer		 Cannoneer	 Ninja		*/
		/*Wave 1*/	{0			,0			,20			,0			},
		/*Wave 2*/	{20			,5			,0			,0			},
		/*Wave 3*/	{30			,10			,0			,0			},
		/*Wave 4*/	{35			,20			,3			,0			},
		/*Wave 5*/	{40			,20			,6			,0			},
		/*Wave 6*/	{45			,20			,6			,0			},
		/*Wave 7*/	{45			,20			,9			,5			},
		/*Wave 8*/	{45			,20			,9			,10			},
		/*Wave 9*/	{55			,25			,12			,12			},
		/*Wave 10*/ {60			,25			,15			,15			},
	};
}


void Init_Enemies(SamuraiPool& pool, ArcherPool &archPool, CannoneerPool& cPool, NinjaPool &ninPool, int startingWave = 1);

void Update_Enemies(SamuraiPool& samPool, ArcherPool& archPool,CannoneerPool& cPool, NinjaPool &ninpool, Player& player, PlayerInfo& playerInfo);

void Draw_Enemies(SamuraiPool& pool, ArcherPool& archPool, CannoneerPool& cPool, NinjaPool &ninPool);

void Push_Enemies(SamuraiPool& samPool, ArcherPool& archPool, DIRECTION direction, float targetAxis, NinjaPool& ninPool);

#endif // !1

