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
	#define SHRINE_HEIGHT  50
	#define SHRINE_WIDTH  50
	#define LOADING_WIDTH  150
	#define LOADING_HEIGHT  10
	#define PUSH_BY  -500
	AEGfxVertexList* shrineMesh;
	AEGfxVertexList* shrineBoundary;
	AEGfxVertexList* loadingBarMesh;
	NinjaPool ninPools;
	ArcherPool archPools;
	PlayerInfo playerInfos;
	ExplosionPool exPools;
}

class Shrine
{
public:
	Transform transform;
	Transform loading;
	bool hasBeenUsed = false;
	bool isColliding = false;
	float loadingBarPercentage = 0;
	float timeElapsed = 0;
	float deleteTimer =5.0;
	enum Types { Explosion,Freeze, Push,God,Heal, Void, TotalShrines };
	Types types ;
	
};



struct ShrinePool 
{
public:
	Shrine Shrines[Shrine_Count];
	Shrine* activeShrine[Shrine_Count];
	int activeSize = 0;
	
	
};

void Shrine_PoolInit(ShrinePool& shrinePool);
void Shrine_Add(ShrinePool& shrinePool);
void Shrine_Delete(int index, ShrinePool& shrinePool);
void Shrine_Update(ShrinePool& shrinePool, SamuraiPool& samPool, ArcherPool &archPool,
NinjaPool &ninPool, Player& player, PlayerInfo& playerInfo, ExplosionPool& explosionPool, VoidPool& voidPool, CannoneerPool& canPool);
void Draw_Shrine(ShrinePool& shrinePool);
void Free_Shrines();



#endif