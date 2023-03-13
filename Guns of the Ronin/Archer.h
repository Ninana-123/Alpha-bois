#pragma once

#ifndef ARCHER_H
#define ARCHER_H

#include "Graphics.h"
#include "Physics.h"
#include "Player.h"
#include "Bullets.h"
#include "ArcherArrow.h"
#include "TimeManager.h"
namespace {
	enum ARCHER_AI_STATE { ARCHER_MOVING, ARCHER_ATTACKING, ARCHER_BLOWNAWAY };
	enum { ARCHER_COUNT = 3 };
	int const ARCHER_KILLSCORE = 50;
	float ARCHER_MIN_SPAWNDIST = 200;
	float ARCHER_MAX_SPAWNDIST = 400;
	int ARCHER_HEALTH = 100;
	float ARCHER_MS = 100.0f;
	float ARCHER_SWEEP_MS = 700.0f;
	float ARCHER_HIT_ANIM_DURATION = 0.5f;
	int ARCHER_EXP = 10;
	int ARCHER_DAMAGE = 15;
	AEGfxVertexList* archerMesh = 0;
	AEGfxTexture* archerTexture = 0;
	float ARCHER_HEIGHT = 20, ARCHER_WIDTH = 20;
}

class Archer {
public:
	Transform transform;
	Vector2 colPos, targetPos, collider;
	int health = ARCHER_HEALTH;
	ARCHER_AI_STATE aiState = ARCHER_MOVING;
	bool enabled = false;
	float timeLastAttack = 0;
	Sprite_Animation anim{ 1,4,1 };
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
