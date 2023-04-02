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
@brief This file contains declarations on the void ability 
*//*______________________________________________________________________*/
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
	#define VOID_HEIGHT  100
	#define VOID_WIDTH  100
	AEGfxVertexList* voidMesh;
	AEGfxTexture* assetBlackHole=0;
	#define VOID_COUNT  100

}

class Void
{
public:
	Transform transform;
	bool hasBeenUsed = false;
	bool isColliding = false;
	bool damagedByExplosion =false;
	Transform loading;
	float timeElapsed = 0;
	Sprite_Animation bgAnim{ 30.f,4,1, Anim_Mode::ONE_TIME };
};

struct VoidPool 
{
public:
	Void Voids[Void_Count];
	Void* activeVoid[Void_Count];
	int activeSize = 0;;
	
};

void Void_PoolInit(VoidPool& voidPool);
void Void_Add(VoidPool& voidPool);
void Void_Delete(int index, VoidPool& voidPool);
void Void_Update(VoidPool& voidPool, SamuraiPool& samPool, ArcherPool& archPool, CannoneerPool& canPool);
void Draw_Void(VoidPool& voidPool);
void Free_Void();



#endif