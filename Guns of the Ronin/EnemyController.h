#pragma once

#ifndef ENEMYCONTROLLER_H
#define ENEMYCONTROLLER_H

#include "Samurai.h"
#include "Archer.h"
#include "Cannoneer.h"

namespace {
	float spawnRate_Samurai = 3.0f;
	float spawnRate_Archer = 5.0f;
}

void Init_Enemies(SamuraiPool& pool, ProjectilePool& arrow, ArcherPool &archPool);

void Update_Enemies(SamuraiPool& samPool, ProjectilePool& arrow, ArcherPool& archPool, Player& player, PlayerInfo& playerInfo);

void Draw_Enemies(SamuraiPool& pool, ArcherPool& archPool, ProjectilePool& arrow);

void Push_Enemies(SamuraiPool& pool, ArcherPool& archPool, DIRECTION direction, float targetAxis);

#endif // !1

