#pragma once


#ifndef CANNONEER_H
#define CANNONEER_H

#include "Graphics.h"
#include "Physics.h"
#include "Player.h"
#include "bullets.h"
namespace {
	enum C_AI_STATE { C_ATTACKING, C_RELOADING };
	enum { CANNONEER_COUNT = 3 };
	enum { CANNONBALL_COUNT = 40 };
	float C_MIN_SPAWNDIST = 300;
	float C_MAX_SPAWNDIST = 400;
	int C_HEALTH = 250;
	float C_MS = 100.0f;
	float C_HIT_ANIM_DURATION = 0.5f;
	int C_EXP = 10;
	int C_DAMAGE = 20;
	float C_FIRERATE = 4.5f;
	AEGfxVertexList* cannoneerMesh = 0;
	//CannonBall(CB) variables 
	AEGfxVertexList* cannonBallMesh = 0;
	AEGfxVertexList* explosionMesh = 0;
	float C_HEIGHT = 25, C_WIDTH = 25;
	float CB_MAXSCALE = 2.0f;
	float CB_MS = 200;
	float CB_HEIGHT = 15, CB_WIDTH = 15;
	float CB_EXPLOSION_DURATION = 0.7f;
	float CB_EXPLOSION_RADIUS = 40.0f;
}

class Cannoneer {
public:
	Transform transform;
	int health = C_HEALTH;
	C_AI_STATE aiState = C_RELOADING;
	float timeSinceFired = 0;
	bool enabled = false;
};

struct CannonBall {
	Transform transform;
	Vector2 direction, LZ;
	float halfTotalDist, distTravelled;
	bool reachedMaxScale, exploded;
	float explosionTimer;
};

struct CannoneerPool {
	Cannoneer cannoneers[CANNONEER_COUNT];
	Cannoneer* activeCannoneers[CANNONEER_COUNT];
	CannonBall cannonBalls[CANNONBALL_COUNT];
	int activeCBSize;
	int activeSize;
};



void CannoneerAdd(CannoneerPool& pool, Vector2 playerPos);

void Init_CannoneerPool(CannoneerPool& pool);

void AI_Cannoneer(CannoneerPool& pool, Player& player, PlayerInfo& playerInfo);

void Draw_Cannoneer(CannoneerPool& pool);

void Dmg_Cannoneer(CannoneerPool& pool, PlayerInfo playerInfo, int index);

void Free_Cannoneer();

#endif // !CANNONEER_H
