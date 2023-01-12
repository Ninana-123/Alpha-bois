#pragma once

#include "AEEngine.h"

struct Transform
{
	AEGfxVertexList* mesh = 0;
	AEVec2 position = { 0 };
	float rotation = 0;
	AEVec2 scale = { 0 };
	AEGfxTexture* texture = nullptr;

};


//Creates a rectangle mesh with width and height size
//Stores the mesh created in pMesh
void CreateRectMesh(AEGfxVertexList* pMesh, float width, float hieght);

void DrawMesh(Transform trans);