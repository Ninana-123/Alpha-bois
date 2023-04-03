/*
\copyright
		All content(C) 2023 DigiPen Institute of Technology Singapore.All rights
		reserved.Reproduction or disclosure of this file or its contents without the prior
		written consent of DigiPen Institute of Technology is prohibited.
*/
/*!
@file			Graphics.h
@author			Zeng ZhiCheng
@Email			z.zhicheng@digipen.edu
@co-author		Kai Alexander Van Adrichem Boogaert
@Email			kaialexander.v@digipen.edu
@course			CSD 1451
@section		Section A
@date			2 April 2023
@brief			This file contains declaration of graphics related classes and functions 
*//*______________________________________________________________________*/
#pragma once

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "AEEngine.h"
#include "Physics.h"

struct Color {
	 float r, g, b, a;

	//Values should be between 0.0f and 1.0f
	 Color(float rIn, float gIn, float bIn, float aIn = 1.0f) : r{ rIn }, g{ gIn }, b{ bIn }, a{ aIn } { }
};

struct Transform
{
	AEGfxVertexList** mesh = 0;
	Vector2 position = {  };
	float rotation = 3.14159f;
	Vector2 scale = { 1 , 1 };
	Vector2 colliderSize{ 0, 0 };
	Vector2 colliderOffsetPos{ 0, 0 };
	AEGfxTexture** texture = 0;
	Color color{ 0,0,0,1.0f };
	//TL,TR,BL,BR
	Vector2 quadPoints[4];
	float height = 0, width = 0;
	//The texture x offset in the texture map of the current frame being drawn
	float textureOffsetX = 0;
	//The texture y offset in the texture map of the current frame being drawn
	float textureOffsetY = 0;
};


enum class Anim_Mode {
	LOOP, ONE_TIME
};

class Sprite_Animation {
public: 
	//The animation's play mode, Anim_Mode::LOOP or Anim_Mode::ONE_TIME 
	//ONE_TIME play mode requires manual calling to PlayAnim() to play animation
	Anim_Mode playMode = Anim_Mode::LOOP;

	Sprite_Animation();
	/*
		frame_Rate		-> frame rate of this sprite animation, number of frames per sec
		x_Count			-> the number of animation frames horizontally
		y_Count			-> the number of animation frames vertically 
		Eg. x_Count = 3, y_Count = 2
			The sprite map image will be broken up into 3 x 2 frames for the animation
			The numbers below represents the frame order the image will be broken up into
			1 2 3
			4 5 6
	*/
	Sprite_Animation(float frame_Rate, int x_Count, int y_Count, Anim_Mode mode = Anim_Mode::LOOP);

	/*	
		trans -> the transform to apply the sprite animation to 
	*/
	void update_SpriteAnim(Transform& trans);
	//Change the animation to the next frame
	void next_Frame(Transform& trans);
	//Play the animation
	void play_Anim();
	//Pause the animtion, when PlayAnim() is called resume from the previously played frame
	void pause_Anim();
	//Reset the animation frames
	void reset_Anim(Transform& trans);
	//Get the current frame number
	int current_Frame();
	//Check if animation is playing
	bool is_Playing();

private:

	float frameRate = 0;
	//The animation's own internal timer
	float animTimer = 0;
	//Number of sprite frames horizontally in the sprite map
	int xCount = 0;
	//Number of sprite frames vertically in the sprite map
	int yCount = 0;
	//Number of frames of animation in total
	int frameCount = 0;
	//Which frame number the animation is currently at
	int frameCurrent = 0;
	//whether to play the animation or not
	bool playAnim = false;

	//the x index of the frame currently being drawn
	int textureXIndex = 0;
	//the y index of the frame currently being drawn
	int textureYIndex = 0;
	//width of each frame in the sprite map
	float textureWidth = 0;
	//height of each frame in the sprite map
	float textureHeight = 0;
	//time it every frame is displayed
	float frameTime = 0;
};

//namespace {
//	s8 font;
//}

//void G_Init();
//void G_DestroyFont();
//void G_SetFontSize(int size);
//void G_DrawText(char* ch, float xPos, float yPos, float scale = 1.0f, Color color = Color(0, 0, 0));
bool Col_StaticQuadQuad(Transform trans1, Transform trans2);

//Creates a rectangle mesh with its transform
void Draw_Mesh(Transform* trans);

void Draw_QuadCollider(Transform* trans, AEGfxVertexList*& colliderMesh);

void Set_QuadPoints(Transform& trans, bool useCol = false);

void Create_QuadMesh(float width, float height, Color color, AEGfxVertexList*& mesh, float textureWidth = 1.0f, float textureHeight = 1.0f);

void Create_CircleMesh(float radius, Color color, AEGfxVertexList*& mesh);

//oid CreateSpriteMesh(Transform* trans, AEGfxVertexList*& mesh);

void Draw_StaticSprite(Transform* trans, int index);

bool Is_ButtonHover(float areaCenterX, float areaCenterY, float areaWidth, float areaHeight, s32* mouseX, s32* mouseY);

bool Col_QuadCircle(Transform const& quadTrans, Transform const& circleTrans, bool useQuadCol = false, bool useCircleCol = false);

void Flip_TextureX(Transform& trans);

void Flip_TextureY(Transform& trans);

float Absf(float val);


#endif // !GRAPHICS_H

