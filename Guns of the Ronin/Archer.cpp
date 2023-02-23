
#include "Archer.h"

float archerAttDelay = 2.0f;
ArrowPool arrow;

//When a archer dies 
void ArcherRemove(int index, ArcherPool& pool) {
	pool.activeArchers[index]->enabled = false;
	if (index < (pool.activeSize - 1)) {
		Archer* temp = pool.activeArchers[index];
		pool.activeArchers[index] = pool.activeArchers[pool.activeSize - 1];
		pool.activeArchers[pool.activeSize - 1] = temp;
	}
	pool.activeSize -= 1;
}

//Spawning a new archer
void ArcherAdd(ArcherPool& pool, Vector2 playerPos) {
	for (int i = 0; i < ARCHER_COUNT; i++) {
		if (pool.activeArchers[i]->enabled == false) {
			pool.activeArchers[i]->enabled = true;
			pool.activeArchers[i]->health = ARCHER_HEALTH;
			pool.activeArchers[i]->transform.position = RandomPoint_OutsideSqaure(ARCHER_MIN_SPAWNDIST, ARCHER_MAX_SPAWNDIST, playerPos);
			pool.activeSize += 1;
			break;
		}
	}
}

void Init_ArcherPool(ArcherPool& pool) {
	pool.activeSize = 0;
	CreateQuadMesh(ARCHER_WIDTH, ARCHER_HEIGHT, Color(1, 0, 0), archerMesh);
	for (int i = 0; i < ARCHER_COUNT; i++) {
		pool.archers[i].enabled = false;
		pool.archers[i].health = ARCHER_HEALTH;
		pool.archers[i].aiState = ARCHER_MOVING;
		pool.archers[i].transform.mesh = &archerMesh;
		pool.archers[i].transform.height = ARCHER_HEIGHT;
		pool.archers[i].transform.width = ARCHER_WIDTH;
		pool.activeArchers[i] = &pool.archers[i];
	}
	Init_ArrowPool(arrow);
}

void AI_Archer(ArcherPool& pool, Player& player, PlayerInfo& playerInfo) {
	Vector2 playerPos = player.transform.position;
	for (int i = 0; i < pool.activeSize; i++) {
		Archer* curArcher = pool.activeArchers[i];
		Arrow* proj = arrow.activeArrow[i];
		switch (curArcher->aiState)
		{
		case ARCHER_MOVING:
			curArcher->targetPos = playerPos;
			if (curArcher->transform.position.within_dist(playerPos, 300)) {
				curArcher->aiState = ARCHER_ATTACKING;
			}
			else {
				Vector2 direction = (curArcher->targetPos - curArcher->transform.position).normalize();
				curArcher->transform.position += direction * ARCHER_MS * deltaTime;
			}
			break;
		case ARCHER_ATTACKING:
			curArcher->timeLastAttack += deltaTime;
			if (!curArcher->transform.position.within_dist(playerPos, 300)) {
				curArcher->aiState = ARCHER_MOVING;
			}
			else {
				if (curArcher->timeLastAttack >= archerAttDelay) {
					ArrowAdd(arrow, curArcher->transform.position, playerPos);
					curArcher->timeLastAttack = 0;
				}
			}
			
			break;
		case ARCHER_BLOWNAWAY:
			Vector2 direction = (curArcher->targetPos - curArcher->transform.position).normalize();
			curArcher->transform.position += direction * ARCHER_SWEEP_MS * deltaTime;
			if (curArcher->transform.position.within_dist(curArcher->targetPos, 15.0f)) {
				curArcher->aiState = ARCHER_MOVING;
			}
			break;
		}

		proj->timeSince_lastDmgDeal += deltaTime;
		if (StaticCol_QuadQuad(proj->transform, player.transform)) {
			if (proj->timeSince_lastDmgDeal > 1.0f) {
				player_dmg(playerInfo, ARCHER_DAMAGE);
				proj->timeSince_lastDmgDeal = 0;
				//printf("collided");
			}
		}
	}
	Arrow_AI(arrow);
}

void Dmg_Archer(ArcherPool& pool, PlayerInfo playerInfo, int index) {

	if ((pool.activeArchers[index]->health -= playerInfo.att) <= 0) {
		ArcherRemove(index, pool);
	}
}


//Push Archers in the specified direction to the specific wordPos in the according axis
void Push_Archer(ArcherPool& pool, DIRECTION direction, float targetAxis) {
	for (int i = 0; i < pool.activeSize; i++) {
		pool.activeArchers[i]->aiState = ARCHER_BLOWNAWAY;
		switch (direction)
		{
		case VERTICAL:
			pool.activeArchers[i]->targetPos = Vector2(pool.activeArchers[i]->transform.position.x, targetAxis);
			break;
		case HORIZONTAL:
			pool.activeArchers[i]->targetPos = Vector2(targetAxis, pool.activeArchers[i]->transform.position.y);
			break;
		default:
			break;
		}

	}
}


void Draw_Archer(ArcherPool& pool) {
	for (int i = 0; i < pool.activeSize; i++) {
		DrawMesh(&pool.activeArchers[i]->transform);
	}
	Draw_Arrow(arrow);
}

void Free_Archer() {
	AEGfxMeshFree(archerMesh);
}