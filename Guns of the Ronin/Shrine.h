#pragma once

#ifndef Shrine_H
#define Shrine_H

#include "Graphics.h"
#include "Physics.h"
#include "Player.h"
#include "Archer.h"
#include "Samurai.h"
#include "Ninja.h"
namespace
{
	enum{Shrine_Count = 5};
	float SHRINE_HEIGHT = 50, SHRINE_WIDTH = 50;
	AEGfxVertexList* shrineMesh;
	AEGfxVertexList* loadingBarMesh;
	NinjaPool ninPools;
	ArcherPool archPools;
	SamuraiPool samPools;
	PlayerInfo playerinfos;
}

class Shrine
{
public:
	Transform transform;
	bool hasbeenused = false;
	bool iscolliding = false;
	float loadingbarpercentage = 0;
	Transform loading;
	float timeElapsed = 0;
	enum Types { Freeze, Push, Heal, TotalShrines };
	Types types;
};



struct ShrinePool 
{
public:
	Shrine Shrines[Shrine_Count];
	Shrine* activeShrine[Shrine_Count];
	int activeSize;
	
};

void Shrinepool_Init(ShrinePool& shrinePool);
void ShrineAdd(ShrinePool& shrinePool);
void ShrineDelete(int index, ShrinePool& shrinePool);
void Shrine_Update(ShrinePool& shrinePool, Player& player);
void Draw_Shrine(ShrinePool& shrinePool);
void Free_Shrines();



#endif