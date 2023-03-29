#pragma once

#ifndef SMOKE_H
#define SMOKE_H

#include "Graphics.h"
#include "Physics.h"
#include <iostream>

namespace {
	enum { SMOKE_COUNT = 100 };
	float SMOKE_HEIGHT = 20, SMOKE_WIDTH = 20;
	AEGfxVertexList* smokeMesh = 0;
	AEGfxTexture* smokeTexture = 0;
}
class Smoke {
public:
	Transform transform;
	bool enabled = false;
	Vector2 direction;
	float smokeTimer = 0.f;
	int spriteIndex = 0;
};

struct SmokePool {
	Smoke smoke[SMOKE_COUNT];
	Smoke* activeSmoke[SMOKE_COUNT];
	int activeSize;
	
};

void SmokeAdd(SmokePool& smoke, Vector2 ninPos);

void Init_SmokePool(SmokePool& smoke);

void Smoke_AI(SmokePool& smoke);

void Draw_Smoke(SmokePool& smoke);

void SmokeRemove(int index, SmokePool& smoke);

void Free_Smoke();

#endif // 