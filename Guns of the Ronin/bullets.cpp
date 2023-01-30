#include "bullets.h"
#include "Player.h"
#include "TimeManager.h"

s32 mouseX, mouseY;
float halfX, halfY;
float boundaryX, boundaryY;

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

	std::cout << mouseX << "," << mouseY << std::endl;
	for (int i = 0; i < BULLET_COUNT; i++) {
		if (pool.activeBullets[i]->enabled == false) {
			pool.activeBullets[i]->enabled = true;
			pool.activeBullets[i]->dmg = PROJDAMAGE;
			pool.activeBullets[i]->transform.position = playerPos;
			
			//std::cout << playerPos.x << "," << playerPos.y<< std::endl;
			pool.activeBullets[i]->direction =  (Vector2(mouseX >= halfX ? mouseX - halfX : -(halfX - mouseX),mouseY >= halfY ? -(mouseY - halfY) :halfY - mouseY) - playerPos).normalize();
			pool.activeSize += 1; 
			break;
		}
	}
}

//Init Bullet pool
void Init_BulletPool(BulletPool& pool) {
	pool.activeSize = 0;
	halfX = AEGetWindowWidth() / 2.0f;
	halfY = AEGetWindowHeight() / 2.0f;
	boundaryX = halfX + 100;
	boundaryY = halfY + 100;
	for (int i = 0; i < BULLET_COUNT; i++) {
		pool.bullets[i].enabled = false;
		pool.bullets[i].dmg = PROJDAMAGE;
		CreateQuadMesh(20, 20, Color(0, 0, 0), pool.bullets[i].transform);
		pool.activeBullets[i] = &pool.bullets[i];
	}
}

//Draw active Bullets
void Draw_Bullet(BulletPool& pool) {
	for (int i = 0; i < pool.activeSize; i++) {
		DrawMesh(&pool.activeBullets[i]->transform);
	}
}

void Bullet_AI(BulletPool& pool) {
	for (int i = 0; i < pool.activeSize; i++) {
		pool.activeBullets[i]->transform.position += pool.activeBullets[i]->direction * deltaTime * 300.0f;
		if (pool.activeBullets[i]->transform.position.x > boundaryX) {
			BulletRemove(i, pool);
		}
		else if (pool.activeBullets[i]->transform.position.x < -boundaryX) {
			BulletRemove(i, pool);
		}
		else if (pool.activeBullets[i]->transform.position.y > boundaryY) {
			BulletRemove(i, pool);
		}
		else if (pool.activeBullets[i]->transform.position.y < -boundaryY) {
			BulletRemove(i, pool);
		}
	}
}

