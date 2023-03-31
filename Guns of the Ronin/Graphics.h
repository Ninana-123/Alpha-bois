#pragma once

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "AEEngine.h"
#include "Physics.h"

struct Color {
	 float r, g, b, a;

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
	float texture_offset_x = 0;
	//The texture y offset in the texture map of the current frame being drawn
	float texture_offset_y = 0;
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
		frame_Rate -> frame rate of this sprite animation, number of frames per sec
		x_Count -> the number of animation frames horizontally
		y_Count -> the number of animation frames vertically 
		Eg. x_Count = 3, y_Count = 2
			The sprite map image will be broken up into 3 x 2 frames for the animation
			The numbers below represents the frame order the image will be broken up into
			1 2 3
			4 5 6
	*/
	Sprite_Animation(float frame_Rate, int x_Count, int y_Count, Anim_Mode mode = Anim_Mode::LOOP);

	/*	
		dt -> delta time
		trans -> the transform to apply the sprite animation to 
	*/
	void Update_SpriteAnim(Transform& trans);
	//Change the animation to the next frame
	void NextFrame(Transform& trans);
	//Play the animation
	void PlayAnim();
	//Pause the animtion, when PlayAnim() is called resume from the previously played frame
	void PauseAnim();
	//Reset the animation frames
	void ResetAnim(Transform& trans);
	//Get the current frame number
	int CurrentFrame();
	//Check if animation is playing
	bool IsPlaying();

private:

	float frameRate = 0;
	//The animation's own internal timer
	float anim_timer = 0;
	//Number of sprite frames horizontally in the sprite map
	int x_count = 0;
	//Number of sprite frames vertically in the sprite map
	int y_count = 0;
	//Number of frames of animation in total
	int frame_count = 0;
	//Which frame number the animation is currently at
	int frame_current = 0;
	//whether to play the animation or not
	bool play_anim = false;

	//the x index of the frame currently being drawn
	int texture_index_x = 0;
	//the y index of the frame currently being drawn
	int texture_index_y = 0;
	//width of each frame in the sprite map
	float texture_width = 0;
	//height of each frame in the sprite map
	float texture_height = 0;
	//time it every frame is displayed
	float frame_time = 0;
};

//namespace {
//	s8 font;
//}

//void G_Init();
//void G_DestroyFont();
//void G_SetFontSize(int size);
//void G_DrawText(char* ch, float xPos, float yPos, float scale = 1.0f, Color color = Color(0, 0, 0));
bool StaticCol_QuadQuad(Transform trans1, Transform trans2);

//Creates a rectangle mesh with its transform
void DrawMesh(Transform* trans);

void Draw_QuadCollider(Transform* trans, AEGfxVertexList*& colliderMesh);

void SetQuadPoints(Transform& trans, bool useCol = false);

void CreateQuadMesh(float width, float height, Color color, AEGfxVertexList*& mesh, float texture_w = 1.0f, float texture_h = 1.0f);

void CreateCircleMesh(float radius, Color color, AEGfxVertexList*& mesh);

//oid CreateSpriteMesh(Transform* trans, AEGfxVertexList*& mesh);

void DrawStaticSprite(Transform* trans, int index);

bool IsButtonHover(float area_center_x, float area_center_y, float area_width, float area_height, s32* mouse_x, s32* mouse_y);

bool ColQuadCircle(Transform const& quadTrans, Transform const& circleTrans, bool useQuadCol = false, bool useCircleCol = false);

void FlipTexture_x(Transform& trans);

void FlipTexture_y(Transform& trans);

float Absf(float val);


#endif // !GRAPHICS_H

