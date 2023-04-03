/*
\copyright
		All content(C) 2023 DigiPen Institute of Technology Singapore.All rights
		reserved.Reproduction or disclosure of this file or its contents without the prior
		written consent of DigiPen Institute of Technology is prohibited.
*/
/*!
@file		Credits.h
@author		Sean Ang JiaBao
@Email		ang.s@digipen.edu
@course		CSD 1451
@section	Section A
@date		3 March 2023
@brief		This file contains code for the credit screen.
*//*______________________________________________________________________*/

#pragma once
#include "Graphics.h"


namespace {
	/*          BACKGROUND        */
	AEGfxVertexList* CreditsBGMesh = 0;

	/*         QUIT BUTTON        */
	AEGfxVertexList* backMesh = 0;
}

class Credits {
public:
	Transform transform;
	int spriteIndex = 0;
};

void Init_Credits();

void Update_Credits();

void Draw_Credits();

void Free_Credits();