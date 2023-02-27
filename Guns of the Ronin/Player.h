#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include "Graphics.h"
#include "Physics.h"
#include "bullets.h"
#include "PlayerInfo.h"

namespace {
	AEGfxVertexList* playerMesh;
	float PLAYER_WIDTH = 50, PLAYER_HEIGHT = 50;
}

class Player {
public:
	Transform transform;
	bool w_Pressed, a_Pressed, s_Pressed, d_Pressed, left_mouse_pressed;
	float moveSpeed = 50.0f;

};

void Player_Init(Player* Player,BulletPool &bulletPool);
void Player_Update(Player* Player, BulletPool& bulletPool);
void Draw_Player(Player* player, BulletPool& bulletPool);

void player_dmg(PlayerInfo& info, int dmg);
void Heal_player(PlayerInfo& info);

void Free_Player();

#endif