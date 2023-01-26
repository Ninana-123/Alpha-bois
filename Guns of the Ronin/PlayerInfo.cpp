#include "PlayerInfo.h"


void PlayerInfo_Init(PlayerInfo* playerinfo) {
	playerinfo->att = 1;
	playerinfo->attspd = 1;
	playerinfo->health = 10;
	playerinfo->movementspd = 1;
}

void PlayerInfo_Update(int stats) {
	stats++;
}

void PlayerInfo_Exit() {

}