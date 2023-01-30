#pragma once

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

