
#include "EnemyController.h"
#include "TimeManager.h"
float spawnTImer = 0;

void Init_Enemies(SamuraiPool& samPool) {
	Init_SamuraiPool(samPool);

}

void Update_Enemies(SamuraiPool& samPool, Vector2 playerPos) {
	spawnTImer += deltaTime;
	if (spawnTImer >= spawnRate_Samurai) {
		spawnTImer = 0;
		SamuraiAdd(samPool, playerPos);
	}
	AI_Samurai(samPool, playerPos);
}

void Push_Enemies(SamuraiPool& samPool, DIRECTION direction, float targetAxis) {
	Push_Samurai(samPool, direction, targetAxis);

}

void Draw_Enemies(SamuraiPool& samPool) {
	Draw_Samurai(samPool);
}
