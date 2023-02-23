
#include "EnemyController.h"
#include "TimeManager.h"
#include "Player.h"
float spawnTImer = 0;
float archerSpawnTimer = 0;
float cSpawnTimer = 3;

void Init_Enemies(SamuraiPool& samPool, ProjectilePool& arrow, ArcherPool &archPool, CannoneerPool& cPool) {
	Init_SamuraiPool(samPool);
	Init_ArcherPool(archPool, arrow);
	Init_CannoneerPool(cPool);
}

void Update_Enemies(SamuraiPool& samPool, ProjectilePool& arrow, ArcherPool& archPool, CannoneerPool& cPool, Player& player, PlayerInfo& playerInfo) {
	spawnTImer += deltaTime;
	archerSpawnTimer += deltaTime;
	cSpawnTimer += deltaTime;
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
		AI_Archer(archPool, arrow, player, playerInfo);
		Projectile_AI(arrow);

		// Samurai
		if (cSpawnTimer >= spawnRate_Cannoneer) {
			cSpawnTimer = 0;
			CannoneerAdd(cPool, player.transform.position);
		}
		AI_Cannoneer(cPool, player, playerInfo);
	}

}

void Push_Enemies(SamuraiPool& samPool, ArcherPool& archPool, DIRECTION direction, float targetAxis) {
	Push_Samurai(samPool, direction, targetAxis);
	Push_Archer(archPool, direction, targetAxis);
}

void Draw_Enemies(SamuraiPool& samPool, ArcherPool& archPool, ProjectilePool &arrow, CannoneerPool& cPool) {
	Draw_Samurai(samPool);
	Draw_Archer(archPool, arrow);
	Draw_Cannoneer(cPool);
}
