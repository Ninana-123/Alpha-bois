
#include "Graphics.h"
#include "TimeManager.h"
//void G_Init() {
//	font = AEGfxCreateFont("Assets/Roboto-Regular.ttf", 20);
//}



//Draws text contained in ch at coordinates (xPos, yPos) 
//Color of text ignores alpha value stored in color
void G_DrawText(char* ch, float xPos, float yPos, float scale, Color color) {
	float boundaryX = AEGetWindowWidth() / 2.0f;
	float boundaryY = AEGetWindowHeight() / 2.0f;

	AEGfxPrint(font, ch, xPos / boundaryX, yPos / boundaryY, scale, color.r, color.g, color.b);
}


void G_SetFontSize(int size) {
	AEGfxDestroyFont(font);
	font = AEGfxCreateFont("Assets/Roboto-Regular.ttf", size);
}

void G_DestroyFont() {
	AEGfxDestroyFont(font);
}

unsigned int createARGB(float r, float g, float b, float a)
{
	int ca = int(a * 255), cr = int(r * 255), cg = int(g * 255), cb = int(b * 255);
	return ((ca & 0xff) << 24) + ((cr & 0xff) << 16) + ((cg & 0xff) << 8) + ((cb & 0xff));
}

void CreateQuadMesh(float width, float height, Color color, AEGfxVertexList*& mesh, float texture_w, float texture_h) {
	//AEGfxVertexList* pMesh = 0;
	unsigned int colorCode = createARGB(color.r, color.g, color.b, color.a);
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


void SetQuadPoints(Transform& trans, float height, float width) {
	height /= 2.0f;
	width /= 2.0f;
	trans.quadPoints[0] = Vector2(trans.position.x - width, trans.position.y + height);
	trans.quadPoints[1] = Vector2(trans.position.x + width, trans.position.y + height);
	trans.quadPoints[2] = Vector2(trans.position.x - width, trans.position.y - height);
	trans.quadPoints[2] = Vector2(trans.position.x + width, trans.position.y - height);
}

bool StaticCol_QuadQuad(Transform trans1, Transform trans2) {
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




void DrawMesh(Transform* trans) {

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
		AEGfxTextureSet(*trans->texture, trans->texture_offset_x, trans->texture_offset_y);
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
	
	// Create a scale matrix that scales by 100 x and y
	AEMtx33 scale = { 0 };
	AEMtx33Scale(&scale, trans->scale.x, trans->scale.y);
	// Create a rotation matrix that rotates by 45 degrees
	AEMtx33 rotate = { 0 };
	AEMtx33Rot(&rotate, trans->rotation);
	// Create a translation matrix that translates by
	// 100 in the x-axis and 100 in the y-axis
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

void CreateCircleMesh(float radius, Color color, AEGfxVertexList*& mesh) {
	unsigned int colorCode = createARGB(color.r, color.g, color.b, color.a);
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
	frameRate{ frame_Rate }, x_count{ x_Count }, y_count{ y_Count }, playMode{ mode }
{
	frame_count = x_count * y_count;
	texture_width = 1.0f / x_count;
	texture_height = 1.0f / y_count;
	frame_time = 1.0f / frameRate;
}

void Sprite_Animation::PlayAnim() {
	play_anim = true;
}

void Sprite_Animation::PauseAnim() {
	play_anim = false;
}

void Sprite_Animation::ResetAnim(Transform& trans) {
	play_anim = false;
	texture_index_x = 0;
	texture_index_y = 0;
	trans.texture_offset_x = 0;
	trans.texture_offset_y = 0;
	frame_current = 1;
	anim_timer = 0;
}


void Sprite_Animation::NextFrame(Transform& trans) {
	++frame_current;
	
	++texture_index_x;
	if (texture_index_x > x_count - 1) {
		texture_index_x = 0;
		++texture_index_y;
		if (texture_index_y > y_count - 1) {
			texture_index_y = 0;
		}
	}
	trans.texture_offset_x = texture_width * texture_index_x;
	trans.texture_offset_y = texture_height * texture_index_y;

	if (frame_current > frame_count) {
		frame_current = 1;
		if (playMode == Anim_Mode::ONE_TIME) {
			play_anim = false;
		}
	}
}
void Sprite_Animation::Update_SpriteAnim(Transform& trans) {
	//If animation is not supposed to play
	if (!play_anim) {
		return;
	}

	anim_timer += deltaTime;
	if (anim_timer >= frame_time) {
		NextFrame(trans);
		anim_timer = 0;
	}

}

void FlipTexture_x(Transform& trans) {
	trans.scale.x *= -1;
}

void FlipTexture_y(Transform& trans) {
	trans.scale.y *= -1;
}

void CreateSpriteMesh(Transform* trans, AEGfxVertexList*& mesh) {
	//float BG_Width = 1.0f / 4.0f;
	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, -0.5f, 0xFFFFFFFF, 0 * (trans->height / trans->width), 1.0f,
		0.5f, -0.5f, 0xFFFFFFFF, (0 + 1) * (trans->height / trans->width), 1.0f,
		-0.5f, 0.5f, 0xFFFFFFFF, 0 * (trans->height / trans->width), 0.0f
	);
	AEGfxTriAdd(
		0.5f, -0.5f, 0xFFFFFFFF, (0 + 1) * (trans->height / trans->width), 1.0f,
		0.5f, 0.5f, 0xFFFFFFFF, (0 + 1) * (trans->height / trans->width), 0.0f,
		-0.5f, 0.5f, 0xFFFFFFFF, 0 * (trans->height / trans->width), 0.0f
	);
	mesh = AEGfxMeshEnd();
}

void DrawSprite(Transform* trans,int index) {
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

bool IsButtonHover(float area_center_x, float area_center_y, float area_width, float area_height, s32* mouse_x, s32* mouse_y){
	float area_x_start, area_x_end, area_y_start, area_y_end;
	area_x_start = area_center_x - (0.5 * area_width);
	area_x_end = area_center_x + (0.5 * area_width);
	area_y_start = area_center_y - (0.5 * area_height);
	area_y_end = area_center_y + (0.5 * area_height);

	if (*mouse_x > area_x_start && *mouse_x < area_x_end && *mouse_y < area_y_start && *mouse_y > area_y_end)
	{
		return true;
	}
	else {
		return false;
	}

}
