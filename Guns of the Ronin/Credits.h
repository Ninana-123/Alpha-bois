#pragma once
#include "Graphics.h"


namespace {
	/*          BACKGROUND        */
	AEGfxVertexList* CreditsBGMesh = 0;
}

class Credits {
public:
	Transform transform;
	bool j_pressed = false;
};

void Init_Credits();

void Update_Credits();

void Draw_Credits();

void Free_Credits();