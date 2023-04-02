/*
\copyright
		All content(C) 2023 DigiPen Institute of Technology Singapore.All rights
		reserved.Reproduction or disclosure of this file or its contents without the prior
		written consent of DigiPen Institute of Technology is prohibited.
*/
/*!
@file		EnemyController.cpp
@author		Zeng ZhiCheng
@Email		z.zhicheng@digipen.edu
@course		CSD 1451
@section	Section A
@date		2 April 2023
@brief		This file contains definition of functions responsible for initializing, updating and drawing of enemies
			As well as controlling the spawning of enemies
*//*______________________________________________________________________*/
#include "EnemyController.h"
#include "TimeManager.h"
#include "Player.h"
#include "MainMenu.h"
#include "HighScore.h"

float samuraiSpawnTimer = 0;
float archerSpawnTimer = 0;
float cSpawnTimer = 0;
float ninjaSpawnTimer = 0;

#define WAVE_COUNT_TEXT_X_POS -0.1f
#define WAVE_COUNT_TEXT_Y_POS 0.85f
#define ENEMIES_LEFT_TEXT_X_POS -0.15f
#define ENEMIES_LEFT_TEXT_Y_POS 0.75f
#define ENEMY_CONTROLLER_TEXT_SCALE 0.75f
int enemiesLeft = 0;


void Init_Enemies(SamuraiPool& samPool, ArcherPool &archPool, CannoneerPool& cPool, NinjaPool &ninPool) {
	Init_SamuraiPool(samPool);
	Init_ArcherPool(archPool);
	Init_CannoneerPool(cPool);
	Init_NinjaPool(ninPool);

	for (int i = 0; i < NUM_OF_WAVES; ++i) {
		spawnTotalCount[i] = 0;
		for (int u = 0; u < NUM_OF_ENEMY_TYPES; ++u) {
			spawnTotalCount[i] += spawnCounts[i][u];
		}
	}
	curWave = 9, enemiesLeft = spawnTotalCount[8];

	for (int i = 0; i < NUM_OF_ENEMY_TYPES; ++i) {
		curSpawnCounts[i] = 0;
	}

}

void Update_Enemies(SamuraiPool& samPool, ArcherPool& archPool, CannoneerPool& cPool, NinjaPool& ninPool, Player& player, PlayerInfo& playerInfo) {
	samuraiSpawnTimer += deltaTime;
	archerSpawnTimer += deltaTime;
	cSpawnTimer += deltaTime;
	ninjaSpawnTimer += deltaTime;

	if (!IsTime_Paused() && !IsTime_Paused_Enemy()) {
		// Samurai
		if (samuraiSpawnTimer >= SPAWN_RATE_SAMURAI && curSpawnCounts[SAMURAI] < spawnCounts[curWave - 1][SAMURAI]) {
			samuraiSpawnTimer = 0;
			Add_Samurai(samPool, player.transform.position);
			++curSpawnCounts[SAMURAI];
			//std::cout << curSpawnCounts[SAMURAI] <<"\n";
		}
		AI_Samurai(samPool, player, playerInfo);

		// Archer
		if (archerSpawnTimer >= SPAWN_RATE_ARCHER && curSpawnCounts[ARCHER] < spawnCounts[curWave - 1][ARCHER]) {
			archerSpawnTimer = 0;
			ArcherAdd(archPool, player.transform.position);
			++curSpawnCounts[ARCHER];
		}
		AI_Archer(archPool, player, playerInfo);


		// Cannoneer
		if (cSpawnTimer >= SPAWN_RATE_CANNONEER  && curSpawnCounts[CANNON] < spawnCounts[curWave - 1][CANNON]) {
			cSpawnTimer = 0;
			CannoneerAdd(cPool);
			++curSpawnCounts[CANNON];
		}
		AI_Cannoneer(cPool, player, playerInfo);

		// Ninja
		if (ninjaSpawnTimer >= SPAWN_RATE_NINJA && curSpawnCounts[NINJA] < spawnCounts[curWave - 1][NINJA]) {
			ninjaSpawnTimer = 0;
			NinjaAdd(ninPool, player.transform.position);
			++curSpawnCounts[NINJA];
		}
		AI_Ninja(ninPool, player, playerInfo);
	}

	//all enemies in the current wave defeated
	if (!enemiesLeft) {
		++curWave;
		//If final wave 10 is cleared, playthrough is finished
		if (curWave > NUM_OF_WAVES) {
			TimePause();
			gameEnded = true;
			Finalize_HighScore(false);
			return;
		}
		enemiesLeft = spawnTotalCount[curWave - 1];
		for (int i = 0; i < NUM_OF_ENEMY_TYPES; ++i) {
			curSpawnCounts[i] = 0;
		}
	}
}

//Push enemies to one side
void Push_Enemies(SamuraiPool& samPool, ArcherPool& archPool, DIRECTION direction, float targetAxis, NinjaPool& ninPool) {
	Push_Samurai(samPool, direction, targetAxis);
	Push_Archer(archPool, direction, targetAxis);
	Push_Ninja(ninPool, direction, targetAxis);
}

void Draw_Enemies(SamuraiPool& samPool, ArcherPool& archPool, CannoneerPool& cPool, NinjaPool &ninPool) {
	Draw_Samurai(samPool);
	Draw_Archer(archPool);
	Draw_Cannoneer(cPool);
	Draw_Ninja(ninPool);

	char strBuffer[1024];
	sprintf_s(strBuffer, "Wave: %d", curWave);
	AEGfxPrint(font, strBuffer, WAVE_COUNT_TEXT_X_POS, WAVE_COUNT_TEXT_Y_POS, ENEMY_CONTROLLER_TEXT_SCALE, 0, 0, 0);
	sprintf_s(strBuffer, "Enemies Left: %d", enemiesLeft);
	AEGfxPrint(font, strBuffer, ENEMIES_LEFT_TEXT_X_POS, ENEMIES_LEFT_TEXT_Y_POS, ENEMY_CONTROLLER_TEXT_SCALE, 0, 0, 0);
}
