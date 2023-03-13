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
	AEGfxVertexList* highscoreMesh = 0;
	AEGfxVertexList* quitMesh = 0;
	//AEGfxVertexList* creditMesh = 0;

}

class MainMenu {
public:
	Transform transform;
	int spriteIndex = 0;
	Sprite_Animation sakuraAnim{ 2.f,4,1};

};

void Init_Menu();
void Update_Menu();
void Draw_Menu();
void Free_Menu();

#endif
