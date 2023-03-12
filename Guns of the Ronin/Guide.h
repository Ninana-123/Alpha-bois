#pragma once
#include <iostream>
#include "AEEngine.h"
#include "TimeManager.h"
#include "Graphics.h"
#include "Mainscene.h"
#include "GSM.h"
#include <AEGraphics.h>

#ifndef GUIDE_H
#define GUIDE_H

namespace {
	AEGfxVertexList* GuideBGMesh = 0;
	AEGfxVertexList* playerMesh = 0;
}

class Guide {
public:
	Transform transform;
	int spriteIndex = 0;

};

void Init_Guide();
void Update_Guide();
void Draw_Guide();
void Free_Guide();

#endif