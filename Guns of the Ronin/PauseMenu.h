/*
\copyright
		All content(C) 2023 DigiPen Institute of Technology Singapore.All rights
		reserved.Reproduction or disclosure of this file or its contents without the prior
		written consent of DigiPen Institute of Technology is prohibited.
*/
/*!
@file PauseMenu.h
@author Sean Ang JiaBao
@Email ang.s@digipen.edu
@course CSD 1451
@section Section A
@date 3 March 2023
@brief This file contains function declarations for the pause menu
*//*______________________________________________________________________*/

#pragma once
#include <iostream>
#include "AEEngine.h"
#include "TimeManager.h"
#include "Graphics.h"
#include "Mainscene.h"
#include "GSM.h"
#include <AEGraphics.h>
#include "PlayerInfo.h"

#ifndef PAUSEMENU_H
#define PAUSEMENU_H

namespace {
	AEGfxVertexList* pauseMesh = 0;
}

class PauseMenu {
public:
	Transform transform;
	int spriteIndex = 0;
	bool esc_pressed = false;
};

void Init_PauseMenu();
void Update_PauseMenu(PlayerInfo const& playerInfo);
void Draw_PauseMenu(PlayerInfo const& playerInfo);
void Free_PauseMenu();

#endif	// PAUSEMENU_H
