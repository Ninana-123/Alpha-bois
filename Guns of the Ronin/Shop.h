#pragma once
#include "PlayerInfo.h"

class Shop {
public:
	Transform base;
	Transform att;
	Transform attspd;
	Transform health;
	bool b_Pressed;
};

void Shop_Init(Shop* shop);
void Draw_Shop(Shop* shop, PlayerInfo *playerinfo);
void Shop_Update(Shop *shop, PlayerInfo *playerinfo);