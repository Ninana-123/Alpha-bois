/*
\copyright
		All content(C) 2023 DigiPen Institute of Technology Singapore.All rights
		reserved.Reproduction or disclosure of this file or its contents without the prior
		written consent of DigiPen Institute of Technology is prohibited.
*/
/*!
@file Player.h
@author Kai Alexander Van Adrichem Boogaert
@Email kaialexander.v@digipen.edu
@course CSD 1451
@section Section A
@date 31 January 2023
@brief This file contains declaration for Player.cpp source file as well as defines and mesh.
*//*______________________________________________________________________*/
#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include "Graphics.h"
#include "Physics.h"
#include "Bullets.h"
#include "PlayerInfo.h"
#include "Sound.h"

namespace {
	AEGfxVertexList* playerMesh;
	AEGfxTexture* playerTexture = 0;
	#define PLAYER_WIDTH 90 
	#define	PLAYER_HEIGHT 90
	#define PLAYER_FIRE_RATE 0.2f
	#define PLAYER_MAX_X_POS 780
	#define PLAYER_MAX_Y_POS 420
	#define PLAYER_SPRITE_HEIGHT 1.0f
	#define PLAYER_SPRITE_WIDTH 5.0f
	#define PLAYER_COLLIDER_X 50
	#define PLAYER_COLLIDER_Y 80
	#define PLAYER_MOVEMENT_SPEED 45.0f
	#define PLAYER_DIRECTION_SPEED 2.f

}

class Player {
public:
	Transform transform;
	bool wPressed = false;
	bool aPressed = false;
	bool sPressed = false;
	bool dPressed = false;
	bool leftMousePressed = false;
	bool walkingAudio = false;
	Sprite_Animation animation{ 2.f,5,1 };
};



void Init_Player(Player* player,BulletPool &bulletPool);
void Update_Player(Player* player, BulletPool& bulletPool);
void Draw_Player(Player* player, BulletPool& bulletPool);

void Damage_Player(PlayerInfo& info, int dmg);
void Heal_player(PlayerInfo& info);


void Free_Player();

#endif