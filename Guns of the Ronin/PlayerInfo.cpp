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
	playerinfo->att = 50;
	playerinfo->health = 100;
	playerinfo->playerDead = false;
}
