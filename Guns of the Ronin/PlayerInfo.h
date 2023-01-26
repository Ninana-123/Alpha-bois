#pragma once
class PlayerInfo {
public:
	int health;
	int att;
	int attspd;
	int movementspd;
};

void PlayerInfo_Init(PlayerInfo* playerinfo);

void PlayerInfo_Update(int stats);

void PlayerInfo_Exit();