#pragma once

#ifndef SAMURAI_H
#define SAMURAI_H

#include "Graphics.h"
#include "Physics.h"
#include "Player.h"
#include "Bullets.h"
namespace {
	enum AI_STATE { MOVING, ATTACKING, BLOWNAWAY };
	enum { SAMURAI_COUNT = 60 };
	const int SAMURAI_KILLSCORE = 50;
	float MIN_SPAWNDIST = 200;
	float MAX_SPAWNDIST = 400;
	int HEALTH = 100;
	float MS = 100.0f;
	float SWEEP_MS = 700.0f;
	float HIT_ANIM_DURATION = 0.5f;
	int EXP = 10;
	int DAMAGE = 5;
	AEGfxVertexList* samuraiMesh = 0;
	AEGfxTexture* samuraiTexture = 0;
	float SAMURAI_HEIGHT = 20, SAMURAI_WIDTH = 20;
}

class Samurai {
public:
	Transform transform;
	Vector2 targetPos, offsetPos;
	int health = HEALTH;
	AI_STATE aiState = MOVING;
	bool enabled = false;
	float timeSince_lastDmgDeal = 0;
	bool damagedByExplosion = false;
	bool isCollidingWithExplosion = false;
	int ID;
	Sprite_Animation anim{ 2,2,1 };

};

struct SamuraiPool {
	Samurai samurais[SAMURAI_COUNT];
	Samurai* activeSamurais[SAMURAI_COUNT];
	int activeSize;
};

void SamuraiAdd(SamuraiPool& pool, Vector2 playerPos);

void Init_SamuraiPool(SamuraiPool& pool);

void AI_Samurai(SamuraiPool& pool, Player& player, PlayerInfo& playerInfo);

void Draw_Samurai(SamuraiPool& pool);

void Push_Samurai(SamuraiPool& pool, DIRECTION direction, float targetAxis = 400);

void Dmg_Samurai(SamuraiPool& pool,PlayerInfo playerInfo, int index);

void Die_Samurai(SamuraiPool& pool, int index);

void Free_Samurai();

void SamuraiRemove(int index, SamuraiPool& pool);

#endif // !SAMURAI_H
