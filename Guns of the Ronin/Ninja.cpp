/*
\copyright
		All content(C) 2023 DigiPen Institute of Technology Singapore.All rights
		reserved.Reproduction or disclosure of this file or its contents without the prior
		written consent of DigiPen Institute of Technology is prohibited.
*/
/*!
@file Ninja.cpp
@author Sean Ang JiaBao
@Email ang.s@digipen.edu
@course CSD 1451
@section Section A
@date 3 March 2023
@brief This file contains function definition for the Ninjas (enemy)
*//*______________________________________________________________________*/

#include "Ninja.h"
#include "TimeManager.h"
#include "HighScore.h"
#include "EnemyCounter.h"
#include "PlayerInfo.h"

#define NINJA_ATTACK_INTERVAL 1.0f

ShurikenPool shuriken;

//When a Ninja dies 
void Remove_Ninja(int index, NinjaPool& pool) {
	pool.activeNinjas[index]->enabled = false;
	// Swap pointers
	if (index < (pool.activeSize - 1)) {
		Ninja* temp = pool.activeNinjas[index];
		pool.activeNinjas[index] = pool.activeNinjas[pool.activeSize - 1];
		pool.activeNinjas[pool.activeSize - 1] = temp;
	}
	pool.activeSize -= 1;
	--enemiesLeft;
	Add_Score(NINJA_KILLSCORE);
}

//Spawning a new Ninja
void Add_Ninja(NinjaPool& pool, Vector2 playerPos) {
	for (int i = 0; i < NINJA_COUNT; i++) {
		if (pool.activeNinjas[i]->enabled == false) {
			pool.activeNinjas[i]->enabled = true;
			pool.activeNinjas[i]->health = NINJA_HEALTH;
			pool.activeNinjas[i]->isHit = false;
			pool.activeNinjas[i]->transform.position = Random_PointOutsideSquare(NINJA_MIN_SPAWN_DIST, NINJA_MAX_SPAWN_DIST, playerPos);
			pool.activeNinjas[i]->smoke.scale = { 4, 2.25f };
			pool.activeNinjas[i]->dmgDealt = false;
			pool.activeSize += 1;
			break;
		}
	}
}

// Initialising ninja pool
void Init_NinjaPool(NinjaPool& pool) {
	pool.activeSize = 0;
	Create_QuadMesh(NINJA_WIDTH, NINJA_HEIGHT, Color(0, 1, 1), ninjaMesh, 0.5f, 1.0f);
	Create_QuadMesh(NINJA_WIDTH, NINJA_HEIGHT, Color(0, 1, 1), smokeMesh, 1.0f, 1.0f);
	ninjaTexture = AEGfxTextureLoad("Assets/NinjaSpriteSheet.png");
	smokeTexture = AEGfxTextureLoad("Assets/Smoke2.png");
	for (int i = 0; i < NINJA_COUNT; i++) {
		pool.ninjas[i].enabled = false;
		pool.ninjas[i].health = NINJA_HEALTH;
		pool.ninjas[i].aiState = NINJA_MOVING;
		pool.ninjas[i].transform.mesh = &ninjaMesh;
		pool.ninjas[i].transform.texture = &ninjaTexture;
		pool.ninjas[i].transform.height = NINJA_HEIGHT;
		pool.ninjas[i].transform.width = NINJA_WIDTH;

		pool.ninjas[i].smoke.mesh = &smokeMesh;
		pool.ninjas[i].smoke.texture = &smokeTexture;
		pool.ninjas[i].smoke.height = NINJA_HEIGHT;
		pool.ninjas[i].smoke.width = NINJA_WIDTH;
		pool.ninjas[i].isHit = false;
		pool.activeNinjas[i] = &pool.ninjas[i];
	}
	Init_ShurikenPool(shuriken);
	
}

// Ninja movement, attacking state, wind shrine 
void AI_Ninja(NinjaPool& pool, Player& player, PlayerInfo& playerInfo) {
	Vector2 playerPos = player.transform.position;
	for (int i = 0; i < pool.activeSize; i++) {
		Ninja* curNinja = pool.activeNinjas[i];
		
		switch (curNinja->aiState)
		{
			// Ninja moving
		case NINJA_MOVING:
			curNinja->targetPos = playerPos;
			
			// if player within ninja attack range, switch to NINJA_ATTACKING case
			if (curNinja->transform.position.within_Dist(playerPos, NINJA_ATT_RANGE)) {
				curNinja->aiState = NINJA_ATTACKING;
				curNinja->anim.reset_Anim(player.transform);
				curNinja->anim.play_Anim();
				curNinja->anim.next_Frame(curNinja->transform);
			}

			// if player not within ninja's attack range, move towards player
			else {
				Vector2 direction = (curNinja->targetPos - curNinja->transform.position).normalize();
				curNinja->transform.position += direction * NINJA_MS * deltaTime;
				
				// Flipping direction of sprites
				if (direction.x > 0) {
					curNinja->transform.scale.x = Absf(curNinja->transform.scale.x) * -1.0f;
				}
				else {
					curNinja->transform.scale.x = Absf(curNinja->transform.scale.x);
				}
			}
			break;

			// Ninja attacking
		case NINJA_ATTACKING:
			curNinja->timeLastAttack += deltaTime;
			
			// if player not within ninja's attack range, switch to NINJA_MOVING case
			if (!curNinja->transform.position.within_Dist(playerPos, NINJA_ATT_RANGE)) {
				curNinja->aiState = NINJA_MOVING;
				curNinja->anim.reset_Anim(curNinja->transform);
				curNinja->dmgDealt = false;
			}

			// if player within ninja's attack range, start attacking
			else {
				//	If currently playing the attack animation
				if (curNinja->anim.current_Frame() == NINJA_ATT_ANIM_FRAME) {
					if (curNinja->timeLastAttack >= 1.0f / NINJA_ATT_RATE) {
						if (!curNinja->dmgDealt) {
							AEAudioPlay(ninjaThrow, mainsceneAudioGroup, 0.1f, 1.f, 0);
							ShurikenAdd(shuriken, curNinja->transform.position, player.transform.position);
							curNinja->dmgDealt = true;
							curNinja->timeLastAttack = 0;
						}			
					}
				}
				//attack animation is over, restart animation
				if (!curNinja->anim.is_Playing()) {
					curNinja->anim.play_Anim();
					curNinja->dmgDealt = false;
				}
			}

			break;

			// Wind shrine
		case NINJA_BLOWNAWAY:
			Vector2 direction = (curNinja->targetPos - curNinja->transform.position).normalize();
			curNinja->transform.position += direction * NINJA_SWEEP_MS * deltaTime;
			if (curNinja->transform.position.within_Dist(curNinja->targetPos, 15.0f)) {
				curNinja->aiState = NINJA_MOVING;
			}
			break;
		}

		// update sprite animation
		curNinja->anim.update_SpriteAnim(curNinja->transform);

		// update smoke position to stay on top of ninja
		curNinja->smoke.position = curNinja->transform.position;
		

		
	}

	// Shuriken collide with player
	for (int i = 0; i < shuriken.activeSize; ++i) {
		Shuriken* proj = shuriken.activeShuriken[i];
		proj->timeSince_lastDmgDeal += deltaTime;
		if (Col_StaticQuadQuad(proj->transform, player.transform)) {
			if (proj->timeSince_lastDmgDeal > NINJA_ATTACK_INTERVAL) {
				player_dmg(playerInfo, NINJA_DAMAGE);
				proj->timeSince_lastDmgDeal = 0;
				ShurikenRemove(i, shuriken);
			}
		}
	}
	Shuriken_AI(shuriken);	// update function of shuriken ; removes shuriken when out of boundary
}

// Player projectile colliding with ninja
void Dmg_Ninja(NinjaPool& pool, PlayerInfo& playerInfo, Player& player, int index) {

	// teleport to another location near player when smoke/ shield breaks
	if (pool.activeNinjas[index]->isHit == false) {
		pool.activeNinjas[index]->transform.position = Random_PointOutsideSquare(NINJA_TELEPORT_MIN_DIST, NINJA_ATT_RANGE, player.transform.position);
		pool.activeNinjas[index]->isHit = true;
		pool.activeNinjas[index]->anim.reset_Anim(pool.activeNinjas[index]->transform);
		pool.activeNinjas[index]->dmgDealt = false;
	}
	// if shield does not exist and ninja health below 0, remove ninja
	else{
		if ((pool.activeNinjas[index]->health -= playerInfo.att) <= 0) {
			Remove_Ninja(index, pool);
		}
	}
}


// Push Ninjas in the specified direction to the specific wordPos in the according axis
void Push_Ninja(NinjaPool& pool, DIRECTION direction, float targetAxis) {
	for (int i = 0; i < pool.activeSize; i++) {
		pool.activeNinjas[i]->aiState = NINJA_BLOWNAWAY;
		switch (direction)
		{
		case VERTICAL:
			pool.activeNinjas[i]->targetPos = Vector2(pool.activeNinjas[i]->transform.position.x, targetAxis);
			break;
		case HORIZONTAL:
			pool.activeNinjas[i]->targetPos = Vector2(targetAxis, pool.activeNinjas[i]->transform.position.y);
			break;
		default:
			break;
		}

	}
}

// Draw ninja, and shuriken
void Draw_Ninja(NinjaPool& pool) {
	for (int i = 0; i < pool.activeSize; i++) {
		Draw_Mesh(&pool.activeNinjas[i]->transform);
		
		if (!pool.activeNinjas[i]->isHit) {
			Draw_Mesh(&pool.activeNinjas[i]->smoke);
		}
	}
	Draw_Shuriken(shuriken);
	
}

// Free assets
void Free_Ninja() {
	AEGfxMeshFree(ninjaMesh);
	AEGfxMeshFree(smokeMesh);

	AEGfxTextureUnload(smokeTexture);
	AEGfxTextureUnload(ninjaTexture);
}