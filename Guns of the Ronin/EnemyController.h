#pragma once

#ifndef ENEMYCONTROLLER_H
#define ENEMYCONTROLLER_H

#include "Samurai.h"
#include "Archer.h"
#include "Cannoneer.h"

namespace {
	float spawnRate_Samurai = 1.0f;
	float spawnRate_Archer = 1.0f;
	float spawnRate_Cannoneer = 5.0f;
}

void Init_Enemies(SamuraiPool& pool, ArcherPool &archPool, CannoneerPool& cPool);

void Update_Enemies(SamuraiPool& samPool, ArcherPool& archPool, CannoneerPool& cPool, Player& player, PlayerInfo& playerInfo);

void Draw_Enemies(SamuraiPool& pool, ArcherPool& archPool, CannoneerPool& cPool);

void Push_Enemies(SamuraiPool& pool, ArcherPool& archPool, DIRECTION direction, float targetAxis);

#endif // !1

