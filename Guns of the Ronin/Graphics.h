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
	AEGfxVertexList** mesh = 0;
	Vector2 position = {  };
	float rotation = 3.14159;
	Vector2 scale = { 1 , 1 };
	AEGfxTexture* texture = 0;
	Color color{ 0,0,0,1.0f };
	//TL,TR,BL,BR
	Vector2 quadPoints[4];
	float height = 0, width = 0;
};



namespace {
	s8 font;
	AEGfxTexture *asset;
	AEGfxTexture* cannonballs;
}

//void G_Init();
void G_DestroyFont();
void G_SetFontSize(int size);
void G_DrawText(char* ch, float xPos, float yPos, float scale = 1.0f, Color color = Color(0, 0, 0));
bool StaticCol_QuadQuad(Transform trans1, Transform trans2);

//Creates a rectangle mesh with its transform
void DrawMesh(Transform* trans);

void SetQuadPoints(Transform& trans, float height, float width);

void CreateQuadMesh(float width, float height, Color color, AEGfxVertexList*& mesh);

void CreateCircleMesh(float radius, Color color, AEGfxVertexList*& mesh);

void CreateSpriteMesh(Transform* trans, AEGfxVertexList*& mesh);

void DrawSprite(Transform* trans, int index);


#endif // !GRAPHICS_H

