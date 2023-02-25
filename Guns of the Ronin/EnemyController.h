#pragma once

#ifndef ENEMYCONTROLLER_H
#define ENEMYCONTROLLER_H

#include "Samurai.h"
#include "Archer.h"
#include "Cannoneer.h"
#include "Ninja.h"

namespace {
	float spawnRate_Samurai = 3.0f;
	float spawnRate_Archer = 1000000000.0f;
	float spawnRate_Cannoneer = 1000000000.0f;
	float spawnRate_Ninja = 100000000000.0f;
}

void Init_Enemies(SamuraiPool& pool, ArcherPool &archPool, CannoneerPool& cPool, NinjaPool &ninPool);

void Update_Enemies(SamuraiPool& samPool, ArcherPool& archPool,CannoneerPool& cPool, NinjaPool &ninpool, Player& player, PlayerInfo& playerInfo);

void Draw_Enemies(SamuraiPool& pool, ArcherPool& archPool, CannoneerPool& cPool, NinjaPool &ninPool);

void Push_Enemies(SamuraiPool& pool, ArcherPool& archPool, DIRECTION direction, float targetAxis, NinjaPool& ninPool);


#endif // !1

