#pragma once

#ifndef ENEMYCONTROLLER_H
#define ENEMYCONTROLLER_H

#include "Samurai.h"
#include "Archer.h"
#include "Cannoneer.h"
#include "Ninja.h"
#include "EnemyCounter.h"



namespace {
	float spawnRate_Samurai = 1.5f;
	float spawnRate_Archer = 3.0f;
	float spawnRate_Cannoneer = 1.0f;
	float spawnRate_Ninja = 4.0f;

	int curWave = 1;
	int spawnTotalCount[10] = { 0 };
	int curSpawnCounts[4] = { 0 };



	enum { SAMURAI = 0, ARCHER, CANNON, NINJA };

	const int spawnCounts[10][4]{
		/*Wave n    Samurai		 Archer		 Cannoneer	 Ninja		*/
		/*Wave 1*/	{10			,0			,10			,0			},
		/*Wave 2*/	{20			,5			,0			,0			},
		/*Wave 3*/	{30			,10			,0			,0			},
		/*Wave 4*/	{35			,20			,0			,0			},
		/*Wave 5*/	{40			,20			,3			,0			},
		/*Wave 6*/	{45			,20			,6			,0			},
		/*Wave 7*/	{45			,20			,6			,5			},
		/*Wave 8*/	{45			,20			,10			,10			},
		/*Wave 9*/	{55			,25			,12			,12			},
		/*Wave 10*/ {60			,25			,15			,15			},
	};
}


void Init_Enemies(SamuraiPool& pool, ArcherPool &archPool, CannoneerPool& cPool, NinjaPool &ninPool);

void Update_Enemies(SamuraiPool& samPool, ArcherPool& archPool,CannoneerPool& cPool, NinjaPool &ninpool, Player& player, PlayerInfo& playerInfo);

void Draw_Enemies(SamuraiPool& pool, ArcherPool& archPool, CannoneerPool& cPool, NinjaPool &ninPool);

void Push_Enemies(SamuraiPool& samPool, ArcherPool& archPool, DIRECTION direction, float targetAxis, NinjaPool& ninPool);

void God_Enemies(SamuraiPool& samPool, ArcherPool& archPool, NinjaPool& ninPool, CannoneerPool& canPool, int index);
#endif // !1

