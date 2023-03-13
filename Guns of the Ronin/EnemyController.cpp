
#include "EnemyController.h"
#include "TimeManager.h"
#include "Player.h"

float spawnTImer = 0;
float archerSpawnTimer = 0;
float cSpawnTimer = 0;
float ninjaSpawnTimer = 0;
//s32 mousePosX;
//s32 mousePosY;
//
//s32* mouseX = &mousePosX;
//s32* mouseY = &mousePosY;

void Init_Enemies(SamuraiPool& samPool, ArcherPool &archPool, CannoneerPool& cPool, NinjaPool &ninPool) {
	Init_SamuraiPool(samPool);
	Init_ArcherPool(archPool);
	Init_CannoneerPool(cPool);
	Init_NinjaPool(ninPool);
}

void Update_Enemies(SamuraiPool& samPool, ArcherPool& archPool, CannoneerPool& cPool, NinjaPool& ninPool, Player& player, PlayerInfo& playerInfo) {
	spawnTImer += deltaTime;
	archerSpawnTimer += deltaTime;
	cSpawnTimer += deltaTime;
	ninjaSpawnTimer += deltaTime;

	if (!IsTime_Paused() && !IsTime_Paused_Enemy()) {
		// Samurai
		if (spawnTImer >= spawnRate_Samurai) {
			spawnTImer = 0;
			SamuraiAdd(samPool, player.transform.position);
		}
		AI_Samurai(samPool, player, playerInfo);

	//	// Archer
	//	if (archerSpawnTimer >= spawnRate_Archer) {
	//		archerSpawnTimer = 0;
	//		ArcherAdd(archPool, player.transform.position);
	//	}
	//	AI_Archer(archPool, player, playerInfo);


	//	// Cannoneer
	//	if (cSpawnTimer >= spawnRate_Cannoneer) {
	//		cSpawnTimer = 0;
	//		CannoneerAdd(cPool, player.transform.position);
	//	}
	//	AI_Cannoneer(cPool, player, playerInfo);

	//	// Ninja
		if (ninjaSpawnTimer >= spawnRate_Ninja) {
			ninjaSpawnTimer = 0;
			NinjaAdd(ninPool, player.transform.position);
		}
		AI_Ninja(ninPool, player, playerInfo);
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
}
