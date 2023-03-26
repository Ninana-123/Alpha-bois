
#include "Ninja.h"
#include "TimeManager.h"
#include "HighScore.h"
#include "EnemyCounter.h"


float ninjaAttDelay = 1.0f;
ShurikenPool shuriken;

//When a Ninja dies 
void NinjaRemove(int index, NinjaPool& pool) {
	pool.activeNinjas[index]->enabled = false;
	if (index < (pool.activeSize - 1)) {
		Ninja* temp = pool.activeNinjas[index];
		pool.activeNinjas[index] = pool.activeNinjas[pool.activeSize - 1];
		pool.activeNinjas[pool.activeSize - 1] = temp;
	}
	pool.activeSize -= 1;
	--enemiesLeft;
}

//Spawning a new Ninja
void NinjaAdd(NinjaPool& pool, Vector2 playerPos) {
	for (int i = 0; i < NINJA_COUNT; i++) {
		if (pool.activeNinjas[i]->enabled == false) {
			pool.activeNinjas[i]->enabled = true;
			pool.activeNinjas[i]->health = NINJA_HEALTH;
			pool.activeNinjas[i]->isHit = false;
			pool.activeNinjas[i]->transform.texture = &ninjaTexture;
			pool.activeNinjas[i]->transform.scale = { 3,3 };
			pool.activeNinjas[i]->transform.position = RandomPoint_OutsideSqaure(NINJA_MIN_SPAWNDIST, NINJA_MAX_SPAWNDIST, playerPos);
			pool.activeSize += 1;
			break;
		}
	}
}

void Init_NinjaPool(NinjaPool& pool) {
	pool.activeSize = 0;
	CreateQuadMesh(NINJA_WIDTH, NINJA_HEIGHT, Color(0, 1, 1), ninjaMesh);
	for (int i = 0; i < NINJA_COUNT; i++) {
		pool.ninjas[i].enabled = false;
		pool.ninjas[i].health = NINJA_HEALTH;
		pool.ninjas[i].aiState = NINJA_MOVING;
		pool.ninjas[i].transform.mesh = &ninjaMesh;
		pool.ninjas[i].transform.height = NINJA_HEIGHT;
		pool.ninjas[i].transform.width = NINJA_WIDTH;
		pool.ninjas[i].isHit = false;
		pool.activeNinjas[i] = &pool.ninjas[i];
	}
	Init_ShurikenPool(shuriken);
	ninjaTexture = AEGfxTextureLoad("Assets/Ninja1.PNG");
}

// Ninja movement, attacking state, wind shrine 
void AI_Ninja(NinjaPool& pool, Player& player, PlayerInfo& playerInfo) {
	Vector2 playerPos = player.transform.position;
	for (int i = 0; i < pool.activeSize; i++) {
		Ninja* curNinja = pool.activeNinjas[i];
		Shuriken* proj = shuriken.activeShuriken[i];
		switch (curNinja->aiState)
		{
		case NINJA_MOVING:
			curNinja->targetPos = playerPos;
			if (curNinja->transform.position.within_dist(playerPos, 150)) {
				curNinja->aiState = NINJA_ATTACKING;
			}
			else {
				Vector2 direction = (curNinja->targetPos - curNinja->transform.position).normalize();
				curNinja->transform.position += direction * NINJA_MS * deltaTime;
			}
			break;
		case NINJA_ATTACKING:
			curNinja->timeLastAttack += deltaTime;
			if (!curNinja->transform.position.within_dist(playerPos, 150)) {
				curNinja->aiState = NINJA_MOVING;
			}
			else {
				if (curNinja->timeLastAttack >= ninjaAttDelay) {
					ShurikenAdd(shuriken, curNinja->transform.position, playerPos);
					curNinja->timeLastAttack = 0;
				}
			}

			break;
		case NINJA_BLOWNAWAY:
			Vector2 direction = (curNinja->targetPos - curNinja->transform.position).normalize();
			curNinja->transform.position += direction * NINJA_SWEEP_MS * deltaTime;
			if (curNinja->transform.position.within_dist(curNinja->targetPos, 15.0f)) {
				curNinja->aiState = NINJA_MOVING;
			}
			break;
		}

		// Shuriken collide with player
		proj->timeSince_lastDmgDeal += deltaTime;
		if (StaticCol_QuadQuad(proj->transform, player.transform)) {
			if (proj->timeSince_lastDmgDeal > 1.0f) {
				player_dmg(playerInfo, NINJA_DAMAGE);
				proj->timeSince_lastDmgDeal = 0;
				ShurikenRemove(i, shuriken);
			}
		}
	}
	Shuriken_AI(shuriken);
}

// Player projectile colliding with ninja
void Dmg_Ninja(NinjaPool& pool, PlayerInfo playerInfo, int index) {

	if ((pool.activeNinjas[index]->health -= playerInfo.att) <= 0) {
		NinjaRemove(index, pool);
		Add_Score(NINJA_KILLSCORE);
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
		DrawMesh(&pool.activeNinjas[i]->transform);
	}
	Draw_Shuriken(shuriken);
}

// Free assets
void Free_Ninja() {
	AEGfxMeshFree(ninjaMesh);
	AEGfxTextureUnload(ninjaTexture);
}