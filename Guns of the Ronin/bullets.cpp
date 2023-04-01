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
#include "Bullets.h"
#include "Player.h"
#include "TimeManager.h"

s32 mouseX, mouseY;
float halfX, halfY;
float screenBoundaryX, screenBboundaryY;

//When a Bullet dies / destroyed / you want to hide it / etc..
void BulletRemove(int index, BulletPool& pool) {
	pool.activeBullets[index]->enabled = false;
	if (index < (pool.activeSize - 1)) {
		Bullet* temp = pool.activeBullets[index];
		pool.activeBullets[index] = pool.activeBullets[pool.activeSize - 1];
		pool.activeBullets[pool.activeSize - 1] = temp;
	}
	pool.activeSize -= 1;
}

//Spawning a new Bullet
void BulletAdd(BulletPool& pool,Vector2 playerPos ) {
	AEInputGetCursorPosition(&mouseX, &mouseY);

	for (int i = 0; i < BULLET_COUNT; i++) {
		if (pool.activeBullets[i]->enabled == false) {
			pool.activeBullets[i]->enabled = true;
			//pool.activeBullets[i]->dmg = PROJDAMAGE;
			pool.activeBullets[i]->transform.position = playerPos;			
			pool.activeBullets[i]->direction =  (Vector2(mouseX >= halfX ? mouseX - halfX : -(halfX - mouseX),mouseY >= halfY ? -(mouseY - halfY) :halfY - mouseY) - playerPos).normalize();
			pool.activeSize += 1; 
			pool.activeBullets[i]->transform.texture = &bulletTexture;
			pool.activeBullets[i]->transform.rotation = std::atan2(pool.activeBullets[i]->direction.y, pool.activeBullets[i]->direction.x);
			//pool.activeBullets[i]->transform.scale = { 1,12 };
			break;
		}
	}
}

//Init Bullet pool
void Init_BulletPool(BulletPool& pool) {
	pool.activeSize = 0;
	halfX = AEGetWindowWidth() / 2.0f;
	halfY = AEGetWindowHeight() / 2.0f;
	screenBoundaryX = halfX + 100;
	screenBboundaryY = halfY + 100;
	CreateQuadMesh(BULLET_WIDTH, BULLET_HEIGHT, Color(0, 0, 0), bulletMesh);
	for (int i = 0; i < BULLET_COUNT; i++) {
		pool.bullets[i].enabled = false;
		pool.bullets[i].transform.height = BULLET_HEIGHT;
		pool.bullets[i].transform.width = BULLET_WIDTH;
		pool.bullets[i].transform.scale = { 1.5f,1.5f };
		pool.bullets[i].transform.mesh = &bulletMesh;
		pool.bullets[i].transform.colliderSize = { BULLET_WIDTH, BULLET_HEIGHT * 0.35f };
		//pool.bullets[i].dmg = PROJDAMAGE;
		pool.activeBullets[i] = &pool.bullets[i];

	}
	bulletTexture = AEGfxTextureLoad("Assets/Bullet.png");
}

//Draw active Bullets
void Draw_Bullet(BulletPool& pool) {
	for (int i = 0; i < pool.activeSize; i++) {
		DrawMesh(&pool.activeBullets[i]->transform);
	}
}

void Bullet_AI(BulletPool& pool) {
	for (int i = 0; i < pool.activeSize; i++) {
		pool.activeBullets[i]->transform.position += pool.activeBullets[i]->direction * deltaTime * 500.0f;
		if (pool.activeBullets[i]->transform.position.x > screenBoundaryX) {
			BulletRemove(i, pool);
		}
		else if (pool.activeBullets[i]->transform.position.x < -screenBoundaryX) {
			BulletRemove(i, pool);
		}
		else if (pool.activeBullets[i]->transform.position.y > screenBboundaryY) {
			BulletRemove(i, pool);
		}
		else if (pool.activeBullets[i]->transform.position.y < -screenBboundaryY) {
			BulletRemove(i, pool);
		}
	}
}


void Free_Bullet() {
	AEGfxMeshFree(bulletMesh);
	AEGfxTextureUnload(bulletTexture);
}