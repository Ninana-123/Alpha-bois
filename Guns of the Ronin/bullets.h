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

#ifndef BULLETS_H
#define BULLETS_H

#include "Graphics.h"
#include "Physics.h"
#include <iostream>


namespace {
	enum { BULLET_COUNT = 20 };
	//int PROJDAMAGE = 50;
	float BULLET_HEIGHT = 20, BULLET_WIDTH = 20;
	AEGfxVertexList* bulletMesh = 0;
	AEGfxTexture* bulletTexture = 0;
}
class Bullet {
public:
	Transform transform;
	bool enabled;
	//int dmg;
	Vector2 direction;
};

struct BulletPool {
	Bullet bullets[BULLET_COUNT];
	Bullet* activeBullets[BULLET_COUNT];
	int activeSize;
};

void BulletAdd(BulletPool& bullet,Vector2 playerPos);

void Init_BulletPool(BulletPool& bullet);

void Draw_Bullet(BulletPool& bullet);

void Bullet_AI(BulletPool& pool);

void BulletRemove(int index, BulletPool& pool);

void Free_Bullet();

#endif 