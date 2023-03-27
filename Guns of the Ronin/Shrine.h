#pragma once

#ifndef Shrine_H
#define Shrine_H

#include "Graphics.h"
#include "Physics.h"
#include "Player.h"
#include "Archer.h"
#include "Samurai.h"
#include "Ninja.h"
#include "PlayerInfo.h"
#include "Explosion.h"
#include "Void.h"


namespace
{
	enum{Shrine_Count = 10};
	float SHRINE_HEIGHT = 50, SHRINE_WIDTH = 50;
	AEGfxVertexList* shrineMesh;
	AEGfxVertexList* shrineBoundary;
	AEGfxVertexList* loadingBarMesh;
	NinjaPool ninPools;
	ArcherPool archPools;
	PlayerInfo playerinfos;
	ExplosionPool exPools;
	int shrineRadius = 100;
}

class Shrine
{
public:
	Transform transform;
	Transform shrineBoundary;
	bool hasbeenused = false;
	bool iscolliding = false;
	float loadingbarpercentage = 0;
	Transform loading;
	float timeElapsed = 0;
	enum Types { Explosion,Freeze, Push,God,Heal, Void, TotalShrines };
	Types types;
	float deleteTimer =5.0;
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
void Shrine_Update(ShrinePool& shrinePool, SamuraiPool& samPool, ArcherPool archPool,
NinjaPool ninPool, Player& player, PlayerInfo& playerinfo, ExplosionPool& explosionPool,int inddex, VoidPool& voidPool, CannoneerPool& canPool);
void Draw_Shrine(ShrinePool& shrinePool);
void Free_Shrines();



#endif