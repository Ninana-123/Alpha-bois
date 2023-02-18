
#include "EnemyController.h"
#include "TimeManager.h"
#include "Player.h"
float spawnTImer = 0;
float archerSpawnTimer = 0;

void Init_Enemies(SamuraiPool& samPool, ArcherPool &archPool) {
	Init_SamuraiPool(samPool);
	Init_ArcherPool(archPool);
}

void Update_Enemies(SamuraiPool& samPool, ArcherPool& archPool, Player& player, PlayerInfo& playerInfo) {
	spawnTImer += deltaTime;
	archerSpawnTimer += deltaTime;
	if (!IsTime_Paused()) {
		// Samurai
		if (spawnTImer >= spawnRate_Samurai) {
			spawnTImer = 0;
			SamuraiAdd(samPool, player.transform.position);
		}
		AI_Samurai(samPool, player, playerInfo);

		// Archer
		if (archerSpawnTimer >= spawnRate_Archer) {
			archerSpawnTimer = 0;
			ArcherAdd(archPool, player.transform.position);
		}
		AI_Archer(archPool, player, playerInfo);
	}

}

void Push_Enemies(SamuraiPool& samPool, ArcherPool& archPool, DIRECTION direction, float targetAxis) {
	Push_Samurai(samPool, direction, targetAxis);
	Push_Archer(archPool, direction, targetAxis);
}

void Draw_Enemies(SamuraiPool& samPool, ArcherPool& archPool) {
	Draw_Samurai(samPool);
	Draw_Archer(archPool);
}
