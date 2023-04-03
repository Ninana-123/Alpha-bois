#pragma once

/*
\copyright
		All content(C) 2023 DigiPen Institute of Technology Singapore.All rights
		reserved.Reproduction or disclosure of this file or its contents without the prior
		written consent of DigiPen Institute of Technology is prohibited.
*/
/*!
@file		Object.h
@author		Zeng ZhiCheng
@Email		z.zhicheng@digipen.edu
@course		CSD 1451
@section	Section A
@date		23 February 2023
@brief		This file contains declaration of variables and functions that 
			is used to run a bare-bone version of object pooling used across all object pools in this game
*//*______________________________________________________________________*/

#ifndef OBJECT_H
#define OBJECT_H

#include "Graphics.h"
#include "Physics.h"


namespace {
	#define OBJECT_COUNT 5 
	AEGfxVertexList* objectMesh;
	#define OBJECT_HEIGHT 20 
	#define OBJECT_WIDTH 20
}
class Object {
public:
	Transform transform;
	bool enabled;
};

struct ObjectPool {
	Object objects[OBJECT_COUNT];
	Object* activeObjects[OBJECT_COUNT];
	int activeSize;
};

void Add_Object(ObjectPool& pool);

void Remove_Object(ObjectPool& pool);

void Init_ObjectPool(ObjectPool& pool);

void Draw_Object(ObjectPool& pool);

#endif // !OBJECT_H
