#include "EnemyProjectiles.h"
#include "Player.h"
#include "TimeManager.h"


float projHalfX, projHalfY;
float projBoundaryX, projBoundaryY;

//When a projectile dies / destroyed / you want to hide it / etc..
void ProjectileRemove(int index, ProjectilePool& pool) {
	pool.activeProjectile[index]->enabled = false;
	if (index < (pool.activeSize - 1)) {
		Projectile* temp = pool.activeProjectile[index];
		pool.activeProjectile[index] = pool.activeProjectile[pool.activeSize - 1];
		pool.activeProjectile[pool.activeSize - 1] = temp;
	}
	pool.activeSize -= 1;
}

//Spawning a new projectile
void ProjectileAdd(ProjectilePool& pool, Vector2 archPos, Vector2 playerPos) {

	for (int i = 0; i < PROJECTILE_COUNT; i++) {
		if (pool.activeProjectile[i]->enabled == false) {
			pool.activeProjectile[i]->enabled = true;
			pool.activeProjectile[i]->transform.position = archPos;
			pool.activeProjectile[i]->direction = playerPos.normalize();
			pool.activeSize += 1;
			break;
		}
	}
}

//Init projectile pool
void Init_ProjectilePool(ProjectilePool& pool) {
	pool.activeSize = 0;
	projHalfX = AEGetWindowWidth() / 2.0f;
	projHalfY = AEGetWindowHeight() / 2.0f;
	projBoundaryX = projHalfX + 100;
	projBoundaryY = projHalfY + 100;
	CreateQuadMesh(PROJECTILE_WIDTH, PROJECTILE_HEIGHT, Color(0, 0, 0), projectileMesh);
	for (int i = 0; i < BULLET_COUNT; i++) {
		pool.projectile[i].enabled = false;
		pool.projectile[i].transform.height = PROJECTILE_HEIGHT;
		pool.projectile[i].transform.width = PROJECTILE_WIDTH;
		pool.projectile[i].transform.mesh = &projectileMesh;
		pool.activeProjectile[i] = &pool.projectile[i];

	}
}

//Draw active projectile
void Draw_Projectile(ProjectilePool& pool) {
	for (int i = 0; i < pool.activeSize; i++) {
		DrawMesh(&pool.activeProjectile[i]->transform);
	}
}

void Projectile_AI(ProjectilePool& pool) {
	for (int i = 0; i < pool.activeSize; i++) {
		pool.activeProjectile[i]->transform.position += pool.activeProjectile[i]->direction * deltaTime * 300.0f;
		if (pool.activeProjectile[i]->transform.position.x > projBoundaryX) {
			ProjectileRemove(i, pool);
		}
		else if (pool.activeProjectile[i]->transform.position.x < -projBoundaryX) {
			ProjectileRemove(i, pool);
		}
		else if (pool.activeProjectile[i]->transform.position.y > projBoundaryY) {
			ProjectileRemove(i, pool);
		}
		else if (pool.activeProjectile[i]->transform.position.y < -projBoundaryY) {
			ProjectileRemove(i, pool);
		}
	}
}


void Free_Projectile() {
	AEGfxMeshFree(projectileMesh);
}