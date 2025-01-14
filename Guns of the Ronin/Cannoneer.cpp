/*
\copyright
		All content(C) 2023 DigiPen Institute of Technology Singapore.All rights
		reserved.Reproduction or disclosure of this file or its contents without the prior
		written consent of DigiPen Institute of Technology is prohibited.
*/
/*!
@file		Cannoneer.cpp
@author		Zeng ZhiCheng
@Email		z.zhicheng@digipen.edu
@course		CSD 1451
@section	Section A
@date		2 April 2023
@brief		This file contains declaration of class, struct and functions used to run the Cannoneer enemy
*//*______________________________________________________________________*/
#include "Cannoneer.h"
#include "TimeManager.h"
#include "HighScore.h"
#include "EnemyCounter.h"


//When a cannoneer dies 
void Remove_Cannoneer(int index, CannoneerPool& pool) {
	pool.activeCannoneers[index]->enabled = false;
	if (index < (pool.activeSize - 1)) {
		Cannoneer* temp = pool.activeCannoneers[index];
		pool.activeCannoneers[index] = pool.activeCannoneers[pool.activeSize - 1];
		pool.activeCannoneers[pool.activeSize - 1] = temp;
	}
	pool.activeSize -= 1;
	--enemiesLeft;
	Add_Score(CANNONEER_KILLSCORE);
}

//Spawning a new cannoneer
void Add_Cannoneer(CannoneerPool& pool) {
	for (int i = 0; i < CANNONEER_COUNT; i++) {
		if (pool.activeCannoneers[i]->enabled == false) {
			pool.activeCannoneers[i]->enabled = true;
			pool.activeCannoneers[i]->health = C_HEALTH;
			pool.activeCannoneers[i]->transform.texture = &cannoneerTexture;
			pool.activeCannoneers[i]->transform.position = Random_PointOutsideSquare(C_MIN_SPAWN_DIST, C_MAX_SPAWN_DIST, Vector2(0, 0));
			pool.activeCannoneers[i]->transform.position.y = AEClamp(pool.activeCannoneers[i]->transform.position.y, C_MIN_Y_SPAWN_DIST, C_MAX_Y_SPAWN_DIST);
			pool.activeSize += 1;
			break;
		}
	}
}

//initializing a pool of cannoneers
void Init_CannoneerPool(CannoneerPool& pool) {
	pool.activeSize = 0;
	pool.activeCBSize = 0;
	Create_QuadMesh(C_WIDTH, C_HEIGHT, Color(0, 0, 1), cannoneerMesh);
	Create_QuadMesh(CB_WIDTH, CB_HEIGHT, Color(0, 0, 0), cannonBallMesh);
	Create_CircleMesh(CB_EXPLOSION_RADIUS, Color(1, 0.1f, 0.1f), explosionMesh);
	for (int i = 0; i < CANNONEER_COUNT; i++) {
		pool.cannoneers[i].enabled = false;
		pool.cannoneers[i].health = C_HEALTH;
		pool.cannoneers[i].aiState = C_RELOADING;
		pool.cannoneers[i].transform.mesh = &cannoneerMesh;
		pool.cannoneers[i].transform.height = C_HEIGHT;
		pool.cannoneers[i].transform.width = C_WIDTH;
		pool.cannoneers[i].timeSinceFired = C_INITIAL_FIRE_DELAY;
		pool.activeCannoneers[i] = &pool.cannoneers[i];
	}
	for (int i = 0; i < CANNON_BALL_COUNT; ++i) {
		pool.cannonBalls[i].transform.mesh = &cannonBallMesh;
		pool.cannonBalls[i].transform.height = CB_HEIGHT;
		pool.cannonBalls[i].transform.width = CB_WIDTH;
		pool.cannonBalls[i].exploded = false;
	}
	cannoneerTexture = AEGfxTextureLoad("Assets/Cannon1.PNG");
	cannonBallTexture = AEGfxTextureLoad("Assets/CannonBall.PNG");
}

//Update the AI of a pool of cannoneers
void AI_Cannoneer(CannoneerPool& pool, Player& player, PlayerInfo& playerInfo) {

	//Update active cannoneers
	for (int i = 0; i < pool.activeSize; i++) {
		Cannoneer* curCannoneer = pool.activeCannoneers[i];
		Vector2 direction = player.transform.position - curCannoneer->transform.position;

		//FSM of cannoneers
		switch (curCannoneer->aiState)
		{
		case C_RELOADING:
			curCannoneer->timeSinceFired += deltaTime;

			//Flipping of the cannoneers's texture based on its direction of movement
			if (direction.x > 0) {
				curCannoneer->transform.scale.x = Absf(curCannoneer->transform.scale.x) * -1.0f;
			}
			else {
				curCannoneer->transform.scale.x = Absf(curCannoneer->transform.scale.x);
			}


			if (curCannoneer->timeSinceFired >= C_FIRE_RATE) {
				curCannoneer->aiState = C_ATTACKING;
				curCannoneer->timeSinceFired = 0;
			}
			break;
		case C_ATTACKING: //Fire at the player then go back to reloading state
			//Creating and initializing a new cannon ball objects
			pool.cannonBalls[pool.activeCBSize].direction = direction.normalize();
			pool.cannonBalls[pool.activeCBSize].LZ = player.transform.position;
			pool.cannonBalls[pool.activeCBSize].transform.mesh = &cannonBallMesh;
			pool.cannonBalls[pool.activeCBSize].transform.position = curCannoneer->transform.position;
			pool.cannonBalls[pool.activeCBSize].explosionTimer = 0;
			pool.cannonBalls[pool.activeCBSize].exploded = false;
			pool.cannonBalls[pool.activeCBSize].distTravelled = 0;
			pool.cannonBalls[pool.activeCBSize].halfTotalDist = direction.magnitude() / 2.0f;
			pool.cannonBalls[pool.activeCBSize].reachedMaxScale = false;
			pool.cannonBalls[pool.activeCBSize].transform.color.a = 1.0f;
			pool.cannonBalls[pool.activeCBSize].transform.texture = &cannonBallTexture;
			pool.cannonBalls[pool.activeCBSize].transform.scale = { CB_MAX_SCALE, CB_MAX_SCALE };
			pool.cannonBalls[pool.activeCBSize].dmgDealt = false;
			pool.activeCBSize += 1;
			curCannoneer->aiState = C_RELOADING;
			break;
		}
	}

	//Update all active cannon balls
	for (int i = 0; i < pool.activeCBSize; ++i) {
		CannonBall& curCB = pool.cannonBalls[i];

		//If cannon ball exploded 
		if (curCB.exploded) {
			curCB.transform.mesh = &explosionMesh;
			curCB.transform.texture = 0;
			curCB.explosionTimer += deltaTime;
			//If explosion of cannonball ended
			if (curCB.explosionTimer >= CB_EXPLOSION_DURATION) {
				curCB = pool.cannonBalls[pool.activeCBSize - 1];
				pool.activeCBSize -= 1;
				--i; //Replaced curCB with the last active one in the array so reduce i to recheck curCB
			}

			//If cannonball explosion hit player
			if (!curCB.dmgDealt && Col_QuadCircle(player.transform, curCB.transform, true)) {
				curCB.dmgDealt = true;
				Damage_Player(playerInfo, CB_DAMAGE);
			}
			//Make explosion more transparent over time
			curCB.transform.color.a = 1.0f - curCB.explosionTimer / CB_EXPLOSION_DURATION;
		}
		else {
			//If the cannon ball is near its LZ explode it
			if (curCB.transform.position.within_Dist(curCB.LZ, CB_LZ_ERROR)) {
				AEAudioPlay(cannonShoot, mainsceneAudioGroup, 0.1f, 1.f, 0);
				curCB.exploded = true;
				continue;
			}

			// Move towards its target position
			curCB.transform.position += curCB.direction * deltaTime * CB_MS;
			curCB.distTravelled += (curCB.direction * deltaTime * CB_MS).magnitude();

			//Changing the scale of the cannon ball to make it look like its flying up in the air then dropping
			float scale = 1.0f + (curCB.reachedMaxScale ? 1.0f - curCB.distTravelled / curCB.halfTotalDist : curCB.distTravelled / curCB.halfTotalDist) * (CB_MAX_SCALE - 1.0f);
			if (scale >= CB_MAX_SCALE) {
				curCB.reachedMaxScale = true;
				curCB.distTravelled = 0;
			}
			curCB.transform.scale = Vector2(scale, scale);
		}

	}
}

//Damage a cannoneer in a pool
void Dmg_Cannoneer(CannoneerPool& pool, PlayerInfo playerInfo, int index) {

	if ((pool.activeCannoneers[index]->health -= playerInfo.att) <= 0) {
		Remove_Cannoneer(index, pool);
	}
}


//Draw a pool of cannoneers
void Draw_Cannoneer(CannoneerPool& pool) {
	for (int i = 0; i < pool.activeSize; i++) {
		Draw_Mesh(&pool.activeCannoneers[i]->transform);
	}
	for (int i = 0; i < pool.activeCBSize; ++i) {
		Draw_Mesh(&pool.cannonBalls[i].transform);
	}
}

//Free cannoneer assets
void Free_Cannoneer() {
	AEGfxMeshFree(cannoneerMesh);
	AEGfxMeshFree(cannonBallMesh);
	AEGfxMeshFree(explosionMesh);
	AEGfxTextureUnload(cannoneerTexture);
	AEGfxTextureUnload(cannonBallTexture);

}