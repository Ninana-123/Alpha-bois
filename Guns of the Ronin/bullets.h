/*
\copyright
		All content(C) 2023 DigiPen Institute of Technology Singapore.All rights
		reserved.Reproduction or disclosure of this file or its contents without the prior
		written consent of DigiPen Institute of Technology is prohibited.
*/
/*!
@file Bullets.h
@author Kai Alexander Van Adrichem Boogaert
@Email kaialexander.v@digipen.edu
@course CSD 1451
@section Section A
@date 31 January 2023
@brief This file contains declaration for Bullets.cpp source file as well as defines and mesh.
*//*______________________________________________________________________*/
#pragma once

#ifndef BULLETS_H
#define BULLETS_H

#include "Graphics.h"
#include "Physics.h"
#include <iostream>


namespace {

	enum { BULLET_COUNT = 20 };
	#define BULLET_HEIGHT 20
	#define BULLET_WIDTH 20
	#define BULLET_SCALE_X 1.5f
	#define BULLET_SCALE_Y 1.5f
	#define BULLET_SPEED 500.0f
	AEGfxVertexList* bulletMesh = 0;
	AEGfxTexture* bulletTexture = 0;
}
class Bullet {
public:
	Transform transform;
	bool enabled;
	Vector2 direction;
};

struct BulletPool {
	Bullet bullets[BULLET_COUNT]{};
	Bullet* activeBullets[BULLET_COUNT]{};
	int activeSize = 0;
};

void Add_Bullet(BulletPool& bullet,Vector2 playerPos);

void Init_BulletPool(BulletPool& bullet);

void Draw_Bullet(BulletPool& bullet);

void Bullet_AI(BulletPool& pool);

void Remove_Bullet(int index, BulletPool& pool);

void Free_Bullet();

#endif 