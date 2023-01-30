#pragma once


#ifndef OBJECT_H
#define OBJECT_H

#include "Graphics.h"
#include "Physics.h"


namespace {
	enum { OBJECT_COUNT = 50 };
	AEGfxVertexList* objectMesh;
	float OBJECT_HEIGHT = 20, OBJECT_WIDTH = 20;
}
class Object {
public:
	Transform transform;
	bool enabled;
	int health;
};

struct ObjectPool {
	Object objects[OBJECT_COUNT];
	Object* activeObjects[OBJECT_COUNT];
	int activeSize;
};

void ObjectAdd(ObjectPool& pool);

void Init_ObjectPool(ObjectPool& pool);

void Draw_Object(ObjectPool& pool);

#endif // !OBJECT_H
