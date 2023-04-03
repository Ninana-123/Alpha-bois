/*
\copyright
		All content(C) 2023 DigiPen Institute of Technology Singapore.All rights
		reserved.Reproduction or disclosure of this file or its contents without the prior
		written consent of DigiPen Institute of Technology is prohibited.
*/
/*!
@file Ninja.h
@author Sean Ang JiaBao
@Email ang.s@digipen.edu
@course CSD 1451
@section Section A
@date 3 March 2023
@brief This file contains function declaration for the Ninjas (enemy)
*//*______________________________________________________________________*/

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
	#define NINJA_COUNT 20
	const int NINJA_KILLSCORE = 100;
	#define NINJA_MIN_SPAWN_DIST 200
	#define NINJA_MAX_SPAWN_DIST 400
	#define NINJA_HEALTH 100
	#define NINJA_MS 100.0f
	#define NINJA_SWEEP_MS 700.0f
	//#define NINJA_HIT_ANIM_DURATION 0.5f
	//#define NINJA_EXP 10
	#define NINJA_DAMAGE 5
	#define NINJA_ATT_RANGE 160.0f
	#define NINJA_TELEPORT_MIN_DIST 130.0f
	#define NINJA_ATT_ANIM_FRAME 2
	#define NINJA_ATT_RATE 1.5f
	#define NINJA_HEIGHT 45
	#define NINJA_WIDTH 45
 	AEGfxVertexList* ninjaMesh = 0;
	AEGfxTexture* ninjaTexture = 0;
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
	bool dmgDealt = false;
	float timeLastAttack = 0;
	bool isHit = false;
	bool damagedByExplosion = false;
	bool isCollidingWithExplosion = false;
	Sprite_Animation anim{ NINJA_ATT_RATE, 2, 1, Anim_Mode::ONE_TIME };
};

struct NinjaPool {
	Ninja ninjas[NINJA_COUNT]{};
	Ninja* activeNinjas[NINJA_COUNT]{};
	int activeSize =0;
};

void Add_Ninja(NinjaPool& pool, Vector2 playerPos);

void Init_NinjaPool(NinjaPool& pool);

void AI_Ninja(NinjaPool& pool, Player& player, PlayerInfo& playerInfo);

void Draw_Ninja(NinjaPool& pool);

void Push_Ninja(NinjaPool& pool, DIRECTION direction, float targetAxis = 400);

void Dmg_Ninja(NinjaPool& pool, PlayerInfo& playerInfo, Player& player, int index);

void Free_Ninja();

void Remove_Ninja(int index, NinjaPool& pool);

#endif // !NINJA_H
