
/*
\copyright
		All content(C) 2023 DigiPen Institute of Technology Singapore.All rights
		reserved.Reproduction or disclosure of this file or its contents without the prior
		written consent of DigiPen Institute of Technology is prohibited.
*/
/*!
@file Archer.h
@author Sean Ang JiaBao
@Email ang.s@digipen.edu
@course CSD 1451
@section Section A
@date 3 March 2023
@brief This file contains the function declarations of the archers (enemy)
*//*______________________________________________________________________*/


#pragma once

#ifndef ARCHER_H
#define ARCHER_H

#include "Graphics.h"
#include "Physics.h"
#include "Player.h"
#include "Bullets.h"
#include "ArcherArrow.h"
#include "TimeManager.h"
namespace
{
	enum ARCHER_AI_STATE { ARCHER_MOVING, ARCHER_ATTACKING, ARCHER_BLOWNAWAY };
	#define ARCHER_COUNT 30
	int const ARCHER_KILLSCORE = 50;
	#define ARCHER_MIN_SPAWN_DIST 200
	#define ARCHER_MAX_SPAWN_DIST 400
	#define ARCHER_HEALTH 100
	#define ARCHER_MS 100.0f
	#define ARCHER_SWEEP_MS 700.0f	// For wind shrine
	#define ARCHER_DAMAGE 15
	#define ARCHER_ATT_RANGE 350
	#define ARCHER_HEIGHT 15
	#define ARCHER_WIDTH 15
	AEGfxVertexList* archerMesh = 0;
	AEGfxTexture* archerTexture = 0;
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
	bool damagedByExplosion = false;
	bool isCollidingWithExplosion = false;
};

struct ArcherPool {
	Archer archers[ARCHER_COUNT]{};
	Archer* activeArchers[ARCHER_COUNT]{};
	int activeSize = 0;
};

void Add_Archer(ArcherPool& pool, Vector2 playerPos);

void Init_ArcherPool(ArcherPool& pool);

void AI_Archer(ArcherPool& pool, Player& player, PlayerInfo& playerInfo);

void Draw_Archer(ArcherPool& pool);

void Push_Archer(ArcherPool& pool, DIRECTION direction, float targetAxis = 400);

void Dmg_Archer(ArcherPool& pool, PlayerInfo playerInfo, int index);

void Free_Archer();

void Remove_Archer(int index, ArcherPool& pool);
#endif // !ARCHER_H
