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
#include "Guide.h"
Guide guideBG;
AEGfxTexture* guideBGTexture;

Player guidePLayer;
BulletPool guideBullet;

/* Shrines */
Guide windShrine;
Guide loadingBar;

AEGfxTexture* windTexture;


float shrineScale = 3.f;

float windShrineX = -500.f;
float windShrineY = -200.f;


/* Enemies */

/* Controls */
Guide WASD;
AEGfxTexture* controlsTexture;
Guide click;


float WASDX = 0.0f;
float WASDY = 100.0f;

void Init_Guide() {
	/*BG*/
	guideBGTexture = AEGfxTextureLoad("Assets/GuideUpdated.png");
	CreateQuadMesh(1.f, 1.f, Color(1, 1, 1), GuideBGMesh);
	guideBG.transform.texture = &guideBGTexture;
	guideBG.transform.position = { 0.0f,0.0f };
	guideBG.transform.scale = { 1600.0f,-900.0f };
	guideBG.transform.height = 1.0f;
	guideBG.transform.width = 1.0f;
	guideBG.transform.rotation = 0.0f;
	guideBG.transform.mesh = &GuideBGMesh;

	/*Player*/
	Player_Init(&guidePLayer, guideBullet);
	
	/*Shrines*/
	
	windTexture = AEGfxTextureLoad("Assets/guideWind.png");
	CreateQuadMesh(50.f, 50.f, Color(1, 1, 1), windMesh);
	windShrine.transform.texture = &windTexture;
	windShrine.transform.position = { windShrineX,windShrineY };
	windShrine.transform.scale = { shrineScale,-shrineScale };
	windShrine.transform.height = 1.0f;
	windShrine.transform.width = 1.0f;
	windShrine.transform.rotation = 0.0f;
	windShrine.transform.mesh = &windMesh;
	

	CreateQuadMesh(1.0f, 10.0f, Color(0.0f, 0.0f, 0.0f, 1.0f), guideLoadingBar);
	loadingBar.transform.position = { windShrineX, windShrineY + 85.f };
	loadingBar.transform.scale.x = 0.f;
	loadingBar.transform.mesh = &guideLoadingBar;

	/*Controls*/
	controlsTexture = AEGfxTextureLoad("Assets/Controls.png");
	CreateQuadMesh(1.f, 1.f, Color(1, 1, 1), WASDMesh, 1.0f / 11.0f, 1.0f);
	WASD.transform.texture = &controlsTexture;
	WASD.transform.position = { -100.0f,-150.0f };
	WASD.transform.scale = { 210.0f,-180.0f};
	WASD.transform.height = 1.0f;
	WASD.transform.width = 11.0f;
	WASD.transform.rotation = 0.0f;
	WASD.transform.mesh = &WASDMesh;

	CreateQuadMesh(1.f, 1.f, Color(1, 1, 1), clickMesh, 1.0f / 11.0f, 1.0f);
	click.transform.texture = &controlsTexture;
	click.transform.position = { 100.0f,-150.0f };
	click.transform.scale = { 210.0f,-180.0f};
	click.transform.height = 1.0f;
	click.transform.width = 11.0f;
	click.transform.rotation = 0.0f;
	click.transform.mesh = &clickMesh;

	AEAudioPlay(guideSong, guideAudioGroup, 1, 1, -1);

}

void Update_Guide() {
	/*Resuming Credits Audio*/
	AEAudioResumeGroup(guideAudioGroup);

	Player_Update(&guidePLayer, guideBullet);
	/*SetQuadPoints(guidePLayer.transform,true);
	SetQuadPoints(windShrine.transform);*/

	if (AEInputCheckCurr(AEVK_W)) {
		WASD.spriteIndex = 1;
	}
	if (AEInputCheckCurr(AEVK_A)) {
		WASD.spriteIndex = 4;
	}
	if (AEInputCheckCurr(AEVK_S)) {
		WASD.spriteIndex = 5;
	}
	if (AEInputCheckCurr(AEVK_D)) {
		WASD.spriteIndex = 8;
	}
	if (AEInputCheckCurr(AEVK_W) && AEInputCheckCurr(AEVK_A)) {
		WASD.spriteIndex = 2;
	}
	if (AEInputCheckCurr(AEVK_W) && AEInputCheckCurr(AEVK_D)) {
		WASD.spriteIndex = 3;
	}
	if (AEInputCheckCurr(AEVK_S) && AEInputCheckCurr(AEVK_A)) {
		WASD.spriteIndex = 6;
	}
	if (AEInputCheckCurr(AEVK_S) && AEInputCheckCurr(AEVK_D)) {
		WASD.spriteIndex = 7;
	}
	if (!(AEInputCheckCurr(AEVK_W) || AEInputCheckCurr(AEVK_A) || AEInputCheckCurr(AEVK_S) || AEInputCheckCurr(AEVK_D))) {
		WASD.spriteIndex = 0;
	}
	if(AEInputCheckCurr(AEVK_LBUTTON)) {
		click.spriteIndex = 10;
	}
	if(!(AEInputCheckCurr(AEVK_LBUTTON))) {
		click.spriteIndex = 9;
	}
	if ((StaticCol_QuadQuad(guidePLayer.transform,windShrine.transform)) ) {
		loadingBar.transform.scale.x += (deltaTime * 100.f);
	}
	if(loadingBar.transform.scale.x >= 100.f) {
		AEAudioPauseGroup(guideAudioGroup);
		gGameStateNext = GS_MAINMENU;
	}
}

void Draw_Guide() {

	/*BG*/
	DrawMesh(&guideBG.transform);

	/*Shrines*/
	DrawMesh(&windShrine.transform);
	DrawMesh(&loadingBar.transform);

	/*Controls*/
	DrawStaticSprite(&WASD.transform,WASD.spriteIndex);
	DrawStaticSprite(&click.transform, click.spriteIndex);

	/*Draw Player*/
	Draw_Player(&guidePLayer, guideBullet);
}
void Free_Guide() {
	/*Player Unload*/
	Free_Player();

	/*Meshes*/
	AEGfxMeshFree(GuideBGMesh);
	AEGfxMeshFree(windMesh);
	AEGfxMeshFree(guideLoadingBar);
	AEGfxMeshFree(WASDMesh);
	AEGfxMeshFree(clickMesh);

	/*Textures*/
	AEGfxTextureUnload(guideBGTexture);
	AEGfxTextureUnload(windTexture);
	AEGfxTextureUnload(controlsTexture);
	
}
