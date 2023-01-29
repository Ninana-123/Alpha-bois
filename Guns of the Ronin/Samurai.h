#pragma once

#ifndef SAMURAI_H
#define SAMURAI_H

#include "Graphics.h"
#include "Physics.h"

namespace {
	enum AI_STATE { MOVING, ATTACKING, BLOWNAWAY };
	enum { SAMURAI_COUNT = 5 };
	float MIN_SPAWNDIST = 200;
	float MAX_SPAWNDIST = 400;
	int HEALTH = 75;
	float MS = 100.0f;
	float MAX_MS = 500.0f;
	float HIT_ANIM_DURATION = 0.5f;
	int EXP = 10;
	int DAMAGE = 5;
}

class Samurai {
public:
	Transform transform;
	Vector2 colPos, targetPos, collider;
	int health;
	AI_STATE aiState;
	bool enabled, playCollideAnim, playHitAnim;;
	float collideAnimTimer, hitAnimTimer;
	float curMoveSpeed;
};

struct SamuraiPool {
	Samurai samurais[SAMURAI_COUNT];
	Samurai* activeSamurais[SAMURAI_COUNT];
	int activeSize;
};

void SamuraiAdd(SamuraiPool& pool, Vector2 playerPos);

void Init_SamuraiPool(SamuraiPool& pool);

void AI_Samurai(SamuraiPool& pool, Vector2 playerPos);

void Draw_Samurai(SamuraiPool& pool);

void Push_Samurai(SamuraiPool& pool, DIRECTION direction, float targetAxis = 400);

#endif // !SAMURAI_H
