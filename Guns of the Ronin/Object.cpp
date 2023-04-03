/*
\copyright
		All content(C) 2023 DigiPen Institute of Technology Singapore.All rights
		reserved.Reproduction or disclosure of this file or its contents without the prior
		written consent of DigiPen Institute of Technology is prohibited.
*/
/*!
@file		Object.cpp
@author		Zeng ZhiCheng
@Email		z.zhicheng@digipen.edu
@course		CSD 1451
@section	Section A
@date		23 February 2023
@brief		This file contains declaration of variables and functions that
			is used to run a bare-bone version of object pooling used across all object pools in this game
*//*______________________________________________________________________*/



#include "Object.h"

//When a object dies / destroyed / you want to hide it / etc..
void Remove_Remove(int index, ObjectPool& pool) {
	pool.activeObjects[index]->enabled = false;
	if (index < (pool.activeSize - 1)) {
		Object* temp = pool.activeObjects[index];
		pool.activeObjects[index] = pool.activeObjects[pool.activeSize - 1];
		pool.activeObjects[pool.activeSize - 1] = temp;
	}
	pool.activeSize -= 1;
}

//Spawning a new object
void Add_Object(ObjectPool& pool) {
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