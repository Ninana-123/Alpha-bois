
#include "Guide.h"
AEGfxTexture* GuideBG;
AEGfxTexture* playerTexture;


Guide guide;
Guide player;

void Init_Guide() {

	GuideBG = AEGfxTextureLoad("Assets/GameBG1.png");
	CreateQuadMesh(1.f, 1.f, Color(1, 1, 1), GuideBGMesh);
	guide.transform.texture = &GuideBG;
	guide.transform.position = { 0.0f,0.0f };
	guide.transform.scale = { 1600.0f,-900.0f };
	guide.transform.height = 1.0f;
	guide.transform.width = 1.0f;
	guide.transform.rotation = 0.0f;
	guide.transform.mesh = &GuideBGMesh;	
	
	playerTexture = AEGfxTextureLoad("Assets/RoninStanding.png");
	CreateQuadMesh(50.f, 50.f, Color(1, 1, 1), playerMesh);
	player.transform.texture = &playerTexture;
	player.transform.position = { 0.0f,0.0f };
	player.transform.scale = { 2.f,-2.f };
	player.transform.height = 1.0f;
	player.transform.width = 1.0f;
	player.transform.rotation = 0.0f;
	player.transform.mesh = &playerMesh;

}

void Update_Guide() {

}
void Draw_Guide() {
	DrawMesh(&guide.transform);
	DrawMesh(&player.transform);
}
void Free_Guide() {

}
