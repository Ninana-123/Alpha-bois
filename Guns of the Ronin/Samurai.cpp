
#include "Samurai.h"

extern float dt;


//When a samurai dies 
void SamuraiRemove(int index, SamuraiPool& pool) {
	pool.activeSamurais[index]->enabled = false;
	if (index < (pool.activeSize - 1)) {
		Samurai* temp = pool.activeSamurais[index];
		pool.activeSamurais[index] = pool.activeSamurais[pool.activeSize - 1];
		pool.activeSamurais[pool.activeSize - 1] = temp;
	}
	pool.activeSize -= 1;
}

//Spawning a new samurai
void SamuraiAdd(SamuraiPool& pool, Vector2 playerPos) {
	for (int i = 0; i < SAMURAI_COUNT; i++) {
		if (pool.activeSamurais[i]->enabled == 0) {
			pool.activeSamurais[i]->enabled = 1;
			pool.activeSamurais[i]->health = HEALTH;
			pool.activeSamurais[i]->transform.position = RandomPoint_OutsideSqaure(MIN_SPAWNDIST, MAX_SPAWNDIST, playerPos);
			pool.activeSamurais[i]->curMoveSpeed = MS;
			pool.activeSize += 1;
			break;
		}
	}
}

void Init_SamuraiPool(SamuraiPool& pool) {
	pool.activeSize = 0;
	for (int i = 0; i < SAMURAI_COUNT; i++) {
		pool.samurais[i].enabled = 0;
		pool.samurais[i].health = HEALTH;
		pool.samurais[i].hitAnimTimer = 0;
		CreateQuadMesh(30, 50, Color(0, 1, 0), pool.samurais[i].transform);
		pool.activeSamurais[i] = &pool.samurais[i];
	}
}

void AI_Samurai(SamuraiPool& pool) {

}

void Draw_Samurai(SamuraiPool& pool) {
	for (int i = 0; i < pool.activeSize; i++) {
		DrawMesh(&pool.activeSamurais[i]->transform);
	}
}