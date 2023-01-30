
//#include "Shop.h"
#include "PlayerInfo.h"
#include "TimeManager.h"
#include "Physics.h"
#include "Abilities.h"
#include "Player.h"

s32 mse_x;
s32 mse_y;
float dashX, dashY;

void Abilities_Init(PlayerInfo *playerinfo) {
	dashX = AEGetWindowWidth() / 2.0f;
	dashY = AEGetWindowHeight() / 2.0f;
}

void Draw_Abilities(PlayerInfo *playerinfo) {
	
}

void Abilities_Update(Player* player, PlayerInfo* playerinfo, Vector2 playerPos, Abilities *ability) {
	Vector2 newPos{ };
	Vector2 vel{ };
	Vector2 acc{ };
	if (!IsTime_Paused()) {
		if (AEInputCheckTriggered(AEVK_E)) {
			// For future reference
			// If ability == dash, if ability == heal, etc...
			AEInputGetCursorPosition(&mse_x, &mse_y);
			std::cout << mse_x << ',' << mse_y << std::endl;
			newPos.x = mse_x;
			newPos.y = mse_y;
			
			player->transform.position = (Vector2(mse_x >= dashX ? mse_x - dashX : -(dashX - mse_x), mse_y >= dashY ? -(mse_y - dashY) : dashY - mse_y));
			player->transform.position += ability->direction * deltaTime;
			std::cout << "dash" << std::endl;
			
		}
	}
}

void Abilities_Exit() {

}
