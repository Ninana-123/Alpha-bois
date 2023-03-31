
/*
\copyright
		All content(C) 2023 DigiPen Institute of Technology Singapore.All rights
		reserved.Reproduction or disclosure of this file or its contents without the prior
		written consent of DigiPen Institute of Technology is prohibited.
*/
/*!
@file void.cpp
@author Teo Sheen Yeoh
@Email t.sheenyeoh@digipen.edu
@course CSD 1450
@section Section A
@date 3 March 2023
@brief This file contains code for the credit screen.
*//*______________________________________________________________________*/
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
	AEGfxTexture* arrowTexture = 0;
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