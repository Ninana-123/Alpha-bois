#pragma once

#ifndef ARCHERARROW_H
#define ARCHERARROW_H

#include "Graphics.h"
#include "Physics.h"
#include <iostream>


namespace {
	enum { ARROW_COUNT = 100 };
	//int PROJDAMAGE = 50;
	float ARROW_HEIGHT = 20, ARROW_WIDTH = 20;
	AEGfxVertexList* arrowMesh = 0;
}
class Arrow {
public:
	Transform transform;
	bool enabled;
	//int dmg;
	Vector2 direction;
	float timeSince_lastDmgDeal = 0;
};

struct ArrowPool {
	Arrow arrow[ARROW_COUNT];
	Arrow* activeArrow[ARROW_COUNT];
	int activeSize;
};

void ArrowAdd(ArrowPool& arrow, Vector2 archPos, Vector2 playerPos);

void Init_ArrowPool(ArrowPool& arrow);

void Draw_Arrow(ArrowPool& pool);

void Arrow_AI(ArrowPool& arrow);

void ArrowRemove(int index, ArrowPool& arrow);

void Free_Arrow();

#endif // 