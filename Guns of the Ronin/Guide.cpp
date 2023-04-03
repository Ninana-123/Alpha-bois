/*
\copyright
		All content(C) 2023 DigiPen Institute of Technology Singapore.All rights
		reserved.Reproduction or disclosure of this file or its contents without the prior
		written consent of DigiPen Institute of Technology is prohibited.
*/
/*!
@file		Guide.cpp
@author		Kai Alexander Van Adrichem Boogaert
@Email		kaialexander.v@digipen.edu
@course		CSD 1451
@section	Section A
@date		5 Febuary 2023
@brief		This file contains declaration for the guide page. Meshes are declared here as well as class Guide.
*//*______________________________________________________________________*/
#include "Guide.h"
/*BACKGROUND*/
Guide guideBG;
AEGfxTexture* guideBGTexture;
#define GUIDE_BG_SCALE_X 1600.f
#define GUIDE_BG_SCALE_Y 900.f
#define GUIDE_BG_HEIGHT 1.f
#define GUIDE_BG_WIDTH 1.f
#define GUIDE_BG_ROTATION 0.f

/*PLAYER*/
Player guidePLayer;
BulletPool guideBullet;

/* SHRINES */
Guide windShrine;
Guide loadingBar;
AEGfxTexture* windTexture;
#define GUIDE_SHRINE_SCALE 150.f
#define GUIDE_WIND_SHRINE_X -500.f
#define GUIDE_WIND_SHRINE_Y -200.f
#define GUIDE_WIND_SHRINE_HIEGHT 1.f
#define GUIDE_WIND_SHRINE_WIDTH 1.f
#define GUIDE_WIND_SHRINE_ROTATION 0.f
#define GUIDE_LOADING_BAR_OFFSET 85.f
#define GUIDE_LOADING_BAR_SCALE_X 0.f
#define GUIDE_LOADING_BAR_MAX_PERCENT 100.f

/* CONTROLS */
Guide WASD;
AEGfxTexture* controlsTexture;
Guide click;
#define GUIDE_WASD_X -100.0f
#define GUIDE_WASD_Y -150.0f
#define GUIDE_MOUSE_X 100.0f
#define GUIDE_MOUSE_Y -150.0f
#define GUIDE_MOVEMENT_SCALE_X 210.f
#define GUIDE_MOVMENT_SCALE_Y 180.f
#define GUIDE_MOVEMENT_HEIGHT 1.f
#define GUIDE_MOVMENT_WIDTH 11.f
#define GUIDE_MOVMENT_ROTATION 0.f


void Init_Guide() {
	/*BG*/
	guideBGTexture = AEGfxTextureLoad("Assets/GuideUpdated.png");
	Create_QuadMesh(1.f, 1.f, Color(1, 1, 1), GuideBGMesh);
	guideBG.transform.texture = &guideBGTexture;
	guideBG.transform.position = { 0.0f,0.0f };
	guideBG.transform.scale = { GUIDE_BG_SCALE_X,-GUIDE_BG_SCALE_Y };
	guideBG.transform.height = GUIDE_BG_HEIGHT;
	guideBG.transform.width = GUIDE_BG_WIDTH;
	guideBG.transform.rotation = GUIDE_BG_ROTATION;
	guideBG.transform.mesh = &GuideBGMesh;

	/*Player*/
	Init_Player(&guidePLayer, guideBullet);
	
	/*Shrines*/
	
	windTexture = AEGfxTextureLoad("Assets/guideWind.png");
	Create_QuadMesh(1.f, 1.f, Color(1, 1, 1), windMesh);
	windShrine.transform.texture = &windTexture;
	windShrine.transform.position = { GUIDE_WIND_SHRINE_X,GUIDE_WIND_SHRINE_Y };
	windShrine.transform.scale = { GUIDE_SHRINE_SCALE,-GUIDE_SHRINE_SCALE };
	windShrine.transform.height = GUIDE_WIND_SHRINE_HIEGHT;
	windShrine.transform.width = GUIDE_WIND_SHRINE_WIDTH;
	windShrine.transform.rotation = GUIDE_WIND_SHRINE_ROTATION;
	windShrine.transform.mesh = &windMesh;
	

	Create_QuadMesh(1.0f, 10.0f, Color(0.0f, 0.0f, 0.0f, 1.0f), guideLoadingBar);
	loadingBar.transform.position = { GUIDE_WIND_SHRINE_X, GUIDE_WIND_SHRINE_Y + GUIDE_LOADING_BAR_OFFSET };
	loadingBar.transform.scale.x = GUIDE_LOADING_BAR_SCALE_X;
	loadingBar.transform.mesh = &guideLoadingBar;

	/*Controls*/
	controlsTexture = AEGfxTextureLoad("Assets/Controls.png");
	Create_QuadMesh(1.f, 1.f, Color(1, 1, 1), WASDMesh, GUIDE_MOVEMENT_HEIGHT / GUIDE_MOVMENT_WIDTH, GUIDE_MOVEMENT_HEIGHT);
	WASD.transform.texture = &controlsTexture;
	WASD.transform.position = { GUIDE_WASD_X,GUIDE_WASD_Y };
	WASD.transform.scale = { GUIDE_MOVEMENT_SCALE_X,-GUIDE_MOVMENT_SCALE_Y };
	WASD.transform.height = GUIDE_MOVEMENT_HEIGHT;
	WASD.transform.width = GUIDE_MOVMENT_WIDTH;
	WASD.transform.rotation = GUIDE_MOVMENT_ROTATION;
	WASD.transform.mesh = &WASDMesh;

	Create_QuadMesh(1.f, 1.f, Color(1, 1, 1), clickMesh, GUIDE_MOVEMENT_HEIGHT / GUIDE_MOVMENT_WIDTH, GUIDE_MOVEMENT_HEIGHT);
	click.transform.texture = &controlsTexture;
	click.transform.position = { GUIDE_MOUSE_X,GUIDE_MOUSE_Y };
	click.transform.scale = { GUIDE_MOVEMENT_SCALE_X,-GUIDE_MOVMENT_SCALE_Y };
	click.transform.height = GUIDE_MOVEMENT_HEIGHT;
	click.transform.width = GUIDE_MOVMENT_WIDTH;
	click.transform.rotation = GUIDE_MOVMENT_ROTATION;
	click.transform.mesh = &clickMesh;

	AEAudioPlay(guideSong, guideAudioGroup, 1, 1, -1);

}

void Update_Guide() {
	/*Resuming Guide Audio*/
	AEAudioResumeGroup(guideAudioGroup);

	Set_QuadPoints(guidePLayer.transform,true);
	Set_QuadPoints(windShrine.transform);
	Update_Player(&guidePLayer, guideBullet);

	/*Toggling between the movement sprites*/
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
	if ((Col_StaticQuadQuad(guidePLayer.transform,windShrine.transform)) ) {
	/*Loading bar for wind shrine*/
		loadingBar.transform.scale.x += (deltaTime * GUIDE_LOADING_BAR_MAX_PERCENT);
	}
	if(loadingBar.transform.scale.x >= GUIDE_LOADING_BAR_MAX_PERCENT) {
		AEAudioPauseGroup(guideAudioGroup);
		gGameStateNext = GS_MAIN_MENU;
	}
}

void Draw_Guide() {

	/*BG*/
	Draw_Mesh(&guideBG.transform);

	/*Shrines*/
	Draw_Mesh(&windShrine.transform);
	Draw_Mesh(&loadingBar.transform);

	/*Controls*/
	Draw_StaticSprite(&WASD.transform,WASD.spriteIndex);
	Draw_StaticSprite(&click.transform, click.spriteIndex);

	/*Draw Player*/
	Draw_Player(&guidePLayer, guideBullet);
}
void Free_Guide() {
	/*Player Unload*/
	Free_Player();
	Free_Bullet();

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
