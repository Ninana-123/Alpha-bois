#pragma once
#pragma once

#ifndef ENEMYARCHER_H
#define ENEMYARCHER_H

#include "Graphics.h"
#include "Physics.h"
#include "Player.h"
#include "bullets.h"
namespace {
	enum AI_STATE { MOVING, ATTACKING, BLOWNAWAY };
	enum { ARCHER_COUNT = 50 };
	float MIN_SPAWNDIST = 200;
	float MAX_SPAWNDIST = 400;
	int HEALTH = 100;
	float MS = 100.0f;
	float SWEEP_MS = 700.0f;
	float HIT_ANIM_DURATION = 0.5f;
	int EXP = 10;
	int DAMAGE = 5;
	AEGfxVertexList* archerMesh = 0;
	float ARCHER_HEIGHT = 20, ARCHER_WIDTH = 20;
}

class Archer {
public:
	Transform transform;
	Vector2 colPos, targetPos, collider;
	int health = HEALTH;
	AI_STATE aiState = MOVING;
	bool enabled = false;
	float timeSince_lastDmgDeal = 0;
};

struct ArcherPool {
	Archer archers[ARCHER_COUNT];
	Archer* activeArchers[ARCHER_COUNT];
	int activeSize;
};

void ArcherAdd(ArcherPool& pool, Vector2 playerPos);

void Init_ArcherPool(ArcherPool& pool);

void AI_Archer(ArcherPool& pool, Player& player, PlayerInfo& playerInfo);

void Draw_Archer(ArcherPool& pool);

void Push_Archer(ArcherPool& pool, DIRECTION direction, float targetAxis = 400);

void Dmg_Archer(ArcherPool& pool, PlayerInfo playerInfo, int index);

void Free_Archer();

#endif // !ARCHER_H
