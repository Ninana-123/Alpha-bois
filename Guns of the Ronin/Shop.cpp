#include "Graphics.h"
#include "Shop.h"
#include "TimeManager.h"
#include "PlayerInfo.h"
#include <string>
#include <iostream>

bool checkBPressed = false;
s32 mouse_x;
s32 mouse_y;
s32* x = &mouse_x;
s32* y = &mouse_y;

void Shop_Init(Shop* shop) {

	CreateQuadMesh(SHOPWIDTH, SHOPHEIGHT, shopBGColor, shopMesh);
	CreateQuadMesh(ICONWIDTH, ICONHEIGHT, iconColor, iconMesh);

	shop->base.mesh = &shopMesh;
	shop->att.mesh = &iconMesh;
	shop->attspd.mesh = &iconMesh;
	shop->health.mesh = &iconMesh;

	shop->base.position = Vector2(0.f, 0.f);
	shop->att.position = Vector2(-400.f, 100.f);
	shop->attspd.position = Vector2(0.f, 100.f);
	shop->health.position = Vector2(400.f, 100.f);
}

void Draw_Shop(Shop* shop, PlayerInfo* playerinfo) {
	shop->b_Pressed = AEInputCheckTriggered(AEVK_B);

	if (shop->b_Pressed) {
		if (checkBPressed == false) {
			checkBPressed = true;
		}
		else {
			checkBPressed = false;
		}

	}

	if (checkBPressed == true) {
		TimePause();
		DrawMesh(&shop->base);
		DrawMesh(&shop->att);
		DrawMesh(&shop->attspd);
		DrawMesh(&shop->health);

		char testCh[] = "SHOP";
		G_DrawText(testCh, 0, 200, 2, Color(1, 1, 1, 1));

		// Attack
		char att[] = "ATTACK";
		G_DrawText(att, -475.f, 120.f, 1, Color(1, 1, 1, 1));

		// Attack Speed
		char att_str[20];
		int player_att = playerinfo->att;
		sprintf_s(att_str, "%d", player_att);
		G_DrawText(att_str, -475.f, 90.f, 1, Color(1, 1, 1, 1));

		char attspd1[] = "ATTACK";
		G_DrawText(attspd1, -50.f, 120.f, 1, Color(1, 1, 1, 1));
		char attspd2[] = "SPEED";
		G_DrawText(attspd2, -50.f, 90.f, 1, Color(1, 1, 1, 1));

		char attspd_str[20];
		int player_attspd = playerinfo->attspd;
		sprintf_s(attspd_str, "%d", player_attspd);
		G_DrawText(attspd_str, -50.f, 60.f, 1, Color(1, 1, 1, 1));

	}

	else {
		TimeResume();
	}
}
void Shop_Update(Shop* shop, PlayerInfo* playerinfo) {

	// if att is clicked, call the playerinfo_update function and increment the stats by 1
	// CreateQuadMesh(200.0f, 100.0f, shop->att.color, shop->att);
	// shop->att.position = Vector2(-400.f, 100.f);

	

	if (IsTime_Paused()) {
		AEInputGetCursorPosition(x, y);
		if (AEInputCheckTriggered(VK_LBUTTON)) {
			std::cout << *x << "," << *y << std::endl;	// checking mouse position on the screen
			// att
			if (*x >= 300 && *x <= 500) {
				if (*y >= 300 && *y <= 400) {
					std::string name = "att";
					PlayerInfo_Update(playerinfo, name);
				}
			}

			// attspd
			if (*x >= 700 && *x <= 900) {
				if (*y >= 300 && *y <= 400) {
					std::string name = "attspd";
					PlayerInfo_Update(playerinfo, name);
				}
			}
			// health

			// movementspd
		}
		//char att[] = "Attack: ";
		//G_DrawText(att, 0.f, 0.f, 1.0f, Color(0, 0, 0));
		
	}
}

void Shop_Exit() {
	
}

void Free_Shop() {
	AEGfxMeshFree(shopMesh);
	AEGfxMeshFree(iconMesh);
}