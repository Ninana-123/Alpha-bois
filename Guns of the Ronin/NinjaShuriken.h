#pragma once

#ifndef NINJASHURIKEN_H
#define NINJASHURIKEN_H

#include "Graphics.h"
#include "Physics.h"
#include <iostream>


namespace {
	enum { SHURIKEN_COUNT = 100 };
	//int PROJDAMAGE = 50;
	float SHURIKEN_HEIGHT = 20, SHURIKEN_WIDTH = 20;
	AEGfxVertexList* shurikenMesh = 0;
	AEGfxTexture* shurikenTexture = 0;
}
class Shuriken {
public:
	Transform transform;
	bool enabled = false;
	//int dmg;
	Vector2 direction;
	float timeSince_lastDmgDeal = 0;
};

struct ShurikenPool {
	Shuriken shuriken[SHURIKEN_COUNT];
	Shuriken* activeShuriken[SHURIKEN_COUNT];
	int activeSize;
};

void ShurikenAdd(ShurikenPool& shuriken, Vector2 ninPos, Vector2 playerPos);

void Init_ShurikenPool(ShurikenPool& shuriken);

void Draw_Shuriken(ShurikenPool& shuriken);

void Shuriken_AI(ShurikenPool& shuriken);

void ShurikenRemove(int index, ShurikenPool& shuriken);

void Free_Shuriken();

#endif // 