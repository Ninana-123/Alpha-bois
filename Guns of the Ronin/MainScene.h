/*
\copyright
		All content(C) 2023 DigiPen Institute of Technology Singapore.All rights
		reserved.Reproduction or disclosure of this file or its contents without the prior
		written consent of DigiPen Institute of Technology is prohibited.
*/
/*!
@file void.cpp
@author Teo Sheen Yeoh
@Email t.sheenyeoh@digipen.edu
@course CSD 1450
@section Section A
@date 3 March 2023
@brief This file contains code for the credit screen.
*//*______________________________________________________________________*/
#pragma once
#ifndef MAINSCENE_H
#define MAINSCENE_H

namespace {
	AEGfxVertexList* levelMesh = 0;
}

class Level{
public:
	Transform transform;
};

void Init_Scene();
void Update_Scene();
void Draw_Scene();
void Free_Scene();
void Set_StartingWave(int waveNum);
#endif

