
#include "Graphics.h"

void G_Init() {
	font = AEGfxCreateFont("Assets/Roboto-Regular.ttf", 100);
}



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

void CreateQuadMesh(float width, float height, Color color, AEGfxVertexList*& mesh) {
	//AEGfxVertexList* pMesh = 0;
	unsigned int colorCode = createARGB(color.r, color.g, color.b, color.a);
	AEGfxMeshStart();
	// This shape has 2 triangles that makes up a square
	// Color parameters represent colours as ARGB
	// UV coordinates to read from loaded textures
	AEGfxTriAdd(
		-width / 2.0f, -height / 2.0f, colorCode, 0.0f, 0.0f,
		width / 2.0f, -height / 2.0f, colorCode, 1.0f, 0.0f,
		-width / 2.0f, height / 2.0f, colorCode, 0.0f, 1.0f);
	AEGfxTriAdd(
		width / 2.0f, -height / 2.0f, colorCode, 1.0f, 0.0f,
		width / 2.0f, height / 2.0f, colorCode, 1.0f, 1.0f,
		-width / 2.0f, height / 2.0f, colorCode, 0.0f, 1.0f);
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

	// Tell the engine to get ready to draw something with texture.
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	// Set the tint to white, so that the sprite can
	// display the full range of colors (default is black).
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, trans->color.a);
	// Set blend mode to AE_GFX_BM_BLEND
	// This will allow transparency.
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(1.0f);

	//Set the texture
	AEGfxTextureSet(trans->texture, 0, 0);
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