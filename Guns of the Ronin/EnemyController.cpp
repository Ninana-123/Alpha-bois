
#include "EnemyController.h"
#include "TimeManager.h"
#include "Player.h"
#include "MainMenu.h"

float spawnTImer = 0;
float archerSpawnTimer = 0;
float cSpawnTimer = 0;
float ninjaSpawnTimer = 0;
//s32 mousePosX;
//s32 mousePosY;
//
//s32* mouseX = &mousePosX;
//s32* mouseY = &mousePosY;
int enemiesLeft = 0;


void Init_Enemies(SamuraiPool& samPool, ArcherPool &archPool, CannoneerPool& cPool, NinjaPool &ninPool) {
	Init_SamuraiPool(samPool);
	Init_ArcherPool(archPool);
	Init_CannoneerPool(cPool);
	Init_NinjaPool(ninPool);

	for (int i = 0; i < 10; ++i) {
		spawnTotalCount[i] = 0;
		for (int u = 0; u < 4; ++u) {
			spawnTotalCount[i] += spawnCounts[i][u];
		}
	}
	curWave = 1, enemiesLeft = spawnTotalCount[0];

	for (int i = 0; i < 4; ++i) {
		curSpawnCounts[i] = 0;
	}

}

void Update_Enemies(SamuraiPool& samPool, ArcherPool& archPool, CannoneerPool& cPool, NinjaPool& ninPool, Player& player, PlayerInfo& playerInfo) {
	spawnTImer += deltaTime;
	archerSpawnTimer += deltaTime;
	cSpawnTimer += deltaTime;
	ninjaSpawnTimer += deltaTime;

	if (!IsTime_Paused() && !IsTime_Paused_Enemy()) {
		// Samurai
		if (spawnTImer >= spawnRate_Samurai && curSpawnCounts[SAMURAI] < spawnCounts[curWave - 1][SAMURAI]) {
			spawnTImer = 0;
			SamuraiAdd(samPool, player.transform.position);
			++curSpawnCounts[SAMURAI];
			std::cout << curSpawnCounts[SAMURAI] <<"\n";
		}
		AI_Samurai(samPool, player, playerInfo);

		// Archer
		if (archerSpawnTimer >= spawnRate_Archer && curSpawnCounts[ARCHER] < spawnCounts[curWave - 1][ARCHER]) {
			archerSpawnTimer = 0;
			ArcherAdd(archPool, player.transform.position);
			++curSpawnCounts[ARCHER];
		}
		AI_Archer(archPool, player, playerInfo);


		// Cannoneer
		if (cSpawnTimer >= spawnRate_Cannoneer && curSpawnCounts[CANNON] < spawnCounts[curWave - 1][CANNON]) {
			cSpawnTimer = 0;
			CannoneerAdd(cPool, player.transform.position);
			++curSpawnCounts[CANNON];
		}
		AI_Cannoneer(cPool, player, playerInfo);

	//	// Ninja
		if (ninjaSpawnTimer >= spawnRate_Ninja && curSpawnCounts[NINJA] < spawnCounts[curWave - 1][NINJA]) {
			ninjaSpawnTimer = 0;
			NinjaAdd(ninPool, player.transform.position);
			++curSpawnCounts[NINJA];
		}
		AI_Ninja(ninPool, player, playerInfo);
	}

	//all enemies in the current wave defeated
	if (!enemiesLeft) {
		++curWave;
		enemiesLeft = spawnTotalCount[curWave - 1];
		for (int i = 0; i < 4; ++i) {
			curSpawnCounts[i] = 0;
		}
	}
}

void Push_Enemies(SamuraiPool& samPool, ArcherPool& archPool, DIRECTION direction, float targetAxis, NinjaPool& ninPool) {
	Push_Samurai(samPool, direction, targetAxis);
	Push_Archer(archPool, direction, targetAxis);
	Push_Ninja(ninPool, direction, targetAxis);
}

//void God_Enemies(SamuraiPool& samPool, ArcherPool& archPool, NinjaPool& ninPool, CannoneerPool& canPool, int index)
//{
//	AEInputGetCursorPosition(mouseX, mouseY);
//	*mouseX = *mouseX - 800;
//	*mouseY = (*mouseY - 450) * -1;
//	for (int i = 0; i < samPool.activeSize; ++i)
//	{
//		if (IsButtonHover(samPool.activeSamurais[i]->transform.position.x, samPool.activeSamurais[i]->transform.position.y,
//			samPool.activeSamurais[i]->transform.width, samPool.activeSamurais[i]->transform.height, mouseX, mouseY))
//		{
//			//std::cout << "in" << std::endl;
//			if (AEInputCheckTriggered(AEVK_LBUTTON))
//			{
//				//std::cout << "pressed" << std::endl;
//				SamuraiRemove(index, samPool);
//			}
//		}
//	}
//}


void Draw_Enemies(SamuraiPool& samPool, ArcherPool& archPool, CannoneerPool& cPool, NinjaPool &ninPool) {
	Draw_Samurai(samPool);
	Draw_Archer(archPool);
	Draw_Cannoneer(cPool);
	Draw_Ninja(ninPool);

	char strBuffer[1024];
	sprintf_s(strBuffer, "Wave: %d", curWave);
	AEGfxPrint(font, strBuffer, -0.1f, 0.9f, 2, 0, 0, 0);
	sprintf_s(strBuffer, "Enemies Left: %d", enemiesLeft);
	AEGfxPrint(font, strBuffer, -0.15f, 0.8f, 1.5, 0, 0, 0);
}
