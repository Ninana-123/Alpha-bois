/*
\copyright
		All content(C) 2023 DigiPen Institute of Technology Singapore.All rights
		reserved.Reproduction or disclosure of this file or its contents without the prior
		written consent of DigiPen Institute of Technology is prohibited.
*/
/*!
@file		PlayerInfo.cpp
@author		Kai Alexander Van Adrichem Boogaert
@Email		kaialexander.v@digipen.edu
@course		CSD 1451
@section	Section A
@date		31 January 2023
@brief		This file contains definition for playerinfo.
			Playerinfo file was initially integrated for the Shop. However, after our product pitch
			it was reccomended to focus on our unique shrines and scrape the shop. Thus, this file
			is here.
*//*______________________________________________________________________*/
#include "PlayerInfo.h"
#include <string>
#include <iostream>


void PlayerInfo_Init(PlayerInfo* playerinfo) {
	playerinfo->att = 50;
	playerinfo->health = 100;
	playerinfo->playerDead = false;
}
