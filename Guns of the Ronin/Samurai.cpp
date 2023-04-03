/*
\copyright
		All content(C) 2023 DigiPen Institute of Technology Singapore.All rights
		reserved.Reproduction or disclosure of this file or its contents without the prior
		written consent of DigiPen Institute of Technology is prohibited.
*/
/*!
@file		Samurai.cpp
@author		Zeng ZhiCheng
@Email		z.zhicheng@digipen.edu
@course		CSD 1451
@section	Section A
@date		2 April 2023
@brief		This file contains declaration of class, struct and functions used to run the Samurai enemy
*//*______________________________________________________________________*/
#include "Samurai.h"
#include "TimeManager.h"
#include "HighScore.h"
#include "EnemyCounter.h"
#include "Sound.h"


//When a samurai dies 
void Remove_Samurai(int index, SamuraiPool& pool) {
	pool.activeSamurais[index]->enabled = false;
	
	if (index < (pool.activeSize - 1)) {
		Samurai* temp = pool.activeSamurais[index];
		pool.activeSamurais[index] = pool.activeSamurais[pool.activeSize - 1];
		pool.activeSamurais[pool.activeSize - 1] = temp;
	}
	pool.activeSize -= 1;
	--enemiesLeft;
	Add_Score(SAMURAI_KILL_SCORE);
}



//Spawning a new samurai
void Add_Samurai(SamuraiPool& pool, Vector2 playerPos) {
	for (int i = 0; i < SAMURAI_COUNT; i++) {
		if (pool.activeSamurais[i]->enabled == false) {
			pool.activeSamurais[i]->enabled = true;
			pool.activeSamurais[i]->health = SAMURAI_HEALTH;
			pool.activeSamurais[i]->transform.position = Random_PointOutsideSquare(MIN_SPAWN_DIST, MAX_SPAWN_DIST, playerPos);
			//The random offset position of the player that the samurai will be chasing
			pool.activeSamurais[i]->offsetPos = Vector2(AERandFloat() * 2.0f * SAMURAI_CHASING_ERROR - SAMURAI_CHASING_ERROR, 2.0f * SAMURAI_CHASING_ERROR - SAMURAI_CHASING_ERROR);
			pool.activeSamurais[i]->hitByPlayer = false;
			pool.activeSamurais[i]->timeSinceLastHit = 0;
			pool.activeSamurais[i]->dmgDealt = false;
			pool.activeSamurais[i]->anim.reset_Anim(pool.activeSamurais[i]->transform);
			pool.activeSize += 1;
			break;
		}
	}
}

//Initialize a pool of samurais
void Init_SamuraiPool(SamuraiPool& pool) {
	pool.activeSize = 0;
	Create_QuadMesh(SAMURAI_WIDTH, SAMURAI_HEIGHT, Color(0, 1, 0), samuraiMesh, SAMURAI_TEXTURE_WIDTH, SAMURAI_TEXTURE_HEIGHT);
	for (int i = 0; i < SAMURAI_COUNT; i++) {
		pool.samurais[i].enabled = false;
		pool.samurais[i].health = SAMURAI_HEALTH;
		pool.samurais[i].aiState = MOVING;
		pool.samurais[i].transform.mesh = &samuraiMesh;
		pool.samurais[i].transform.height = SAMURAI_HEIGHT;
		pool.samurais[i].transform.width = SAMURAI_WIDTH;
		pool.samurais[i].transform.texture = &samuraiTexture;
		pool.samurais[i].transform.colliderSize = { SAMURAI_COLLIDER_WIDTH , SAMURAI_COLLIDER_HEIGHT };
		pool.activeSamurais[i] = &pool.samurais[i];
	}
	samuraiTexture = AEGfxTextureLoad("Assets/Samurai_Combined.png");
}


//Update the AI of a pool of cannoneers
void AI_Samurai(SamuraiPool& pool, Player& player, PlayerInfo& playerInfo) {

	Vector2 playerPos = player.transform.position;
	for (int i = 0; i < pool.activeSize; i++) {
		Samurai* curSamurai = pool.activeSamurais[i];

		switch (curSamurai->aiState)
		{
		case MOVING:
			curSamurai->targetPos = playerPos;
			if (curSamurai->transform.position.within_Dist(playerPos, SAMURAI_ATT_RANGE)) {
				curSamurai->aiState = ATTACKING;
				curSamurai->anim.reset_Anim(player.transform);
				curSamurai->anim.play_Anim();
				curSamurai->anim.next_Frame(curSamurai->transform);
			}
			else {
				Vector2 direction = (curSamurai->targetPos - curSamurai->transform.position - curSamurai->offsetPos).normalize();

				//If samurai was hit by player
				if (curSamurai->hitByPlayer) {
					curSamurai->timeSinceLastHit += deltaTime;
					//Move at a slower speed 
					curSamurai->transform.position += direction * SAMURAI_SLOWED_MS * deltaTime;
					//if the slow duration is over 
					if (curSamurai->timeSinceLastHit >= SAMURAI_SLOW_DURATION) {
						curSamurai->hitByPlayer = false;
						curSamurai->timeSinceLastHit = 0;
					}
				}
				else { //If was not hit by player recently
					//move at normal speed
					curSamurai->transform.position += direction * SAMURAI_MS * deltaTime;
				}

				//Flipping of the samurai's texture based on its direction of movement
				if (direction.x > 0) {
					curSamurai->transform.scale.x = Absf(curSamurai->transform.scale.x) * -1.0f;
				}
				else {
					curSamurai->transform.scale.x = Absf(curSamurai->transform.scale.x);
				}
			}
			break;
		case ATTACKING:
			//If the player moved outside of the attack range chase the player
			if (!curSamurai->transform.position.within_Dist(playerPos, SAMURAI_ATT_RANGE)) {
				curSamurai->aiState = MOVING;
				curSamurai->anim.reset_Anim(curSamurai->transform);
				curSamurai->dmgDealt = false;
			}
			else {
				//If currently playing the attack animation
				if (curSamurai->anim.current_Frame() == SAMURAI_ATT_ANIM_FRAME) {
					if (!curSamurai->dmgDealt) {
						AEAudioPlay(samuraiSlash, mainsceneAudioGroup, 0.1f, 1.f, 0);
						player_dmg(playerInfo, SAMURAI_DAMAGE);
						curSamurai->dmgDealt = true;
					}
				}
				//attack animation is over, restart animation
				if (!curSamurai->anim.is_Playing()) {
					curSamurai->anim.play_Anim();
					curSamurai->dmgDealt = false;
				}
			}
			break;
		case BLOWN_AWAY:
			Vector2 direction = (curSamurai->targetPos - curSamurai->transform.position).normalize();
			curSamurai->transform.position += direction * SAMURAI_SWEEP_MS * deltaTime;
			if (curSamurai->transform.position.within_Dist(curSamurai->targetPos, SAMURAI_BLOWN_AWAY_ERROR)) {
				curSamurai->aiState = MOVING;
			}
			break;
		}
		curSamurai->anim.update_SpriteAnim(curSamurai->transform);

	}

}

//Damage a samurai in a pool
void Dmg_Samurai(SamuraiPool& pool, PlayerInfo playerInfo, int index) {

	if ((pool.activeSamurais[index]->health -=playerInfo.att) <= 0) {
		Remove_Samurai(index, pool);
	}
	else {
		pool.activeSamurais[index]->hitByPlayer = true;
	}
}


//Push Samurais in the specified direction to the specific wordPos in the according axis
void Push_Samurai(SamuraiPool& pool, DIRECTION direction, float targetAxis) {
	for (int i = 0; i < pool.activeSize; i++) {
		pool.activeSamurais[i]->aiState = BLOWN_AWAY;
		switch (direction)
		{
		case VERTICAL:
			pool.activeSamurais[i]->targetPos = Vector2(pool.activeSamurais[i]->transform.position.x, targetAxis);
			break;
		case HORIZONTAL:
			pool.activeSamurais[i]->targetPos = Vector2(targetAxis, pool.activeSamurais[i]->transform.position.y);
			break;
		default:
			break;
		}

	}
}


void Draw_Samurai(SamuraiPool& pool) {
	for (int i = 0; i < pool.activeSize; i++) {
		Draw_Mesh(&pool.activeSamurais[i]->transform);
	}
}

void Free_Samurai() {
	AEGfxMeshFree(samuraiMesh);
	AEGfxTextureUnload(samuraiTexture);
}