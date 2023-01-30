#include "PlayerInfo.h"
#include <string>
#include <iostream>


void PlayerInfo_Init(PlayerInfo* playerinfo) {
	playerinfo->att =50;	// max 100 attack?
	playerinfo->attspd = 1;	// max level 5 attack speed?
	playerinfo->health = 100;
	playerinfo->movementspd = 1;
	playerinfo->dash = 0;
	//playerinfo->weaponlevel = 0;	
}

void PlayerInfo_Update(PlayerInfo *playerinfo, std::string name) {

	if (name == "att") {
		if (playerinfo->att == 100) {
			std::cout << "max level 10" << '\n';
		}
		else {
			playerinfo->att *= 2;
		}
		
	}
	else if (name == "attspd"){
		playerinfo->attspd++;
	}
	else if (name == "health") {
		playerinfo->health += 10;
	}
}

void PlayerInfo_Exit() {

}