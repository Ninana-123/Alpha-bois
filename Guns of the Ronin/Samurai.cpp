
#include "Samurai.h"
#include "TimeManager.h"


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
		if (pool.activeSamurais[i]->enabled == false) {
			pool.activeSamurais[i]->enabled = true;
			pool.activeSamurais[i]->health = HEALTH;
			pool.activeSamurais[i]->transform.texture = asset;
			pool.activeSamurais[i]->transform.scale = { 5, 5 };
			pool.activeSamurais[i]->transform.position = RandomPoint_OutsideSqaure(MIN_SPAWNDIST, MAX_SPAWNDIST, playerPos);
			pool.activeSize += 1;
			break;
		}
	}
}

void Init_SamuraiPool(SamuraiPool& pool) {
	pool.activeSize = 0;
	CreateQuadMesh(SAMURAI_WIDTH, SAMURAI_HEIGHT, Color(0, 1, 0), samuraiMesh);
	for (int i = 0; i < SAMURAI_COUNT; i++) {
		pool.samurais[i].enabled = false;
		pool.samurais[i].health = HEALTH;
		pool.samurais[i].aiState = MOVING;
		pool.samurais[i].transform.mesh = &samuraiMesh;
		pool.samurais[i].transform.height = SAMURAI_HEIGHT;
		pool.samurais[i].transform.width = SAMURAI_WIDTH;
		pool.activeSamurais[i] = &pool.samurais[i];
	}
	asset = AEGfxTextureLoad("Assets/Samurai1.png");
}

void AI_Samurai(SamuraiPool& pool, Player& player, PlayerInfo& playerInfo) {
	if (!IsTime_Paused_Enemy()) {
		Vector2 playerPos = player.transform.position;
		for (int i = 0; i < pool.activeSize; i++) {
			Samurai* curSamurai = pool.activeSamurais[i];

			switch (curSamurai->aiState)
			{
			case MOVING:
				curSamurai->targetPos = playerPos;
				if (curSamurai->transform.position.within_dist(playerPos, 20)) {
					curSamurai->aiState = ATTACKING;
				}
				else {
					Vector2 direction = (curSamurai->targetPos - curSamurai->transform.position).normalize();
					curSamurai->transform.position += direction * MS * deltaTime;
					//curSamurai->transform.rotation = acosf(direction.x);
				}
				break;
			case ATTACKING:
				if (!curSamurai->transform.position.within_dist(playerPos, 35)) {
					curSamurai->aiState = MOVING;
				}
				break;
			case BLOWNAWAY:
				Vector2 direction = (curSamurai->targetPos - curSamurai->transform.position).normalize();
				curSamurai->transform.position += direction * SWEEP_MS * deltaTime;
				if (curSamurai->transform.position.within_dist(curSamurai->targetPos, 15.0f)) {
					curSamurai->aiState = MOVING;
				}
				break;
			}

			curSamurai->timeSince_lastDmgDeal += deltaTime;
			if (StaticCol_QuadQuad(curSamurai->transform, player.transform)) {
				if (curSamurai->timeSince_lastDmgDeal > 0.5f) {
					player_dmg(playerInfo, DAMAGE);
					curSamurai->timeSince_lastDmgDeal = 0;
				}
			}
		}
	}
}

void Dmg_Samurai(SamuraiPool& pool, PlayerInfo playerInfo, int index) {

	if ((pool.activeSamurais[index]->health -=playerInfo.att) <= 0) {
		SamuraiRemove(index, pool);
	}
}


//Push Samurais in the specified direction to the specific wordPos in the according axis
void Push_Samurai(SamuraiPool& pool, DIRECTION direction, float targetAxis) {
	for (int i = 0; i < pool.activeSize; i++) {
		pool.activeSamurais[i]->aiState = BLOWNAWAY;
		switch (direction)
		{
		case VERTICAL:
			pool.activeSamurais[i]->targetPos = Vector2(pool.activeSamurais[i]->transform.position.x, targetAxis);
			break;
		case HORIZONTAL:
			pool.activeSamurais[i]->targetPos = Vector2(targetAxis, pool.activeSamurais[i]->transform.position.y);
			break;
		default:
			break;
		}

	}
}


void Draw_Samurai(SamuraiPool& pool) {
	for (int i = 0; i < pool.activeSize; i++) {
		DrawMesh(&pool.activeSamurais[i]->transform);
	}
}

void Free_Samurai() {
	AEGfxMeshFree(samuraiMesh);
}