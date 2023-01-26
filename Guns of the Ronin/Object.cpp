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
	for (int i = 0; i < OBJECT_COUNT; i++) {
		pool.objects[i].enabled = false;
		CreateQuadMesh(20, 20, Color(0, 1, 0), pool.objects[i].transform);
		pool.activeObjects[i] = &pool.objects[i];
	}
}

//Draw active objects
void Draw_Object(ObjectPool& pool) {
	for (int i = 0; i < pool.activeSize; i++) {
		DrawMesh(&pool.activeObjects[i]->transform);
	}
}