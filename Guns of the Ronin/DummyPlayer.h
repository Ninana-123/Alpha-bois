#pragma once
/*
\copyright
		All content(C) 2023 DigiPen Institute of Technology Singapore.All rights
		reserved.Reproduction or disclosure of this file or its contents without the prior
		written consent of DigiPen Institute of Technology is prohibited.
*/
/*!
@file		DummyPlayer.h
@author		Zeng ZhiCheng
@Email		z.zhicheng@digipen.edu
@course		CSD 1451
@section	Section A
@date		3 February 2023
@brief		This file contains code for testing
*//*______________________________________________________________________*/



#ifndef DUMMYPLAYER_H
#define DUMMYPLAYER_H

#include "Graphics.h"
#include "Physics.h"

namespace {
	AEGfxVertexList* dummyMesh;
	float DUMMY_HEIGHT = 40, DUMMY_WIDTH = 40;
}

class DummyPlayer {
public:
	Transform transform;
	bool w_Pressed = false, a_Pressed = false, s_Pressed = false, d_Pressed = false;
	float moveSpeed = 200.0f;

};

void DummyPlayer_Init(DummyPlayer* dummyPlayer);
void DummyPlayer_Update(DummyPlayer* dummyPlayer);
void Free_Dummy();


#endif // !DUMMYPLAYER_H

