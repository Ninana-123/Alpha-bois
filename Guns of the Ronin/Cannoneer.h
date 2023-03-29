#pragma once


#ifndef CANNONEER_H
#define CANNONEER_H

#include "Graphics.h"
#include "Physics.h"
#include "Player.h"
#include "Bullets.h"
namespace {
	enum C_AI_STATE { C_ATTACKING, C_RELOADING };
	enum { CANNONEER_COUNT = 20 };
	enum { CANNONBALL_COUNT = 40 };
	const int CANNONEER_KILLSCORE = 150;


	float C_MIN_SPAWNDIST = 350;
	float C_MAX_SPAWNDIST = 750;
	float C_MAX_Y_SPAWNDIST = 425;
	int C_HEALTH = 350;
	float C_MS = 100.0f;
	float C_HIT_ANIM_DURATION = 0.5f;
	int C_EXP = 10;
	int C_DAMAGE = 20;
	float C_FIRERATE = 4.5f;
	AEGfxVertexList* cannoneerMesh = 0;
	//CannonBall(CB) variables 
	AEGfxVertexList* cannonBallMesh = 0;
	AEGfxVertexList* explosionMesh = 0;
	AEGfxTexture* cannoneerTexture = 0;
	AEGfxTexture* cannonBallTexture = 0;
	float C_HEIGHT = 20, C_WIDTH = 20;
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
	bool damagedByExplosion = false;
	bool isCollidingWithExplosion = false;
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



void CannoneerAdd(CannoneerPool& pool);

void Init_CannoneerPool(CannoneerPool& pool);

void AI_Cannoneer(CannoneerPool& pool, Player& player, PlayerInfo& playerInfo);

void Draw_Cannoneer(CannoneerPool& pool);

void Dmg_Cannoneer(CannoneerPool& pool, PlayerInfo playerInfo, int index);

void Free_Cannoneer();

void CannoneerRemove(int index, CannoneerPool& pool);

#endif // !CANNONEER_H
