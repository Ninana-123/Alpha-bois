
#include "Graphics.h"

void G_Init() {
	font = AEGfxCreateFont("Assets/Roboto-Regular.ttf", 20);
}


//Draws text contained in ch at coordinates (xPos, yPos) 
//Color of text ignores alpha value stored in color
void G_DrawText(char* ch, float xPos, float yPos, Color color) {
	float boundaryX = AEGetWindowWidth() / 2.0f;
	float boundaryY = AEGetWindowHeight() / 2.0f;

	AEGfxPrint(font, ch, xPos / boundaryX, yPos / boundaryY, 1, color.r, color.g, color.b);

}


void G_SetFontSize(float size) {
	AEGfxDestroyFont(font);
	font = AEGfxCreateFont("Assets/Roboto-Regular.ttf", size);
}

void CreateQuadMesh(AEGfxVertexList* pMesh, float width, float height) {

	AEGfxMeshStart();
	// This shape has 2 triangles that makes up a square
	// Color parameters represent colours as ARGB
	// UV coordinates to read from loaded textures
	AEGfxTriAdd(
		-width / 2.0f, -height / 2.0f, 0xFFFF0000, 0.0f, 0.0f,
		width / 2.0f, -height / 2.0f, 0xFF00FF00, 1.0f, 0.0f,
		-width / 2.0f, height / 2.0f, 0xFF0000FF, 0.0f, 1.0f);
	AEGfxTriAdd(
		width / 2.0f, -height / 2.0f, 0xFFFF0000, 1.0f, 0.0f,
		width / 2.0f, height / 2.0f, 0xFF00FF00, 1.0f, 1.0f,
		-width / 2.0f, height / 2.0f, 0xFF0000FF, 0.0f, 1.0f);
	// Saving the mesh (list of triangles) in pMesh
	pMesh = AEGfxMeshEnd();
}

void DrawMesh(Transform* trans) {
	// Set the texture to pTex
	AEGfxTextureSet(trans->texture, 0, 0);
	// Create a scale matrix that scales by 100 x and y
	AEMtx33 scale = { 0 };
	AEMtx33Scale(&scale, trans->scale.x, trans->scale.y);
	// Create a rotation matrix that rotates by 45 degrees
	AEMtx33 rotate = { 0 };
	AEMtx33Rot(&rotate, trans->rotation * PI * 2);
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
	AEGfxMeshDraw(trans->mesh, AE_GFX_MDM_TRIANGLES);
}
