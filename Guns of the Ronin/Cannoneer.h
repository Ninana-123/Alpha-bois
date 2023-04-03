
/*
\copyright
		All content(C) 2023 DigiPen Institute of Technology Singapore.All rights
		reserved.Reproduction or disclosure of this file or its contents without the prior
		written consent of DigiPen Institute of Technology is prohibited.
*/
/*!
@file		Cannoneer.h
@author		Zeng ZhiCheng
@Email		z.zhicheng@digipen.edu
@course		CSD 1451
@section	Section A
@date		2 April 2023
@brief		This file contains declaration of variables, functions and structs used to run the Cannoneer enemy
*//*______________________________________________________________________*/
#pragma once


#ifndef CANNONEER_H
#define CANNONEER_H

#include "Graphics.h"
#include "Physics.h"
#include "Player.h"
#include "Bullets.h"
namespace {
	enum C_AI_STATE { C_ATTACKING, C_RELOADING };
#define CANNONEER_COUNT 20
#define CANNON_BALL_COUNT 40
#define CANNONEER_KILLSCORE 150


#define C_MIN_SPAWN_DIST 350
#define C_MAX_SPAWN_DIST 750
#define C_MAX_Y_SPAWN_DIST 425
#define C_HEALTH 350
#define C_MS 100.0f
#define C_HIT_ANIM_DURATION 0.5f
#define C_EXP 10
#define C_FIRE_RATE 4.5f
#define C_INITIAL_FIRE_DELAY 2.5f
	AEGfxVertexList* cannoneerMesh = 0;
	//CannonBall(CB) variables 
	AEGfxVertexList* cannonBallMesh = 0;
	AEGfxVertexList* explosionMesh = 0;
	AEGfxTexture* cannoneerTexture = 0;
	AEGfxTexture* cannonBallTexture = 0;
#define C_HEIGHT 60.0f
#define C_WIDTH 60.0f
#define CB_DAMAGE 20
#define CB_MAX_SCALE 2.0f
#define CB_MS 200.0f
#define CB_HEIGHT 20.0f
#define CB_WIDTH 20.0f
#define CB_EXPLOSION_DURATION 0.7f
#define CB_EXPLOSION_RADIUS 40.0f
#define CB_LZ_ERROR 5.0f  //The error of margin in case the game lags and the cannonball travels too far off the LZ
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
	float halfTotalDist = 0.0f;
	float distTravelled = 0.0f;
	bool reachedMaxScale;
	bool exploded = false;
	bool dmgDealt = false;
	float explosionTimer = 0.0f;
};

struct CannoneerPool {
	Cannoneer cannoneers[CANNONEER_COUNT]{};
	Cannoneer* activeCannoneers[CANNONEER_COUNT]{};
	CannonBall cannonBalls[CANNON_BALL_COUNT]{};
	int activeCBSize = 0;
	int activeSize = 0;
};



void Add_Cannoneer(CannoneerPool& pool);

void Init_CannoneerPool(CannoneerPool& pool);

void AI_Cannoneer(CannoneerPool& pool, Player& player, PlayerInfo& playerInfo);

void Draw_Cannoneer(CannoneerPool& pool);

void Dmg_Cannoneer(CannoneerPool& pool, PlayerInfo playerInfo, int index);

void Free_Cannoneer();

void Remove_Cannoneer(int index, CannoneerPool& pool);

#endif // !CANNONEER_H
