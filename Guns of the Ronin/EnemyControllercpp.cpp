
#include "EnemyController.h"
#include "TimeManager.h"
#include "Player.h"
float spawnTImer = 0;

void Init_Enemies(SamuraiPool& samPool) {
	Init_SamuraiPool(samPool);

}

void Update_Enemies(SamuraiPool& samPool, Player& player, PlayerInfo& playerInfo) {
	spawnTImer += deltaTime;
	if (!IsTime_Paused()) {
		if (spawnTImer >= spawnRate_Samurai) {
			spawnTImer = 0;
			SamuraiAdd(samPool, player.transform.position);
		}
		AI_Samurai(samPool, player, playerInfo);
	}

}

void Push_Enemies(SamuraiPool& samPool, DIRECTION direction, float targetAxis) {
	Push_Samurai(samPool, direction, targetAxis);

}

void Draw_Enemies(SamuraiPool& samPool) {
	Draw_Samurai(samPool);
}
