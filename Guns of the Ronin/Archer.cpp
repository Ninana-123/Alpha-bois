/*
\copyright
		All content(C) 2023 DigiPen Institute of Technology Singapore.All rights
		reserved.Reproduction or disclosure of this file or its contents without the prior
		written consent of DigiPen Institute of Technology is prohibited.
*/
/*!
@file Archer.cpp
@author Sean Ang JiaBao
@Email ang.s@digipen.edu
@course CSD 1451
@section Section A
@date 3 March 2023
@brief This file contains the function definitions for the archers (enemy)
*//*______________________________________________________________________*/

#include "Archer.h"
#include "HighScore.h"
#include "EnemyCounter.h"

#define ARCHER_ATTACK_DELAY 2.0f
#define ARCHER_ATTACK_INTERVAL 1.0f
ArrowPool arrow;

//When a archer dies 
void Remove_Archer(int index, ArcherPool& pool) {
	pool.activeArchers[index]->enabled = false;

	// Swap the pointers
	if (index < (pool.activeSize - 1)) {
		Archer* temp = pool.activeArchers[index];
		pool.activeArchers[index] = pool.activeArchers[pool.activeSize - 1];
		pool.activeArchers[pool.activeSize - 1] = temp;
	}
	pool.activeSize -= 1;
	--enemiesLeft;
	Add_Score(ARCHER_KILLSCORE);
}

//Spawning a new archer
void Add_Archer(ArcherPool& pool, Vector2 playerPos) {
	for (int i = 0; i < ARCHER_COUNT; i++) {
		if (pool.activeArchers[i]->enabled == false) {
			pool.activeArchers[i]->enabled = true;
			pool.activeArchers[i]->health = ARCHER_HEALTH;
			pool.activeArchers[i]->transform.texture = &archerTexture;
			pool.activeArchers[i]->transform.scale = { 4, 4 };
			pool.activeArchers[i]->transform.position = Random_PointOutsideSquare(ARCHER_MIN_SPAWN_DIST, ARCHER_MAX_SPAWN_DIST, playerPos);
			pool.activeSize += 1;
			break;
		}
	}
}

// Initialising archer pool
void Init_ArcherPool(ArcherPool& pool) {
	pool.activeSize = 0;
	Create_QuadMesh(ARCHER_WIDTH, ARCHER_HEIGHT, Color(1, 0, 0), archerMesh, 0.25f, 1.f);
	for (int i = 0; i < ARCHER_COUNT; i++) {
		pool.archers[i].enabled = false;
		pool.archers[i].health = ARCHER_HEALTH;
		pool.archers[i].aiState = ARCHER_MOVING;
		pool.archers[i].transform.mesh = &archerMesh;
		pool.archers[i].transform.height = ARCHER_HEIGHT;
		pool.archers[i].transform.width = ARCHER_WIDTH;
		pool.activeArchers[i] = &pool.archers[i];
	}
	archerTexture = AEGfxTextureLoad("Assets/ArcherSpriteSheet.png");
	Init_ArrowPool(arrow);	// initialise arrows here
}

// Archer movement, attacking, wind shrine activation
void AI_Archer(ArcherPool& pool, Player& player, PlayerInfo& playerInfo) {
	Vector2 playerPos = player.transform.position;
	for (int i = 0; i < pool.activeSize; i++) {
		Archer* curArcher = pool.activeArchers[i];

		switch (curArcher->aiState)
		{
			//	Archer moving
		case ARCHER_MOVING:
			curArcher->targetPos = playerPos;

			// if player is within attack range, switch to ARCHER_ATTACKING case
			if (curArcher->transform.position.within_Dist(playerPos, ARCHER_ATT_RANGE)) {
				curArcher->aiState = ARCHER_ATTACKING;
				curArcher->anim.play_Anim();
				curArcher->anim.next_Frame(curArcher->transform);
			}

			// if player is not within attack range, move towards player
			else {
				Vector2 direction = (curArcher->targetPos - curArcher->transform.position).normalize();
				curArcher->transform.position += direction * ARCHER_MS * deltaTime;
				if (direction.x > 0) {
					curArcher->transform.scale.x = Absf(curArcher->transform.scale.x) * -1.0f;
				}
				else {
					curArcher->transform.scale.x = Absf(curArcher->transform.scale.x);
				}
			}
			break;

			// Archer attacking
		case ARCHER_ATTACKING:
			curArcher->timeLastAttack += deltaTime;

			// if player not within archer's attacking range, switch to ARCHER_MOVING case
			if (!curArcher->transform.position.within_Dist(playerPos, ARCHER_ATT_RANGE)) {
				curArcher->aiState = ARCHER_MOVING;
				curArcher->anim.reset_Anim(curArcher->transform);
			}

			// if player within archer's attacking range, start attacking
			else {
				if (curArcher->timeLastAttack >= ARCHER_ATTACK_DELAY) {
					ArrowAdd(arrow, curArcher->transform.position, playerPos);
					AEAudioPlay(archerShoot, mainsceneAudioGroup, 0.1f, 1.f, 0);
					curArcher->timeLastAttack = 0;
				}
			}
			break;

			// Wind shrine
		case ARCHER_BLOWNAWAY:
			Vector2 direction = (curArcher->targetPos - curArcher->transform.position).normalize();
			curArcher->transform.position += direction * ARCHER_SWEEP_MS * deltaTime;
			if (curArcher->transform.position.within_Dist(curArcher->targetPos, 15.0f)) {
				curArcher->aiState = ARCHER_MOVING;
			}
			break;
		}

		// Sprite animation of archers
		curArcher->anim.update_SpriteAnim(curArcher->transform);


	}

	// Update function of the arrows
	Arrow_AI(arrow);

	// Arrow collision with player
	for (int i = 0; i < arrow.activeSize; ++i) {
		Arrow* proj = arrow.activeArrow[i];
		proj->timeSince_lastDmgDeal += deltaTime;
		if (Col_StaticQuadQuad(proj->transform, player.transform)) {
			if (proj->timeSince_lastDmgDeal > ARCHER_ATTACK_INTERVAL) {
				player_dmg(playerInfo, ARCHER_DAMAGE);
				proj->timeSince_lastDmgDeal = 0;
				ArrowRemove(i, arrow);
			}
		}
	}
}

// Player projectile colliding with archers
void Dmg_Archer(ArcherPool& pool, PlayerInfo playerInfo, int index) {

	// Check if archer health is equals to or below 0, and remove the archer
	if ((pool.activeArchers[index]->health -= playerInfo.att) <= 0) {
		Remove_Archer(index, pool);
	}
}


//Push Archers in the specified direction to the specific wordPos in the according axis
void Push_Archer(ArcherPool& pool, DIRECTION direction, float targetAxis) {
	for (int i = 0; i < pool.activeSize; i++) {
		pool.activeArchers[i]->aiState = ARCHER_BLOWNAWAY;
		switch (direction)
		{
		case VERTICAL:
			pool.activeArchers[i]->targetPos = Vector2(pool.activeArchers[i]->transform.position.x, targetAxis);
			break;
		case HORIZONTAL:
			pool.activeArchers[i]->targetPos = Vector2(targetAxis, pool.activeArchers[i]->transform.position.y);
			break;
		default:
			break;
		}

	}
}

// Draw archer and arrow
void Draw_Archer(ArcherPool& pool) {

	for (int i = 0; i < pool.activeSize; i++) {
		Draw_Mesh(&pool.activeArchers[i]->transform);
	}
	Draw_Arrow(arrow);
}

// Free texture & mesh
void Free_Archer() {
	AEGfxMeshFree(archerMesh);
	AEGfxTextureUnload(archerTexture);
}