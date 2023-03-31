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
	float PLAYER_WIDTH = 90, PLAYER_HEIGHT = 90;
	float PLAYER_FIRERATE = 0.2f;
}

class Player {
public:
	Transform transform;
	bool w_Pressed, a_Pressed, s_Pressed, d_Pressed, left_mouse_pressed;
	bool walkingAudio = false;
	float moveSpeed = 45.0f;
	Sprite_Animation animation{ 2.f,5,1 };
};



void Player_Init(Player* player,BulletPool &bulletPool);
void Player_Update(Player* player, BulletPool& bulletPool);
void Draw_Player(Player* player, BulletPool& bulletPool);

void player_dmg(PlayerInfo& info, int dmg);
void Heal_player(PlayerInfo& info);


void Free_Player();

#endif