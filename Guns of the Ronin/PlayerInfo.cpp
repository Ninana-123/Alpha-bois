#include "PlayerInfo.h"
#include <string>
#include <iostream>


void PlayerInfo_Init(PlayerInfo* playerinfo) {
	playerinfo->att = 50;	// max 100 attack?
	playerinfo->attspd = 1;	// max level 5 attack speed?
	playerinfo->health = 100;
	playerinfo->movementspd = 10;
	playerinfo->dash = 0;
	playerinfo->playerDead = false;
	//playerinfo->weaponlevel = 0;	
}

void PlayerInfo_Update(PlayerInfo *playerinfo, std::string name) {

}

void PlayerInfo_Exit() {

}