/*
\copyright
		All content(C) 2023 DigiPen Institute of Technology Singapore.All rights
		reserved.Reproduction or disclosure of this file or its contents without the prior
		written consent of DigiPen Institute of Technology is prohibited.
*/
/*!
@file void.cpp
@author Teo Sheen Yeoh
@Email t.sheenyeoh@digipen.edu
@course CSD 1450
@section Section A
@date 3 March 2023
@brief This file contains code for the credit screen.
*//*______________________________________________________________________*/
#pragma once

#ifndef SAMURAI_H
#define SAMURAI_H

#include "Graphics.h"
#include "Physics.h"
#include "Player.h"
#include "Bullets.h"
namespace {
	enum AI_STATE { MOVING, ATTACKING, BLOWNAWAY };
#define SAMURAI_COUNT 60
#define SAMURAI_KILL_SCORE 50
#define MIN_SPAWN_DIST 325.0f
#define MAX_SPAWN_DIST 450.f
#define SAMURAI_HEALTH 100
#define SAMURAI_MS 100.0f
#define SAMURAI_SWEEP_MS 700.0f
#define SAMURAI_SLOWED_MS 20.0f
#define SAMURAI_SLOW_DURATION 0.5f
#define SAMURAI_DAMAGE 5
#define SAMURAI_ATT_ANIM_FRAME 2 //The frame number of animation that is the attacking frame
#define SAMURAI_ATT_RANGE 50.0f
#define SAMURAI_BLOWN_AWAY_ERROR 15.0f
#define SAMURAI_WIDTH 75.0f
#define SAMURAI_HEIGHT 75.0f
#define SAMURAI_COLLIDER_WIDTH 37.5f 
#define SAMURAI_COLLIDER_HEIGHT 60.0f
#define SAMURAI_TEXTURE_WIDTH 0.5f
#define SAMURAI_TEXTURE_HEIGHT 1.0f

/*	This is the error offset position for samurais such that they chase a slightly offsetted position of the player, 
	this is to prevent a large group of them from stacking on top of each other without a clear indicator that there is more than one of them */
#define SAMURAI_CHASING_ERROR 6.0f
	AEGfxTexture* samuraiTexture = 0;
	AEGfxVertexList* samuraiMesh = 0;
}

class Samurai {
public:
	Transform transform;
	Vector2 targetPos, offsetPos;
	int health = SAMURAI_HEALTH;
	AI_STATE aiState = MOVING;
	bool enabled = false;
	bool dmgDealt = false;
	bool hitByPlayer = false;
	float timeSinceLastHit = 0;

	Sprite_Animation anim{ 2, 2, 1, Anim_Mode::ONE_TIME };

};

struct SamuraiPool {
	Samurai samurais[SAMURAI_COUNT];
	Samurai* activeSamurais[SAMURAI_COUNT]{ };
	int activeSize = 0;
};

void Add_Samurai(SamuraiPool& pool, Vector2 playerPos);

void Init_SamuraiPool(SamuraiPool& pool);

void AI_Samurai(SamuraiPool& pool, Player& player, PlayerInfo& playerInfo);

void Draw_Samurai(SamuraiPool& pool);

void Push_Samurai(SamuraiPool& pool, DIRECTION direction, float targetAxis = 400);

void Dmg_Samurai(SamuraiPool& pool,PlayerInfo playerInfo, int index);

void Free_Samurai();

void Remove_Samurai(int index, SamuraiPool& pool);

#endif // !SAMURAI_H
