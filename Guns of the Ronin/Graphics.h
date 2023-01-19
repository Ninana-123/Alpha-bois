#pragma once

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "AEEngine.h"
#include "Physics.h"

struct Color {
	struct { float r, g, b, a; };

	//Values should be between 0.0f and 1.0f
	Color(float r, float g, float b, float a = 1.0f) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}

};

struct Transform
{
	AEGfxVertexList* mesh = 0;
	Vector2 position = {  };
	float rotation = 0;
	Vector2 scale = { 1 , 1 };
	AEGfxTexture* texture = 0;
	Color color{ 0,0,0,1.0f };
};



namespace {
	s8 font;
}

void G_Init();
void G_SetFontSize(int size);
void G_DrawText(char* ch, float xPos, float yPos, Color color = Color(0, 0, 0));

//Creates a rectangle mesh with width and height size
//Stores the mesh created in pMesh
AEGfxVertexList* CreateQuadMesh(float width, float height, Color color);

void DrawMesh(Transform* trans);
#endif // !GRAPHICS_H
