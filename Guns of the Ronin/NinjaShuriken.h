/*
\copyright
		All content(C) 2023 DigiPen Institute of Technology Singapore.All rights
		reserved.Reproduction or disclosure of this file or its contents without the prior
		written consent of DigiPen Institute of Technology is prohibited.
*/
/*!
@file		NinjaShuriken.h
@author		Sean Ang JiaBao
@Email		ang.s@digipen.edu
@course		CSD 1451
@section	Section A
@date		3 March 2023
@brief		This file contains function declaration for the ninja's projectiles (shuriken)
*//*______________________________________________________________________*/
#pragma once

#ifndef NINJASHURIKEN_H
#define NINJASHURIKEN_H

#include "Graphics.h"
#include "Physics.h"
#include <iostream>


namespace {
	#define SHURIKEN_COUNT 100
	#define SHURIKEN_HEIGHT 20
	#define SHURIKEN_WIDTH 20
	AEGfxVertexList* shurikenMesh = 0;
	AEGfxTexture* shurikenTexture = 0;
}
class Shuriken {
public:
	Transform transform;
	bool enabled = false;
	Vector2 direction;
	float timeSince_lastDmgDeal = 0;
};

struct ShurikenPool {
	Shuriken shuriken[SHURIKEN_COUNT]{};
	Shuriken* activeShuriken[SHURIKEN_COUNT]{};
	int activeSize =0;
};

void ShurikenAdd(ShurikenPool& shuriken, Vector2 ninPos, Vector2 playerPos);

void Init_ShurikenPool(ShurikenPool& shuriken);

void Draw_Shuriken(ShurikenPool& shuriken);

void Shuriken_AI(ShurikenPool& shuriken);

void ShurikenRemove(int index, ShurikenPool& shuriken);

void Free_Shuriken();

#endif // NINJASHURIKEN_H