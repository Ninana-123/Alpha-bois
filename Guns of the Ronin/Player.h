#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include "Graphics.h"
#include "Physics.h"
#include "bullets.h"
#include "PlayerInfo.h"

class Player {
public:
	Transform transform;
	bool w_Pressed, a_Pressed, s_Pressed, d_Pressed, left_mouse_pressed;
	float moveSpeed = 50.0f;

};

void Player_Init(Player* Player,BulletPool &bulletPool);
void Player_Update(Player* Player, BulletPool& bulletPool);
void Draw_Player(Player* player, BulletPool& bulletPool);




#endif