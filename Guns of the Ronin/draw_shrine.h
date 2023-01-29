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

};

struct ShrinePool 
{
public:
	Shrine Shrines[Shrine_Count];
	Shrine* activeShrine[Shrine_Count];
	int activeSize;
	
	

};

void Shrinepool_Init(ShrinePool&pool);
void Shrine_Update(ShrinePool* Shrines, Player* Player);
void Draw_Shrine(ShrinePool* Shrines, Shrine*loading);




#endif