#pragma once

#ifndef NINJA_H
#define NINJA_H

#include "Graphics.h"
#include "Physics.h"
#include "Player.h"
#include "Bullets.h"
#include "NinjaShuriken.h"

namespace {
	enum NINJA_AI_STATE { NINJA_MOVING, NINJA_ATTACKING, NINJA_BLOWNAWAY };
	enum { NINJA_COUNT = 20 };
	const int NINJA_KILLSCORE = 100;
	float NINJA_MIN_SPAWNDIST = 200;
	float NINJA_MAX_SPAWNDIST = 400;
	int NINJA_HEALTH = 100;
	float NINJA_MS = 100.0f;
	float NINJA_SWEEP_MS = 700.0f;
	float NINJA_HIT_ANIM_DURATION = 0.5f;
	int NINJA_EXP = 10;
	int NINJA_DAMAGE = 5;
	AEGfxVertexList* ninjaMesh = 0;
	AEGfxTexture* ninjaTexture = 0;
	float NINJA_HEIGHT = 15, NINJA_WIDTH = 15;
	AEGfxVertexList* smokeMesh = 0;
	AEGfxTexture* smokeTexture = 0;
}

class Ninja {
public:
	Transform transform;
	Transform smoke;
	Vector2 colPos, targetPos, collider;
	int health = NINJA_HEALTH;
	NINJA_AI_STATE aiState = NINJA_MOVING;
	bool enabled = false;
	float timeLastAttack = 0;
	bool isHit = false;
	bool damagedByExplosion = false;
	bool isCollidingWithExplosion = false;
	Sprite_Animation anim{ 1,2,1 };
};

struct NinjaPool {
	Ninja ninjas[NINJA_COUNT];
	Ninja* activeNinjas[NINJA_COUNT];
	int activeSize;
};

void NinjaAdd(NinjaPool& pool, Vector2 playerPos);

void Init_NinjaPool(NinjaPool& pool);

void AI_Ninja(NinjaPool& pool, Player& player, PlayerInfo& playerInfo);

void Draw_Ninja(NinjaPool& pool);

void Push_Ninja(NinjaPool& pool, DIRECTION direction, float targetAxis = 400);

void Dmg_Ninja(NinjaPool& pool, PlayerInfo playerInfo, int index);

void Free_Ninja();

void NinjaRemove(int index, NinjaPool& pool);

#endif // !NINJA_H
