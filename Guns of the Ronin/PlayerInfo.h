/*
\copyright
		All content(C) 2023 DigiPen Institute of Technology Singapore.All rights
		reserved.Reproduction or disclosure of this file or its contents without the prior
		written consent of DigiPen Institute of Technology is prohibited.
*/
/*!
@file PlayerInfo.h
@author Kai Alexander Van Adrichem Boogaert
@Email kaialexander.v@digipen.edu
@course CSD 1451
@section Section A
@date 31 January 2023
@brief This file contains declaration for playerinfo.
		Playerinfo file was initially integrated for the Shop. However, after our product pitch
		it was reccomended to focus on our unique shrines and scrape the shop. Thus, this file
		is here.
*//*______________________________________________________________________*/
#pragma once
#include <string>
class PlayerInfo {
public:
	int att;
	int health;
	bool playerDead;
};

void PlayerInfo_Init(PlayerInfo* playerinfo);