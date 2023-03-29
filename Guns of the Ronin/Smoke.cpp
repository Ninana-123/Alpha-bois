#include "Smoke.h"
#include "Player.h"
#include "TimeManager.h"

//When a projectile dies / destroyed / you want to hide it / etc..
void SmokeRemove(int index, SmokePool& pool) {
	pool.activeSmoke[index]->enabled = false;
	if (index < (pool.activeSize - 1)) {
		Smoke* temp = pool.activeSmoke[index];
		pool.activeSmoke[index] = pool.activeSmoke[pool.activeSize - 1];
		pool.activeSmoke[pool.activeSize - 1] = temp;
	}
	pool.activeSize -= 1;
}

//Spawning a new projectile
void SmokeAdd(SmokePool& pool, Vector2 ninPos) {

	for (int i = 0; i < SMOKE_COUNT; i++) {
		if (pool.activeSmoke[i]->enabled == false) {
			pool.activeSmoke[i]->enabled = true;
			pool.activeSmoke[i]->transform.position = ninPos;
			pool.activeSmoke[i]->transform.texture = &smokeTexture;
			pool.activeSmoke[i]->transform.scale = { 2,2 };
			pool.activeSmoke[i]->direction = { 0,0 };
			pool.activeSmoke[i]->smokeTimer = 0.f;
			pool.activeSize += 1;
			break;
		}
	}
}

//Init projectile pool
void Init_SmokePool(SmokePool& pool) {
	pool.activeSize = 0;
	CreateQuadMesh(SMOKE_WIDTH, SMOKE_HEIGHT, Color(1, 0, 1), smokeMesh);
	for (int i = 0; i < SMOKE_COUNT; i++) {
		pool.smoke[i].enabled = false;
		pool.smoke[i].transform.height = SMOKE_HEIGHT;
		pool.smoke[i].transform.width = SMOKE_WIDTH;
		pool.smoke[i].transform.mesh = &smokeMesh;
		pool.activeSmoke[i] = &pool.smoke[i];
	}
	smokeTexture = AEGfxTextureLoad("Assets/PlanetTexture.png");
}

void Smoke_AI(SmokePool& pool) {
	for (int i = 0; i < pool.activeSize; i++) {
		pool.activeSmoke[i]->smokeTimer += deltaTime;
		/*
		if (pool.activeSmoke[i]->smokeTimer > 0.5f) {
			DrawStaticSprite(&pool.activeSmoke[i]->transform, 1);
		}
		if (pool.activeSmoke[i]->smokeTimer > 1.0f) {
			DrawStaticSprite(&pool.activeSmoke[i]->transform, 2);
		}
		if (pool.activeSmoke[i]->smokeTimer > 1.5f) {
			DrawStaticSprite(&pool.activeSmoke[i]->transform, 3);
		}
		*/
		if (pool.activeSmoke[i]->smokeTimer > 1.5f) {
			SmokeRemove(i, pool);
		}
	}
}

//Draw active projectile
void Draw_Smoke(SmokePool& pool) {

	for (int i = 0; i < pool.activeSize; i++) {
		DrawMesh(&pool.activeSmoke[i]->transform);
	}
	
}

// Free assets
void Free_Smoke() {
	AEGfxMeshFree(smokeMesh);

	AEGfxTextureUnload(smokeTexture);
}