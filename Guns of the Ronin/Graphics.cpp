/*
\copyright
		All content(C) 2023 DigiPen Institute of Technology Singapore.All rights
		reserved.Reproduction or disclosure of this file or its contents without the prior
		written consent of DigiPen Institute of Technology is prohibited.
*/
/*!
@file void.cpp
@author Teo Sheen Yeoh
@Email t.sheenyeoh@digipen.edu
@course CSD 1450
@section Section A
@date 3 March 2023
@brief This file contains code for the credit screen.
*//*______________________________________________________________________*/
#include "Graphics.h"
#include "TimeManager.h"


//void G_Init() {
//	font = AEGfxCreateFont("Assets/Roboto-Regular.ttf", 20);
//}



//Draws text contained in ch at coordinates (xPos, yPos) 
//Color of text ignores alpha value stored in color
//void G_DrawText(char* ch, float xPos, float yPos, float scale, Color color) {
//	float boundaryX = AEGetWindowWidth() / 2.0f;
//	float boundaryY = AEGetWindowHeight() / 2.0f;
//
//	AEGfxPrint(font, ch, xPos / boundaryX, yPos / boundaryY, scale, color.r, color.g, color.b);
//}

//
//void G_SetFontSize(int size) {
//	AEGfxDestroyFont(font);
//	font = AEGfxCreateFont("Assets/Roboto-Regular.ttf", size);
//}

//void G_DestroyFont() {
//	AEGfxDestroyFont(font);
//}

float Absf(float val) {
	return val < 0.0f ? (val * -1.0f) : val;
}


unsigned int Create_ARGB(float r, float g, float b, float a)
{
	int ca = int(a * 255), cr = int(r * 255), cg = int(g * 255), cb = int(b * 255);
	return ((ca & 0xff) << 24) + ((cr & 0xff) << 16) + ((cg & 0xff) << 8) + ((cb & 0xff));
}

void Create_QuadMesh(float width, float height, Color color, AEGfxVertexList*& mesh, float texture_w, float texture_h) {
	//AEGfxVertexList* pMesh = 0;
	unsigned int colorCode = Create_ARGB(color.r, color.g, color.b, color.a);
	AEGfxMeshStart();
	// This shape has 2 triangles that makes up a square
	// Color parameters represent colours as ARGB
	// UV coordinates to read from loaded textures
	AEGfxTriAdd(
		-width / 2.0f, -height / 2.0f, colorCode, 0.0f, 0.0f,
		width / 2.0f, -height / 2.0f, colorCode, texture_w, 0.0f,
		-width / 2.0f, height / 2.0f, colorCode, 0.0f, texture_h);
	AEGfxTriAdd(
		width / 2.0f, -height / 2.0f, colorCode, texture_w, 0.0f,
		width / 2.0f, height / 2.0f, colorCode, texture_w, texture_h,
		-width / 2.0f, height / 2.0f, colorCode, 0.0f, texture_h);
	// Saving the mesh (list of triangles) in pMesh
	mesh = AEGfxMeshEnd();
}


void Set_QuadPoints(Transform& trans, bool useCol) {
	float height = useCol ? trans.colliderSize.y / 2.0f : trans.height * Absf(trans.scale.y) / 2.0f;
	float width = useCol ? trans.colliderSize.x / 2.0f : trans.width * Absf(trans.scale.x) / 2.0f;

	trans.quadPoints[0] = Vector2(trans.position.x + (useCol ? trans.colliderOffsetPos.x : 0) - width,
		trans.position.y + (useCol ? trans.colliderOffsetPos.y : 0) + height);
	trans.quadPoints[1] = Vector2(trans.position.x + (useCol ? trans.colliderOffsetPos.x : 0) + width,
		trans.position.y + (useCol ? trans.colliderOffsetPos.y : 0) + height);
	trans.quadPoints[2] = Vector2(trans.position.x + (useCol ? trans.colliderOffsetPos.x : 0) - width,
		trans.position.y + (useCol ? trans.colliderOffsetPos.y : 0) - height);
	trans.quadPoints[2] = Vector2(trans.position.x + (useCol ? trans.colliderOffsetPos.x : 0) + width,
		trans.position.y + (useCol ? trans.colliderOffsetPos.y : 0) - height);
}

bool Col_StaticQuadQuad(Transform trans1, Transform trans2) {
	bool collided = true;
	if (trans1.quadPoints[0].x > trans2.quadPoints[1].x) {
		collided = false;
	}
	if (trans2.quadPoints[0].x > trans1.quadPoints[1].x) {
		collided = false;
	}
	if (trans1.quadPoints[0].y < trans2.quadPoints[2].y) {
		collided = false;
	}
	if (trans2.quadPoints[0].y < trans1.quadPoints[2].y) {
		collided = false;
	}
	return collided;
}


/* 
	This function by default uses transform's height and width with scale applied
	if useQuadCol/useCircleCol is set to true the function uses the transform's colliderSize and colliderOffsetPos instead 
*/
bool Col_QuadCircle(Transform const& quadTrans, Transform const& circleTrans, bool useQuadCol, bool useCircleCol) {

	//float circleDistX = Absf(quadTrans.position.x - circleTrans.position.x);
	float circleDistX = Absf(quadTrans.position.x + (useQuadCol ? quadTrans.colliderOffsetPos.x : 0) - 
		circleTrans.position.x + (useCircleCol ? circleTrans.colliderOffsetPos.x : 0));

	//float circleDistY = Absf(quadTrans.position.y - circleTrans.position.y);
	float circleDistY = Absf(quadTrans.position.y + (useQuadCol ? quadTrans.colliderOffsetPos.y : 0) - 
		circleTrans.position.y + (useCircleCol ? circleTrans.colliderOffsetPos.y : 0));

	float quadWidth = quadTrans.width * Absf(quadTrans.scale.x);
	float quadHeight = quadTrans.height * Absf(quadTrans.scale.y);
	float circleWidth = circleTrans.width * Absf(circleTrans.scale.x);

	if (useQuadCol) {
		quadWidth = quadTrans.colliderSize.x;
		quadHeight = quadTrans.colliderSize.y;
		
	}
	if (useCircleCol) {
		circleWidth = circleTrans.colliderSize.x;
	}

	if (circleDistX > (quadWidth / 2.0f + circleWidth)) {
		return false;
	}
	if (circleDistY > (quadHeight / 2.0f + circleWidth)) {
		return false;
	}

	if (circleDistX <= quadWidth / 2.0f) {
		return true;
	}
	if (circleDistY <= quadHeight / 2.0f) {
		return true;
	}

	float cornerSqauredDist = (circleDistX - quadWidth / 2.0f) * (circleDistX - quadWidth / 2.0f) +
		(circleDistY - quadHeight / 2.0f) * (circleDistY - quadHeight / 2.0f);

	return (cornerSqauredDist <= circleWidth * circleWidth);
}



void Draw_Mesh(Transform* trans) {

	//If the transform has texture, draw the texture
	if (trans->texture) {
		// Tell the engine to get ready to draw something with texture.
		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		// Set the tint to white, so that the sprite can
		// display the full range of colors (default is black).
		AEGfxSetTintColor(1.0f, 1.0f, 1.0f, trans->color.a);
		// Set blend mode to AE_GFX_BM_BLEND
		// This will allow transparency.
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		AEGfxSetTransparency(1.0f);

		//Set the texture map 
		//If using sprite animation use class Sprite_Animation to update texture offset
		AEGfxTextureSet(*trans->texture, trans->textureOffsetX, trans->textureOffsetY);
	}
	//Otherwise draw simple colours
	else {
		// Tell the engine to get ready to draw something with texture.
		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		// Set the tint to white, so that the sprite can
		// display the full range of colors (default is black).
		AEGfxSetTintColor(1.0f, 1.0f, 1.0f, trans->color.a);
		// Set blend mode to AE_GFX_BM_BLEND
		// This will allow transparency.
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		AEGfxSetTransparency(1.0f);
	}
	
	// Create a scale matrix 
	AEMtx33 scale = { 0 };
	AEMtx33Scale(&scale, trans->scale.x, trans->scale.y);
	// Create a rotation matrix 
	AEMtx33 rotate = { 0 };
	AEMtx33Rot(&rotate, trans->rotation);
	// Create a translation matrix
	AEMtx33 translate = { 0 };
	AEMtx33Trans(&translate, trans->position.x, trans->position.y);

	// Concat the matrices (TRS)
	AEMtx33 transform = { 0 };
	AEMtx33Concat(&transform, &rotate, &scale);
	AEMtx33Concat(&transform, &translate, &transform);
	// Choose the transform to use
	AEGfxSetTransform(transform.m);
	// Actually drawing the mesh
	AEGfxMeshDraw(*trans->mesh, AE_GFX_MDM_TRIANGLES);
}

//Please supply a 1x1 size mesh for the colliderMesh
void Draw_QuadCollider(Transform* trans, AEGfxVertexList*& colliderMesh) {
	// Tell the engine to get ready to draw something with texture.
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	// Set the tint to white, so that the sprite can
	// display the full range of colors (default is black).
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 0.5f);
	// Set blend mode to AE_GFX_BM_BLEND
	// This will allow transparency.
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(1.0f);

	// Create a scale matrix 
	AEMtx33 scale = { 0 };
	AEMtx33Scale(&scale, trans->colliderSize.x, trans->colliderSize.y);
	// Create a rotation matrix 
	AEMtx33 rotate = { 0 };
	AEMtx33Rot(&rotate, trans->rotation);
	// Create a translation matrix
	AEMtx33 translate = { 0 };
	AEMtx33Trans(&translate, trans->position.x + trans->colliderOffsetPos.x, trans->position.y + trans->colliderOffsetPos.y);

	// Concat the matrices (TRS)
	AEMtx33 transform = { 0 };
	AEMtx33Concat(&transform, &rotate, &scale);
	AEMtx33Concat(&transform, &translate, &transform);
	// Choose the transform to use
	AEGfxSetTransform(transform.m);

	// Actually drawing the mesh
	AEGfxMeshDraw(colliderMesh, AE_GFX_MDM_TRIANGLES);
}

void Create_CircleMesh(float radius, Color color, AEGfxVertexList*& mesh) {
	unsigned int colorCode = Create_ARGB(color.r, color.g, color.b, color.a);
	AEGfxMeshStart();
	int noOfVertices = 32;
	//Creating the circle shape
	for (float i = 0; i < noOfVertices; ++i)
	{
		AEGfxTriAdd(
			0.0f, 0.0f, colorCode, 0.0f, 0.0f,
			cosf(i * 2 * PI / noOfVertices) * radius, sinf(i * 2 * PI / noOfVertices) * radius, colorCode, 0.0f, 0.0f,
			cosf((i + 1) * 2 * PI / noOfVertices) * radius, sinf((i + 1) * 2 * PI / noOfVertices) * radius, colorCode, 0.0f, 0.0f);
	}
	mesh = AEGfxMeshEnd();
}


Sprite_Animation::Sprite_Animation() {

}
Sprite_Animation::Sprite_Animation(float frame_Rate, int x_Count, int y_Count, Anim_Mode mode) :
	frameRate{ frame_Rate }, xCount{ x_Count }, yCount{ y_Count }, playMode{ mode }
{
	frameCount = xCount * yCount;
	textureWidth = 1.0f / xCount;
	textureHeight = 1.0f / yCount;
	frameTime = 1.0f / frameRate;
}

void Sprite_Animation::play_Anim() {
	playAnim = true;
}

void Sprite_Animation::pause_Anim() {
	playAnim = false;
}

//Get the current frame number
int Sprite_Animation::current_Frame() {
	return frameCurrent;
}
//Check if animation is playing
bool Sprite_Animation::is_Playing() {
	return playAnim;
}

void Sprite_Animation::reset_Anim(Transform& trans) {
	playAnim = false;
	textureXIndex = 0;
	textureYIndex = 0;
	trans.textureOffsetX = 0;
	trans.textureOffsetY = 0;
	frameCurrent = 1;
	animTimer = 0;
}


void Sprite_Animation::next_Frame(Transform& trans) {
	++frameCurrent;
	
	++textureXIndex;
	if (textureXIndex > xCount - 1) {
		textureXIndex = 0;
		++textureYIndex;
		if (textureYIndex > yCount - 1) {
			textureYIndex = 0;
		}
	}
	trans.textureOffsetX = textureWidth * textureXIndex;
	trans.textureOffsetY = textureHeight * textureYIndex;

	if (frameCurrent > frameCount) {
		frameCurrent = 1;
		if (playMode == Anim_Mode::ONE_TIME) {
			playAnim = false;
		}
	}
}
void Sprite_Animation::update_SpriteAnim(Transform& trans) {
	//If animation is not supposed to play
	if (!playAnim) {
		return;
	}

	animTimer += deltaTime;
	if (animTimer >= frameTime) {
		next_Frame(trans);
		animTimer = 0;
	}

}

void Flip_TextureX(Transform& trans) {
	trans.scale.x *= -1.0f;
}

void Flip_TextureY(Transform& trans) {
	trans.scale.y *= -1.0f;
}


void Draw_StaticSprite(Transform* trans,int index) {
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxSetTransparency(1.0f);
	AEGfxTextureSet(*trans->texture, (trans->height / trans->width)*index, 0.f);

	AEMtx33 scale = { 0 };
	AEMtx33Scale(&scale, trans->scale.x, trans->scale.y);
	AEMtx33 rotate = { 0 };
	AEMtx33Rot(&rotate, trans->rotation);
	AEMtx33 translate = { 0 };
	AEMtx33Trans(&translate, trans->position.x, trans->position.y);
	AEMtx33 transform = { 0 };
	AEMtx33Concat(&transform, &rotate, &scale);
	AEMtx33Concat(&transform, &translate, &transform);
	AEGfxSetTransform(transform.m);
	AEGfxMeshDraw(*trans->mesh, AE_GFX_MDM_TRIANGLES);
}

bool Is_ButtonHover(float area_center_x, float area_center_y, float area_width, float area_height, s32* mouse_x, s32* mouse_y){
	float area_x_start, area_x_end, area_y_start, area_y_end;
	area_x_start = area_center_x - (0.5f * area_width);
	area_x_end = area_center_x + (0.5f * area_width);
	area_y_start = area_center_y - (0.5f * area_height);
	area_y_end = area_center_y + (0.5f * area_height);

	if (*mouse_x > area_x_start && *mouse_x < area_x_end && *mouse_y < area_y_start && *mouse_y > area_y_end)
	{
		return true;
	}
	else {
		return false;
	}




}
