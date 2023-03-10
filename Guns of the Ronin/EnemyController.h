#pragma once

#ifndef ENEMYCONTROLLER_H
#define ENEMYCONTROLLER_H

#include "Samurai.h"
#include "Archer.h"
#include "Cannoneer.h"
#include "Ninja.h"

namespace {
	float spawnRate_Samurai = 1.0f;
	float spawnRate_Archer = 1.0f;
	float spawnRate_Cannoneer = 1.0f;
	float spawnRate_Ninja = 1.0f;
}

void Init_Enemies(SamuraiPool& pool, ArcherPool &archPool, CannoneerPool& cPool, NinjaPool &ninPool);

void Update_Enemies(SamuraiPool& samPool, ArcherPool& archPool,CannoneerPool& cPool, NinjaPool &ninpool, Player& player, PlayerInfo& playerInfo);

void Draw_Enemies(SamuraiPool& pool, ArcherPool& archPool, CannoneerPool& cPool, NinjaPool &ninPool);

void Push_Enemies(SamuraiPool& samPool, ArcherPool& archPool, DIRECTION direction, float targetAxis, NinjaPool& ninPool);


#endif // !1

