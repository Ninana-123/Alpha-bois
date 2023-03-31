/*
\copyright
		All content(C) 2023 DigiPen Institute of Technology Singapore.All rights
		reserved.Reproduction or disclosure of this file or its contents without the prior
		written consent of DigiPen Institute of Technology is prohibited.
*/
/*!
@file void.cpp
@author Teo Sheen Yeoh
@Email t.sheenyeoh@digipen.edu
@course CSD 1450
@section Section A
@date 3 March 2023
@brief This file contains code for the credit screen.
*//*______________________________________________________________________*/
#pragma once
#include <string>
class PlayerInfo {
public:
	int health;
	int att;
	int attspd;
	int movementspd;
	bool playerDead;
	int dash;
	//int weaponlevel;	// kai, do check if weapon level == 0, collision, one bullet, etc.
};

void PlayerInfo_Init(PlayerInfo* playerinfo);

void PlayerInfo_Update(PlayerInfo *playerinfo, std::string name);

void PlayerInfo_Exit();