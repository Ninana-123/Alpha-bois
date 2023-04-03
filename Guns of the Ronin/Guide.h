/*
\copyright
		All content(C) 2023 DigiPen Institute of Technology Singapore.All rights
		reserved.Reproduction or disclosure of this file or its contents without the prior
		written consent of DigiPen Institute of Technology is prohibited.
*/
/*!
@file Guide.h
@author Kai Alexander Van Adrichem Boogaert
@Email kaialexander.v@digipen.edu
@course CSD 1451
@section Section A
@date 5 Febuary 2023
@brief This file contains declaration for the guide page. Meshes are declared here as well as class Guide.
*//*______________________________________________________________________*/
#pragma once
#include <iostream>
#include "AEEngine.h"
#include "TimeManager.h"
#include "Graphics.h"
#include "Mainscene.h"
#include "GSM.h"
#include <AEGraphics.h>
#include "Player.h"
#include "Bullets.h"
#include "MainMenu.h"

#ifndef GUIDE_H
#define GUIDE_H

namespace {
	/*BACKGROUND*/
	AEGfxVertexList* GuideBGMesh = 0;
	/*SHRINES*/
	AEGfxVertexList* windMesh = 0;
	AEGfxVertexList* guideLoadingBar = 0;
	
	/*CONTROLS*/
	AEGfxVertexList* WASDMesh = 0;
	AEGfxVertexList* clickMesh = 0;


}

class Guide {
public:
	Transform transform;
	int spriteIndex = 0;
	float loadingBarPercent = 0;
	

};

void Init_Guide();
void Update_Guide();
void Draw_Guide();
void Free_Guide();

#endif