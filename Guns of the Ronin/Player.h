#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include "Graphics.h"
#include "Physics.h"

class Player {
public:
	Transform transform;
	bool w_Pressed, a_Pressed, s_Pressed, d_Pressed;
	float moveSpeed = 50.0f ;
	
};

void Player_Init(Player* Player);
void Player_Update(Player* Player);




#endif