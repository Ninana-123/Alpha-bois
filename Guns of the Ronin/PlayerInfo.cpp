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