#pragma once
#include <iostream>
#include "AEEngine.h"
#include "TimeManager.h"
#include "Graphics.h"
#include "Mainscene.h"
#include "GSM.h"
#include <AEGraphics.h>

#ifndef PAUSEMENU_H
#define PAUSEMENU_H

namespace {
	AEGfxVertexList* BGMesh = 0;
	AEGfxVertexList* resumeMesh = 0;
	AEGfxVertexList* restartMesh = 0;
	AEGfxVertexList* mainmenuMesh = 0;

}

class PauseMenu {
public:
	Transform transform;
	int spriteIndex = 0;
	bool c_pressed = false;
};

void Init_PauseMenu();
void Update_PauseMenu();
void Draw_PauseMenu();
void Free_PauseMenu();

#endif
