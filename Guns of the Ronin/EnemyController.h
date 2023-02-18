#pragma once

#ifndef ENEMYCONTROLLER_H
#define ENEMYCONTROLLER_H

#include "Samurai.h"
#include "Archer.h"

namespace {
	float spawnRate_Samurai = 1.0f;
	float spawnRate_Archer = 1.0f;
}

void Init_Enemies(SamuraiPool& pool, ArcherPool &archPool);

void Update_Enemies(SamuraiPool& samPool, ArcherPool& archPool, Player& player, PlayerInfo& playerInfo);

void Draw_Enemies(SamuraiPool& pool, ArcherPool& archPool);

void Push_Enemies(SamuraiPool& pool, ArcherPool& archPool, DIRECTION direction, float targetAxis);

#endif // !1

