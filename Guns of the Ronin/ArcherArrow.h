
/*
\copyright
		All content(C) 2023 DigiPen Institute of Technology Singapore.All rights
		reserved.Reproduction or disclosure of this file or its contents without the prior
		written consent of DigiPen Institute of Technology is prohibited.
*/
/*!
@file		ArcherArrow.h
@author		Sean Ang JiaBao
@Email		ang.s@digipen.edu
@course		CSD 1451
@section	Section A
@date		3 March 2023
@brief		This file contains function declarations for the archer's projectiles (arrows)
*//*______________________________________________________________________*/
#pragma once

#ifndef ARCHERARROW_H
#define ARCHERARROW_H

#include "Graphics.h"
#include "Physics.h"
#include <iostream>


namespace {
	#define ARROW_COUNT 100
	#define ARROW_HEIGHT 20
	#define ARROW_WIDTH 20
	AEGfxVertexList* arrowMesh = 0;
	AEGfxTexture* arrowTexture = 0;
}
class Arrow {
public:
	Transform transform;
	bool enabled = false;
	Vector2 direction;
	float timeSince_lastDmgDeal = 0;
};

struct ArrowPool {
	Arrow arrow[ARROW_COUNT];
	Arrow* activeArrow[ARROW_COUNT];
	int activeSize = 0;
};

void ArrowAdd(ArrowPool& arrow, Vector2 archPos, Vector2 playerPos);

void Init_ArrowPool(ArrowPool& arrow);

void Draw_Arrow(ArrowPool& pool);

void Arrow_AI(ArrowPool& arrow);

void ArrowRemove(int index, ArrowPool& arrow);

void Free_Arrow();

#endif // ARCHERARROW_H