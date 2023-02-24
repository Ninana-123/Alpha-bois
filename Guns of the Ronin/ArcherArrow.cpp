#include "ArcherArrow.h"
#include "Player.h"
#include "TimeManager.h"


float arrowHalfX, arrowHalfY;
float arrowBoundaryX, arrowBoundaryY;

//When a projectile dies / destroyed / you want to hide it / etc..
void ArrowRemove(int index, ArrowPool& pool) {
	pool.activeArrow[index]->enabled = false;
	if (index < (pool.activeSize - 1)) {
		Arrow* temp = pool.activeArrow[index];
		pool.activeArrow[index] = pool.activeArrow[pool.activeSize - 1];
		pool.activeArrow[pool.activeSize - 1] = temp;
	}
	pool.activeSize -= 1;
}

//Spawning a new projectile
void ArrowAdd(ArrowPool& pool, Vector2 archPos, Vector2 playerPos) {

	for (int i = 0; i < ARROW_COUNT; i++) {
		if (pool.activeArrow[i]->enabled == false) {
			pool.activeArrow[i]->enabled = true;
			pool.activeArrow[i]->transform.position = archPos;
			pool.activeArrow[i]->direction = (playerPos - archPos).normalize();
			pool.activeSize += 1;
			break;
		}
	}
}

//Init projectile pool
void Init_ArrowPool(ArrowPool& pool) {
	pool.activeSize = 0;
	arrowHalfX = AEGetWindowWidth() / 2.0f;
	arrowHalfY = AEGetWindowHeight() / 2.0f;
	arrowBoundaryX = arrowHalfX + 100;
	arrowBoundaryY = arrowHalfY + 100;
	CreateQuadMesh(ARROW_WIDTH, ARROW_HEIGHT, Color(0, 0, 1), arrowMesh);
	for (int i = 0; i < ARROW_COUNT; i++) {
		pool.arrow[i].enabled = false;
		pool.arrow[i].transform.height = ARROW_HEIGHT;
		pool.arrow[i].transform.width = ARROW_WIDTH;
		pool.arrow[i].transform.mesh = &arrowMesh;
		pool.activeArrow[i] = &pool.arrow[i];
	}
}

//Draw active projectile
void Draw_Arrow(ArrowPool& pool) {
	
		for (int i = 0; i < pool.activeSize; i++) {
			DrawMesh(&pool.activeArrow[i]->transform);
		}
	
}

void Arrow_AI(ArrowPool& pool) {
	for (int i = 0; i < pool.activeSize; i++) {
		SetQuadPoints(pool.activeArrow[i]->transform, 20, 20);
		pool.activeArrow[i]->transform.position += pool.activeArrow[i]->direction * deltaTime * 200.0f;
		if (pool.activeArrow[i]->transform.position.x > arrowBoundaryX) {
			ArrowRemove(i, pool);
		}
		else if (pool.activeArrow[i]->transform.position.x < -arrowBoundaryX) {
			ArrowRemove(i, pool);
		}
		else if (pool.activeArrow[i]->transform.position.y > arrowBoundaryY) {
			ArrowRemove(i, pool);
		}
		else if (pool.activeArrow[i]->transform.position.y < -arrowBoundaryY) {
			ArrowRemove(i, pool);
		}
	}
}


void Free_Arrow() {
	AEGfxMeshFree(arrowMesh);
}