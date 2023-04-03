/*
\copyright
		All content(C) 2023 DigiPen Institute of Technology Singapore.All rights
		reserved.Reproduction or disclosure of this file or its contents without the prior
		written consent of DigiPen Institute of Technology is prohibited.
*/
/*!
@file		explosion.h
@author		Teo Sheen Yeoh
@Email		t.sheenyeoh@digipen.edu
@course		CSD 1451
@section	Section A
@date		3 March 2023
@brief		This file contains the declaration for the explosion ability 
*//*______________________________________________________________________*/
#pragma once

#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "Graphics.h"
#include "Physics.h"
#include "Player.h"
#include "Samurai.h"
#include "Cannoneer.h"
#include "Archer.h"
#include "Ninja.h"

namespace
{
	
	#define EXPLOSION_HEIGHT  100
	#define EXPLOSION_WIDTH  100
	#define EXPLOSION_COUNT 8
	AEGfxVertexList* explosionsMesh;
	AEGfxTexture* assetExplosions = 0;
}

class Explosion 
{
public:
	Transform transform;
	bool hasBeenUsed = false;
	bool isColliding = false;
	bool damagedByExplosion =false;
	Transform loading;
	float timeElapsed = 0;
	float timeActive=0;
};

struct ExplosionPool 
{
public:
	Explosion Explosions[EXPLOSION_COUNT]{};
	Explosion* activeExplosion[EXPLOSION_COUNT]{};
	int activeSize = 0;
	
};

void Init_ExplosionPool(ExplosionPool& explosionPool);
void Add_Explosion(ExplosionPool& explosionPool);
void Delete_Explosion(int index, ExplosionPool& explosionPool);
void Update_Explosion(ExplosionPool& explosionPool, ArcherPool& archPool, CannoneerPool& canPool, NinjaPool& ninPool);
void Draw_Explosions(ExplosionPool& explosionPool);
void Free_Explosions();



#endif