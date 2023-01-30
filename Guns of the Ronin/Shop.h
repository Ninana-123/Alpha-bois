#pragma once
#include "PlayerInfo.h"

namespace {
	AEGfxVertexList* iconMesh;
	float ICONHEIGHT = 100, ICONWIDTH = 200;
	AEGfxVertexList* shopMesh;
	float SHOPHEIGHT = 800, SHOPWIDTH = 1200;

	Color shopBGColor{ 1, 1, 1 };
	Color iconColor{ 1, 0, 0, 0.75f };
}

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
void Free_Shop();
