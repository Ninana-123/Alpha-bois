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
	int activeSize =0;
};

void ShurikenAdd(ShurikenPool& shuriken, Vector2 ninPos, Vector2 playerPos);

void Init_ShurikenPool(ShurikenPool& shuriken);

void Draw_Shuriken(ShurikenPool& shuriken);

void Shuriken_AI(ShurikenPool& shuriken);

void ShurikenRemove(int index, ShurikenPool& shuriken);

void Free_Shuriken();

#endif // 