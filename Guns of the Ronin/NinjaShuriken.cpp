/*
\copyright
		All content(C) 2023 DigiPen Institute of Technology Singapore.All rights
		reserved.Reproduction or disclosure of this file or its contents without the prior
		written consent of DigiPen Institute of Technology is prohibited.
*/
/*!
@file		NinjaShuriken.cpp
@author		Sean Ang JiaBao
@Email		ang.s@digipen.edu
@course		CSD 1451
@section	Section A
@date		3 March 2023
@brief		This file contains function definitions for the ninja's projectiles (shuriken)
*//*______________________________________________________________________*/
#include "NinjaShuriken.h"
#include "Player.h"
#include "TimeManager.h"


#define SHURIKEN_HALF_X (AEGetWindowWidth() / 2.0f)
#define SHURIKEN_HALF_Y (AEGetWindowHeight() / 2.0f)
#define SHURIKEN_BOUNDARY_X (SHURIKEN_HALF_X + 100)
#define SHURIKEN_BOUNDARY_Y (SHURIKEN_HALF_Y + 100)
#define SHURIKEN_SPEED 400.f

//When a projectile dies / destroyed / you want to hide it / etc..
void ShurikenRemove(int index, ShurikenPool& pool) {
	pool.activeShuriken[index]->enabled = false;
	// Swap pointers
	if (index < (pool.activeSize - 1)) {
		Shuriken* temp = pool.activeShuriken[index];
		pool.activeShuriken[index] = pool.activeShuriken[pool.activeSize - 1];
		pool.activeShuriken[pool.activeSize - 1] = temp;
	}
	pool.activeSize -= 1;
}

//Spawning a new projectile
void ShurikenAdd(ShurikenPool& pool, Vector2 ninPos, Vector2 playerPos) {

	for (int i = 0; i < SHURIKEN_COUNT; i++) {
		if (pool.activeShuriken[i]->enabled == false) {
			pool.activeShuriken[i]->enabled = true;
			pool.activeShuriken[i]->transform.position = ninPos;
			pool.activeShuriken[i]->transform.texture = &shurikenTexture;
			//pool.activeShuriken[i]->transform.scale = { 2,2 };
			pool.activeShuriken[i]->direction = (playerPos - ninPos).normalize();
			pool.activeSize += 1;
			break;
		}
	}
}

// initialise projectile pool
void Init_ShurikenPool(ShurikenPool& pool) {
	pool.activeSize = 0;
	Create_QuadMesh(SHURIKEN_WIDTH, SHURIKEN_HEIGHT, Color(1, 0, 1), shurikenMesh);
	for (int i = 0; i < SHURIKEN_COUNT; i++) {
		pool.shuriken[i].enabled = false;
		pool.shuriken[i].transform.height = SHURIKEN_HEIGHT;
		pool.shuriken[i].transform.width = SHURIKEN_WIDTH;
		pool.shuriken[i].transform.mesh = &shurikenMesh;
		pool.activeShuriken[i] = &pool.shuriken[i];
	}
	shurikenTexture = AEGfxTextureLoad("Assets/Shuriken1.PNG");
}

//Draw active projectile
void Draw_Shuriken(ShurikenPool& pool) {

	for (int i = 0; i < pool.activeSize; i++) {
		Draw_Mesh(&pool.activeShuriken[i]->transform);
	}

}

// Remove shuriken if out of boundary
void Shuriken_AI(ShurikenPool& pool) {
	for (int i = 0; i < pool.activeSize; i++) {
		Set_QuadPoints(pool.activeShuriken[i]->transform);
		pool.activeShuriken[i]->transform.position += pool.activeShuriken[i]->direction * deltaTime * SHURIKEN_SPEED;
		if (pool.activeShuriken[i]->transform.position.x > SHURIKEN_BOUNDARY_X) {
			ShurikenRemove(i, pool);
		}
		else if (pool.activeShuriken[i]->transform.position.x < -SHURIKEN_BOUNDARY_X) {
			ShurikenRemove(i, pool);
		}
		else if (pool.activeShuriken[i]->transform.position.y > SHURIKEN_BOUNDARY_Y) {
			ShurikenRemove(i, pool);
		}
		else if (pool.activeShuriken[i]->transform.position.y < -SHURIKEN_BOUNDARY_Y) {
			ShurikenRemove(i, pool);
		}
	}
}

// Free assets
void Free_Shuriken() {
	AEGfxMeshFree(shurikenMesh);

	AEGfxTextureUnload(shurikenTexture);
}