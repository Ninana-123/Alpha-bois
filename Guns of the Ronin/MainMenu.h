/*
\copyright
		All content(C) 2023 DigiPen Institute of Technology Singapore.All rights
		reserved.Reproduction or disclosure of this file or its contents without the prior
		written consent of DigiPen Institute of Technology is prohibited.
*/
/*!
@file		MainMenu.h
@author		Kai Alexander Van Adrichem Boogaert
@Email		kaialexander.v@digipen.edu
@course		CSD 1451
@section	Section A
@date		14 Febuary 2023
@brief		This file contains declaration for the MainMenu page. Meshes are declared here as well as class MainMenu.
*//*______________________________________________________________________*/
#pragma once
#include <iostream>
#include "AEEngine.h"
#include "TimeManager.h"
#include "Graphics.h"
#include "Mainscene.h"
#include "GSM.h"
#include <AEGraphics.h>
#include "Sound.h"

#ifndef MAINMENU_H
#define MAINMENU_H

extern s8 font;

namespace{
	AEGfxVertexList* BGMesh = 0;
	AEGfxVertexList* playMesh = 0;
	AEGfxVertexList* guideMesh = 0;
	AEGfxVertexList* highscoreMesh = 0;
	AEGfxVertexList* quitMesh = 0;
	AEGfxVertexList* creditMesh = 0;

	AEGfxVertexList* splashScreenMesh = 0;
	AEGfxVertexList* quitPromptMesh= 0;

}

class MainMenu {
public:
	Transform transform;
	int spriteIndex = 0;
	Sprite_Animation bgAnim{ 2.f,4,1};

};

void Init_Menu();
void Update_Menu();
void Draw_Menu();
void Free_Menu();

#endif
