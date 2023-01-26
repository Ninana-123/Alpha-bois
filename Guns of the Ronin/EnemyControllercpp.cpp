
#include "EnemyController.h"
#include "TimeManager.h"
float spawnTImer = 0;

void Init_Enemies(SamuraiPool& pool) {
	Init_SamuraiPool(pool);
}

void Update_Enemies(SamuraiPool& pool, Vector2 playerPos) {
	spawnTImer += deltaTime;
	if (spawnTImer >= spawnRate_Samurai) {
		spawnTImer = 0;
		SamuraiAdd(pool, playerPos);
	}
	//SamuraiAdd(pool, playerPos);
	AI_Samurai(pool);
}

void Draw_Enemies(SamuraiPool& pool) {
	Draw_Samurai(pool);
}
