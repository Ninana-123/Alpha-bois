#include "Object.h"

//When a object dies / destroyed / you want to hide it / etc..
void ObjectRemove(int index, ObjectPool& pool) {
	pool.activeObjects[index]->enabled = false;
	if (index < (pool.activeSize - 1)) {
		Object* temp = pool.activeObjects[index];
		pool.activeObjects[index] = pool.activeObjects[pool.activeSize - 1];
		pool.activeObjects[pool.activeSize - 1] = temp;
	}
	pool.activeSize -= 1;
}

//Spawning a new object
void ObjectAdd(ObjectPool& pool) {
	for (int i = 0; i < OBJECT_COUNT; i++) {
		if (pool.activeObjects[i]->enabled == false) {
			pool.activeObjects[i]->enabled = true;
			pool.activeSize += 1;
			break;
		}
	}
}

//Init object pool
void Init_ObjectPool(ObjectPool& pool) {
	pool.activeSize = 0;
	Create_QuadMesh(OBJECT_WIDTH, OBJECT_HEIGHT, Color(0, 1, 0), objectMesh);
	for (int i = 0; i < OBJECT_COUNT; i++) {
		pool.objects[i].enabled = false;
		pool.objects[i].transform.mesh = &objectMesh;
		pool.objects[i].transform.height = OBJECT_HEIGHT;
		pool.objects[i].transform.width = OBJECT_WIDTH;
		pool.activeObjects[i] = &pool.objects[i];
	}
}

//Draw active objects
void Draw_Object(ObjectPool& pool) {
	for (int i = 0; i < pool.activeSize; i++) {
		Draw_Mesh(&pool.activeObjects[i]->transform);
	}
}