#pragma once

#ifndef Shrine_H
#define Shrine_H

#include "Graphics.h"
#include "Physics.h"
#include "Player.h"

namespace
{
	enum{Shrine_Count = 5};
}

class Shrine 
{
public:
	Transform transform;
	bool hasbeenused;
	bool iscolliding;
	float loadingbarpercentage;
	Transform loading;
	float timeElapsed;
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




#endif