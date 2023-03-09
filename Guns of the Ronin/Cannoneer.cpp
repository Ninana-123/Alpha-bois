
#include "Cannoneer.h"
#include "TimeManager.h"


//When a cannoneer dies 
void CannoneerRemove(int index, CannoneerPool& pool) {
	pool.activeCannoneers[index]->enabled = false;
	if (index < (pool.activeSize - 1)) {
		Cannoneer* temp = pool.activeCannoneers[index];
		pool.activeCannoneers[index] = pool.activeCannoneers[pool.activeSize - 1];
		pool.activeCannoneers[pool.activeSize - 1] = temp;
	}
	pool.activeSize -= 1;
}

//Spawning a new cannoneer
void CannoneerAdd(CannoneerPool& pool, Vector2 playerPos) {
	for (int i = 0; i < CANNONEER_COUNT; i++) {
		if (pool.activeCannoneers[i]->enabled == false) {
			pool.activeCannoneers[i]->enabled = true;
			pool.activeCannoneers[i]->health = C_HEALTH;
			pool.activeCannoneers[i]->transform.texture = &cannoneerTexture;
			pool.activeCannoneers[i]->transform.scale = { 3, 3 };
			pool.activeCannoneers[i]->transform.position = RandomPoint_OutsideSqaure(C_MIN_SPAWNDIST, C_MAX_SPAWNDIST, playerPos);
			pool.activeSize += 1;
			break;
		}
	}
}

void Init_CannoneerPool(CannoneerPool& pool) {
	pool.activeSize = 0;
	pool.activeCBSize = 0;
	CreateQuadMesh(C_WIDTH, C_HEIGHT, Color(0, 0, 1), cannoneerMesh);
	CreateQuadMesh(CB_WIDTH, CB_HEIGHT, Color(0, 0, 0), cannonBallMesh);
	CreateCircleMesh(CB_EXPLOSION_RADIUS, Color(1, 0.1f, 0.1f), explosionMesh);
	for (int i = 0; i < CANNONEER_COUNT; i++) {
		pool.cannoneers[i].enabled = false;
		pool.cannoneers[i].health = C_HEALTH;
		pool.cannoneers[i].aiState = C_RELOADING;
		pool.cannoneers[i].transform.mesh = &cannoneerMesh;
		pool.cannoneers[i].transform.height = C_HEIGHT;
		pool.cannoneers[i].transform.width = C_WIDTH;
		pool.cannoneers[i].timeSinceFired = 2.0f;
		pool.activeCannoneers[i] = &pool.cannoneers[i];
	}
	for (int i = 0; i < CANNONBALL_COUNT; ++i) {
		pool.cannonBalls[i].transform.mesh = &cannonBallMesh;
		pool.cannonBalls[i].transform.height = CB_HEIGHT;
		pool.cannonBalls[i].transform.width = CB_WIDTH;
		pool.cannonBalls[i].exploded = false;
	}
	cannoneerTexture = AEGfxTextureLoad("Assets/Cannon1.PNG");
	cannonBallTexture = AEGfxTextureLoad("Assets/CannonBall.PNG");
}

void AI_Cannoneer(CannoneerPool& pool, Player& player, PlayerInfo& playerInfo) {
	Vector2 playerPos = player.transform.position;
	for (int i = 0; i < pool.activeSize; i++) {
		Cannoneer* curCannoneer = pool.activeCannoneers[i];

		switch (curCannoneer->aiState)
		{
		case C_RELOADING:
			curCannoneer->timeSinceFired += deltaTime;
			if (curCannoneer->timeSinceFired >= C_FIRERATE) {
				curCannoneer->aiState = C_ATTACKING;
				curCannoneer->timeSinceFired = 0;
			}
			break;
		case C_ATTACKING:
			pool.cannonBalls[pool.activeCBSize].direction = (player.transform.position - curCannoneer->transform.position).normalize();
			pool.cannonBalls[pool.activeCBSize].LZ = player.transform.position;
			pool.cannonBalls[pool.activeCBSize].transform.mesh = &cannonBallMesh;
			pool.cannonBalls[pool.activeCBSize].transform.position = curCannoneer->transform.position;
			pool.cannonBalls[pool.activeCBSize].explosionTimer = 0;
			pool.cannonBalls[pool.activeCBSize].exploded = false;
			pool.cannonBalls[pool.activeCBSize].distTravelled = 0;
			pool.cannonBalls[pool.activeCBSize].halfTotalDist = (player.transform.position - curCannoneer->transform.position).magnitude() / 2.0f;
			pool.cannonBalls[pool.activeCBSize].reachedMaxScale = false;
			pool.cannonBalls[pool.activeCBSize].transform.color.a = 1.0f;
			pool.cannonBalls[pool.activeCBSize].transform.texture = &cannonBallTexture;
			pool.cannonBalls[pool.activeCBSize].transform.scale = { 2,2 };
			pool.activeCBSize += 1;
			curCannoneer->aiState = C_RELOADING;
			break;
		}
	}

	for (int i = 0; i < pool.activeCBSize; ++i) {
		CannonBall& curCB = pool.cannonBalls[i];

		if (curCB.exploded) {
			curCB.transform.mesh = &explosionMesh;
			curCB.transform.texture = 0;
			curCB.explosionTimer += deltaTime;
			if (curCB.explosionTimer >= CB_EXPLOSION_DURATION) {
				curCB = pool.cannonBalls[pool.activeCBSize - 1];
				pool.activeCBSize -= 1;
				--i; //Replaced curCB with the last active one in the array so reduce i to recheck curCB
			}
			curCB.transform.color.a = 1.0f - curCB.explosionTimer / CB_EXPLOSION_DURATION;
		}
		else {
			if (curCB.transform.position.within_dist(curCB.LZ, 3.0f)) {
				curCB.exploded = true;
				continue;
			}

			curCB.transform.position += curCB.direction * deltaTime * CB_MS;
			curCB.distTravelled += (curCB.direction * deltaTime * CB_MS).magnitude();
			float scale = 1.0f + (curCB.reachedMaxScale ? 1.0f - curCB.distTravelled / curCB.halfTotalDist : curCB.distTravelled / curCB.halfTotalDist) * (CB_MAXSCALE - 1.0f);
			if (scale >= CB_MAXSCALE) {
				curCB.reachedMaxScale = true;
				curCB.distTravelled = 0;
			}
			curCB.transform.scale = Vector2(scale, scale);
		}

	}
}


void Dmg_Cannoneer(CannoneerPool& pool, PlayerInfo playerInfo, int index) {

	if ((pool.activeCannoneers[index]->health -= playerInfo.att) <= 0) {
		CannoneerRemove(index, pool);
	}
}



void Draw_Cannoneer(CannoneerPool& pool) {
	for (int i = 0; i < pool.activeSize; i++) {
		DrawMesh(&pool.activeCannoneers[i]->transform);
	}
	for (int i = 0; i < pool.activeCBSize; ++i) {
		DrawMesh(&pool.cannonBalls[i].transform);
	}
}

void Free_Cannoneer() {
	AEGfxMeshFree(cannoneerMesh);
	AEGfxMeshFree(cannonBallMesh);
	AEGfxMeshFree(explosionMesh);
	AEGfxTextureUnload(cannoneerTexture);
	AEGfxTextureUnload(cannonBallTexture);

}