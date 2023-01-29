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

void Shop_Init(Shop *shop) {
	shop->base.color = Color(1, 1, 1, 1);
	CreateQuadMesh(1200.0f, 700.0f, shop->base.color, shop->base);
	shop->base.position = Vector2(0.f, 0.f);

	shop->att.color = Color(0, 0, 0, 1);
	CreateQuadMesh(200.0f, 100.0f, shop->att.color, shop->att);
	shop->att.position = Vector2(-400.f, 100.f);

	shop->attspd.color = Color(0, 0, 0, 1);
	CreateQuadMesh(200.0f, 100.0f, shop->attspd.color, shop->attspd);
	shop->attspd.position = Vector2(0.f, 100.f);

	shop->health.color = Color(0, 0, 0, 1);
	CreateQuadMesh(200.0f, 100.0f, shop->health.color, shop->health);
	shop->health.position = Vector2(400.f, 100.f);
}

void Shop_Update(Shop *shop, PlayerInfo *playerinfo) {
	
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
		G_DrawText(testCh, -150, 200, 3, Color(1, 0, 0, 1));


		char att[] = "ATTACK";
		G_DrawText(att, -460.f, 90.f,2, Color(1, 0, 0, 1));
		
		// if att is clicked, call the playerinfo_update function and increment the stats by 1
		// CreateQuadMesh(200.0f, 100.0f, shop->att.color, shop->att);
		// shop->att.position = Vector2(-400.f, 100.f);
		AEInputGetCursorPosition(x, y);
		if (AEInputCheckTriggered(VK_LBUTTON)) {
			// att
			if (*x >= 300 && *x <= 500) {
				if (*y >= 300 && *y <= 400) {
					std::string name = "att";
					PlayerInfo_Update(playerinfo, name);
					std::cout << name << '\t' << playerinfo->att << '\n';
				}
			}

			// attspd

			// health

			// movementspd
		}
	}
	else {
		TimeResume();
	}
	
}

void Shop_Exit() {

}