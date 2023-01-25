#pragma once

#ifndef SAMURAI_H
#define SAMURAI_H

#include "Graphics.h"
#include "Physics.h"

namespace {
	enum { SAMURAI_COUNT = 50 };
	float MIN_SPAWNDIST = 400;
	float MAX_SPAWNDIST = 800;
	int HEALTH = 75;
	float MS = 100.0f;
	float MAX_MS = 300.0f;
	float HIT_ANIM_DURATION = 0.5f;
	int EXP = 10;
	int DAMAGE = 5;
}

class Samurai {
public:
	Transform transform;
	Vector2 colPos, targetPos, collider;
	int health;
	bool enabled, playCollideAnim, playHitAnim;;
	float collideAnimTimer, hitAnimTimer;
	float curMoveSpeed;
};

struct SamuraiPool {
	Samurai samurais[SAMURAI_COUNT];
	Samurai* activeSamurais[SAMURAI_COUNT];
	int activeSize;
};


void Init_SamuraiPool(SamuraiPool& pool);

void AI_Samurai(SamuraiPool& pool);

void Draw_Samurai(SamuraiPool& pool);

#endif // !SAMURAI_H
