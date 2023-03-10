#pragma once

#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "Graphics.h"
#include "Physics.h"
#include "Player.h"
#include "Samurai.h"

namespace
{
	enum{Explosion_Count = 5};
	float EXPLOSION_HEIGHT = 50, EXPLOSION_WIDTH = 50;
	AEGfxVertexList* explosionsMesh;
	//AEGfxVertexList* loadingBarMesh;
	int explosionCount = 100;
}

class Explosion 
{
public:
	Transform transform;
	bool hasbeenused = false;
	bool iscolliding = false;
	bool damagedByExplosion =false;
	//float loadingbarpercentage = 0;
	Transform loading;
	float timeElapsed = 0;
};

struct ExplosionPool 
{
public:
	Explosion Explosions[Explosion_Count];
	Explosion* activeExplosion[Explosion_Count];
	int activeSize;
	
};

void Explosionpool_Init(ExplosionPool& explosionPool);
void ExplosionAdd(ExplosionPool& explosionPool);
void ExplosionDelete(int index, ExplosionPool& explosionPool);
void Explosion_Update(ExplosionPool& explosionPool, SamuraiPool& pool);
void Draw_Explosions(ExplosionPool& explosionPool);
void Free_Explosions();



#endif