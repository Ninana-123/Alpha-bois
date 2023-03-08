#pragma once
#include <iostream>
#include "AEEngine.h"
#include "TimeManager.h"
#include "Graphics.h"
#include "Mainscene.h"
#include "GSM.h"
#include <AEGraphics.h>

#ifndef MAINMENU_H
#define MAINMENU_H

namespace{
	AEGfxVertexList* BGMesh = 0;
	AEGfxVertexList* playMesh = 0;
	AEGfxVertexList* guideMesh = 0;
	AEGfxVertexList* exitMesh = 0;

}

class Menu {
public:
	Transform transform;
};

void Init_Menu();
void Update_Menu();
void Draw_Menu();
void Free_Menu();

#endif
