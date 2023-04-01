/*
\copyright
		All content(C) 2023 DigiPen Institute of Technology Singapore.All rights
		reserved.Reproduction or disclosure of this file or its contents without the prior
		written consent of DigiPen Institute of Technology is prohibited.
*/
/*!
@file void.cpp
@author Teo Sheen Yeoh
@Email t.sheenyeoh@digipen.edu
@course CSD 1450
@section Section A
@date 3 March 2023
@brief This file contains code for the credit screen.
*//*______________________________________________________________________*/
#include "NinjaShuriken.h"
#include "Player.h"
#include "TimeManager.h"


float shurikenHalfX, shurikenHalfY;
float shurikenBoundaryX, shurikenBoundaryY;
float shurikenSpeed = 400.f;

//When a projectile dies / destroyed / you want to hide it / etc..
void ShurikenRemove(int index, ShurikenPool& pool) {
	pool.activeShuriken[index]->enabled = false;
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

//Init projectile pool
void Init_ShurikenPool(ShurikenPool& pool) {
	pool.activeSize = 0;
	shurikenHalfX = AEGetWindowWidth() / 2.0f;
	shurikenHalfY = AEGetWindowHeight() / 2.0f;
	shurikenBoundaryX = shurikenHalfX + 100;
	shurikenBoundaryY = shurikenHalfY + 100;
	CreateQuadMesh(SHURIKEN_WIDTH, SHURIKEN_HEIGHT, Color(1, 0, 1), shurikenMesh);
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
		DrawMesh(&pool.activeShuriken[i]->transform);
	}

}

// Remove shuriken if out of boundary
void Shuriken_AI(ShurikenPool& pool) {
	for (int i = 0; i < pool.activeSize; i++) {
		SetQuadPoints(pool.activeShuriken[i]->transform);
		pool.activeShuriken[i]->transform.position += pool.activeShuriken[i]->direction * deltaTime * shurikenSpeed;
		if (pool.activeShuriken[i]->transform.position.x > shurikenBoundaryX) {
			ShurikenRemove(i, pool);
		}
		else if (pool.activeShuriken[i]->transform.position.x < -shurikenBoundaryX) {
			ShurikenRemove(i, pool);
		}
		else if (pool.activeShuriken[i]->transform.position.y > shurikenBoundaryY) {
			ShurikenRemove(i, pool);
		}
		else if (pool.activeShuriken[i]->transform.position.y < -shurikenBoundaryY) {
			ShurikenRemove(i, pool);
		}
	}
}

// Free assets
void Free_Shuriken() {
	AEGfxMeshFree(shurikenMesh);

	AEGfxTextureUnload(shurikenTexture);
}