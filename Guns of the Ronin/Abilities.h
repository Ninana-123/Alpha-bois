
#pragma once
#ifndef ABILITIES_H
#define ABILITIES_H

#include "Graphics.h"
#include "Physics.h"
#include "PlayerInfo.h"
#include <iostream>
#include "Player.h"

class Abilities {
public:
	Vector2 direction;
	
};

void Abilities_Init(PlayerInfo* playerinfo);

void Draw_Abilities(PlayerInfo* playerinfo);

void Abilities_Update(Player* Player, PlayerInfo* playerinfo, Vector2 playerPos, Abilities *ability);

void Abilities_Exit();


#endif 
