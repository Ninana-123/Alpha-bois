#pragma once

#ifndef VOID_H
#define VOID_H

#include "Graphics.h"
#include "Physics.h"
#include "Player.h"
#include "Samurai.h"
#include "Archer.h"
#include "Cannoneer.h"
#include "Archer.h"

namespace
{
	enum{Void_Count = 5};
	float VOID_HEIGHT = 100, VOID_WIDTH = 100;
	AEGfxVertexList* voidMesh;
	AEGfxTexture* assetblackhole=0;
	int voidCount = 100;

}

class Void
{
public:
	Transform transform;
	bool hasbeenused = false;
	bool iscolliding = false;
	bool damagedByExplosion =false;
	Transform loading;
	float timeElapsed = 0;
};

struct VoidPool 
{
public:
	Void Voids[Void_Count];
	Void* activeVoid[Void_Count];
	int activeSize;
	
};

void Voidpool_Init(VoidPool& voidPool);
void VoidAdd(VoidPool& voidPool);
void VoidDelete(int index, VoidPool& voidPool);
void Void_Update(VoidPool& voidPool, SamuraiPool& samPool, ArcherPool& archPool, CannoneerPool& canPool);
void Draw_Void(VoidPool& voidPool);
void Free_Void();



#endif