
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
		pool.samurais[i].enabled = false;
		pool.samurais[i].health = HEALTH;
		pool.samurais[i].hitAnimTimer = 0;
		pool.samurais[i].aiState = MOVING;
		CreateQuadMesh(20, 20, Color(0, 1, 0), pool.samurais[i].transform);
		pool.activeSamurais[i] = &pool.samurais[i];
	}
}

void AI_Samurai(SamuraiPool& pool, Vector2 playerPos) {
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
			curSamurai->transform.position += direction * MAX_MS * deltaTime;
			if (curSamurai->transform.position.within_dist(curSamurai->targetPos, 1.0f)) {
				curSamurai->aiState = MOVING;
			}
			break;
		}
	}
}

void Dmg_Samurai(SamuraiPool& pool, int dmg, int index) {
	pool.activeSamurais[index]->health -= dmg;
	if ((pool.activeSamurais[index]->health -= dmg) <= 0) {
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
			pool.activeSamurais[i]->targetPos.y = targetAxis;
			break;
		case HORIZONTAL:
			pool.activeSamurais[i]->targetPos.x = targetAxis;
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