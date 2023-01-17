#pragma once

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "AEEngine.h"

struct Transform
{
	AEGfxVertexList* mesh = 0;
	AEVec2 position = { 0 };
	float rotation = 0;
	AEVec2 scale = { 0 };
	AEGfxTexture* texture = nullptr;

};

struct Color {
	struct { float r, g, b, a; };
	
	//Values should be between 0.0f and 1.0f
	Color(float r, float g, float b, float a = 1.0f) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}

	//Color& operator=(const Color& c) {
	//	this->r -= c.r;
	//	this->g -= c.g;
	//	this->b -= c.b;
	//	this->a -= c.a;
	//	return *this;
	//}

};

namespace {
	s8 font;
}
void G_Init();
void G_SetFontSize(float size);
void G_DrawText(char* ch, float xPos, float yPos, Color color = Color(0, 0, 0));

//Creates a rectangle mesh with width and height size
//Stores the mesh created in pMesh
void CreateQuadMesh(AEGfxVertexList* pMesh, float width, float hieght);

void DrawMesh(Transform trans);
#endif // !GRAPHICS_H


