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

#endif
