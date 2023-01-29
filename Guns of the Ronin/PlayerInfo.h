#pragma once
#include <string>
class PlayerInfo {
public:
	int health;
	int att;
	int attspd;
	int movementspd;
	bool playerDead;
	//int weaponlevel;	// kai, do check if weapon level == 0, collision, one bullet, etc.
};

void PlayerInfo_Init(PlayerInfo* playerinfo);

void PlayerInfo_Update(PlayerInfo *playerinfo, std::string name);

void PlayerInfo_Exit();