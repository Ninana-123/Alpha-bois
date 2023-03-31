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
	enum { SAMURAI_COUNT = 60 };
	const int SAMURAI_KILLSCORE = 50;
	float MIN_SPAWNDIST = 325;
	float MAX_SPAWNDIST = 475;
	int SAMURAI_HEALTH = 100;
	float SAMURAI_MS = 100.0f;
	float SAMURAI_SWEEP_MS = 700.0f;
	float SAMURAI_SLOWED_MS = 20.0;
	float SAMURAI_SLOW_DURATION = 0.5f;
	int EXP = 10;
	int DAMAGE = 5;
	AEGfxVertexList* samuraiMesh = 0;
	AEGfxTexture* samuraiTexture = 0;
	float SAMURAI_HEIGHT = 75, SAMURAI_WIDTH = 75;
	int SAMURAI_ATT_ANIM_FRAME = 2;	//The frame number of animation that is the attacking frame
	float SAMURAI_ATT_RANGE = 50.0f;
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
	Samurai* activeSamurais[SAMURAI_COUNT];
	int activeSize =0;
};

void SamuraiAdd(SamuraiPool& pool, Vector2 playerPos);

void Init_SamuraiPool(SamuraiPool& pool);

void AI_Samurai(SamuraiPool& pool, Player& player, PlayerInfo& playerInfo);

void Draw_Samurai(SamuraiPool& pool);

void Push_Samurai(SamuraiPool& pool, DIRECTION direction, float targetAxis = 400);

void Dmg_Samurai(SamuraiPool& pool,PlayerInfo playerInfo, int index);

void Free_Samurai();

void SamuraiRemove(int index, SamuraiPool& pool);

#endif // !SAMURAI_H
