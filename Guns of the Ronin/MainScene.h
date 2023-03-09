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

#endif

