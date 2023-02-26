#pragma once
#include "PlayerInfo.h"

namespace {
	AEGfxVertexList* iconMesh;
	float ICONHEIGHT = 60, ICONWIDTH = 170;
	AEGfxVertexList* shopMesh;
	float SHOPHEIGHT = 900, SHOPWIDTH = 1600;

	Color shopBGColor{ 0.0f, 0.0f, 1.0f, 1.0f };
	Color iconColor{ 1.0f, 0.0f, 0.0f, 0.75f };
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
