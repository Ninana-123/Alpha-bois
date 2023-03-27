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
	enum{Explosion_Count = 5};
	float EXPLOSION_HEIGHT = 100, EXPLOSION_WIDTH = 100;
	AEGfxVertexList* explosionsMesh;
	int explosionCount = 100;
}

class Explosion 
{
public:
	Transform transform;
	bool hasbeenused = false;
	bool iscolliding = false;
	bool damagedByExplosion =false;
	Transform loading;
	float timeElapsed = 0;
	float timeActive=0;
};

struct ExplosionPool 
{
public:
	Explosion Explosions[Explosion_Count];
	Explosion* activeExplosion[Explosion_Count];
	int activeSize = 0;
	
};

void Explosionpool_Init(ExplosionPool& explosionPool);
void ExplosionAdd(ExplosionPool& explosionPool);
void ExplosionDelete(int index, ExplosionPool& explosionPool);
void Explosion_Update(ExplosionPool& explosionPool, ArcherPool& archPool, CannoneerPool& canPool, NinjaPool& ninPool);
void Draw_Explosions(ExplosionPool& explosionPool);
void Free_Explosions();



#endif