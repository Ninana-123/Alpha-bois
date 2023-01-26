#pragma once

#ifndef Shrine_H
#define Shrine_H

#include "Graphics.h"
#include "Physics.h"
#include "Player.h"

class Shrine {
public:
	Transform transform;
	bool hasbeenused;

};

void Draw_Shrine_Init(Shrine* Shrines, Shrine* loading);
void Draw_Shrine_Update(Shrine* Shrines, Player* Player, Shrine* loading);




#endif