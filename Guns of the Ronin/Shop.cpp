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

	shop->base.position = Vector2(0.0f, 0.0f);	
	shop->att.position = Vector2(-30.0f, 110.0f);
	shop->attspd.position = Vector2(-30.0f, 10.0f);
	shop->health.position = Vector2(-30.0f, -90.0f);
}

void Draw_Shop(Shop* shop, PlayerInfo* playerinfo) {
	shop->b_Pressed = AEInputCheckTriggered(AEVK_B);

	if (shop->b_Pressed) {
		if (checkBPressed == false) {
			checkBPressed = true;
		}
		else {
			checkBPressed = false;
			TimeResume();
		}

	}

	if (checkBPressed == true) {
		TimePause();
		DrawMesh(&shop->base);
		DrawMesh(&shop->att);
		DrawMesh(&shop->attspd);
		DrawMesh(&shop->health);

		//// Shop
		//char testCh[] = "GUNS OF RONIN";
		//G_DrawText(testCh, -210.0f, 200.0f, 0.5, Color(1, 1, 1, 1));

		//// Resume
		//char resumeButton[] = "Resume";
		//G_DrawText(resumeButton, -85.0f, 100.0f, 0.3, Color(1, 1, 1, 1));

		//// Restart
		//char restartButton[] = "Restart";
		//G_DrawText(restartButton, -80.0f, 0.0f, 0.3, Color(1, 1, 1, 1));

		//// Main Menu
		//char attspd1[] = "Main Menu";
		//G_DrawText(attspd1, -105.0f, -100.0f, 0.3, Color(1, 1, 1, 1));
	}
}
void Shop_Update(Shop* shop, PlayerInfo* playerinfo) {

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
			if (*x >= 1100 && *x <= 1300) {
				if (*y >= 300 && *y <= 400) {
					std::string name = "health";
					PlayerInfo_Update(playerinfo, name);
				}
			}
		}
		
	}
}

void Shop_Exit() {
	
}

void Free_Shop() {
	AEGfxMeshFree(shopMesh);
	AEGfxMeshFree(iconMesh);
}