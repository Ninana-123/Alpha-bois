#pragma once

#ifndef DUMMYPLAYER_H
#define DUMMYPLAYER_H

#include "Graphics.h"
#include "Physics.h"

class DummyPlayer {
public:
	Transform transform;
	bool w_Pressed = false, a_Pressed = false, s_Pressed = false, d_Pressed = false;
	float moveSpeed = 50.0f;

};

void DummyPlayer_Init(DummyPlayer* dummyPlayer);
void DummyPlayer_Update(DummyPlayer* dummyPlayer);



#endif // !DUMMYPLAYER_H

