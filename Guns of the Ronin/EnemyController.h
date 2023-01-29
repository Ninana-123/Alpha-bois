#pragma once

#ifndef ENEMYCONTROLLER_H
#define ENEMYCONTROLLER_H

#include "Samurai.h"

namespace {
	float spawnRate_Samurai = 1.0f;
	
}

void Init_Enemies(SamuraiPool& pool);

void Update_Enemies(SamuraiPool& pool, Vector2 playerPos);

void Draw_Enemies(SamuraiPool& pool);

void Push_Enemies(SamuraiPool& pool, DIRECTION direction, float targetAxis);

#endif // !1

