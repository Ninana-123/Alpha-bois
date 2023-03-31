
#include "Guide.h"
Guide guideBG;
AEGfxTexture* guideBGTexture;

Player player;
BulletPool bulletPool;

/* Shrines */
Guide explosionShrine;
Guide freezeShrine;
Guide godShrine;
Guide healthShrine;
Guide voidShrine;
Guide windShrine;
Guide loadingBar;
Guide shrineSigns;
Guide shrineExplain;
Guide windTest;

AEGfxTexture* explosionTexture;
AEGfxTexture* freezeTexture;
AEGfxTexture* godTexture;
AEGfxTexture* healthTexture;
AEGfxTexture* voidTexture;
AEGfxTexture* windTexture;
AEGfxTexture* shrineSignsTexture;


float shrineScale = 3.f;

float explosionShrineX = -700.0f;
float explosionShrineY = 300.0f;

float freezeShrineX = explosionShrineX + 200.0f;
float freezeShrineY = explosionShrineY;

float godShrineX = explosionShrineX;
float godShrineY = explosionShrineY - 250.0f;

float healthShrineX = freezeShrineX;
float healthShrineY = godShrineY;

float voidShrineX = explosionShrineX;
float voidShrineY = godShrineY - 250.0f;

float windShrineX = freezeShrineX;
float windShrineY = voidShrineY;


/* Enemies */
Guide archer;
Guide samurai;
Guide ninja;
Guide cannon;
Guide enemySigns;
Guide enemyExplain;

AEGfxTexture* archerTexture;
AEGfxTexture* samuraiTexture;
AEGfxTexture* ninjaTexture;
AEGfxTexture* cannonTexture;
AEGfxTexture* enemySignsTexture;

float enemyScale = 3.f;

float archerX = 360.f;
float archerY = 180.f;

float samuraiX = archerX + 250.0f;
float samuraiY = archerY;

float ninjaX = archerX;
float ninjaY = archerY - 300.0f;

float cannonX = samuraiX;
float cannonY = ninjaY;

/* Controls */
Guide WASD;
AEGfxTexture* controlsTexture;
Guide click;


float WASDX = 0.0f;
float WASDY = 100.0f;

void Init_Guide() {
	/*BG*/
	guideBGTexture = AEGfxTextureLoad("Assets/GameBG1.png");
	CreateQuadMesh(1.f, 1.f, Color(1, 1, 1), GuideBGMesh);
	guideBG.transform.texture = &guideBGTexture;
	guideBG.transform.position = { 0.0f,0.0f };
	guideBG.transform.scale = { 1600.0f,-900.0f };
	guideBG.transform.height = 1.0f;
	guideBG.transform.width = 1.0f;
	guideBG.transform.rotation = 0.0f;
	guideBG.transform.mesh = &GuideBGMesh;
	/*Player*/
	Player_Init(&player,bulletPool);
	
	/*Shrines*/
	explosionTexture = AEGfxTextureLoad("Assets/Explosion.png");
	CreateQuadMesh(50.f, 50.f, Color(1, 1, 1), explosionMesh);
	explosionShrine.transform.texture = &explosionTexture;
	explosionShrine.transform.position = { explosionShrineX,explosionShrineY };
	explosionShrine.transform.scale = { shrineScale,-shrineScale };
	explosionShrine.transform.height = 1.0f;
	explosionShrine.transform.width = 1.0f;
	explosionShrine.transform.rotation = 0.0f;
	explosionShrine.transform.mesh = &explosionMesh;

	freezeTexture = AEGfxTextureLoad("Assets/Freeze.png");
	CreateQuadMesh(50.f, 50.f, Color(1, 1, 1), freezeMesh);
	freezeShrine.transform.texture = &freezeTexture;
	freezeShrine.transform.position = { freezeShrineX,freezeShrineY };
	freezeShrine.transform.scale = { shrineScale,-shrineScale };
	freezeShrine.transform.height = 1.0f;
	freezeShrine.transform.width = 1.0f;
	freezeShrine.transform.rotation = 0.0f;
	freezeShrine.transform.mesh = &freezeMesh;

	godTexture = AEGfxTextureLoad("Assets/God.png");
	CreateQuadMesh(50.f, 50.f, Color(1, 1, 1), godMesh);
	godShrine.transform.texture = &godTexture;
	godShrine.transform.position = { godShrineX,godShrineY };
	godShrine.transform.scale = { shrineScale,-shrineScale };
	godShrine.transform.height = 1.0f;
	godShrine.transform.width = 1.0f;
	godShrine.transform.rotation = 0.0f;
	godShrine.transform.mesh = &godMesh;

	healthTexture = AEGfxTextureLoad("Assets/Health.png");
	CreateQuadMesh(50.f, 50.f, Color(1, 1, 1), healthMesh);
	healthShrine.transform.texture = &healthTexture;
	healthShrine.transform.position = { healthShrineX,healthShrineY };
	healthShrine.transform.scale = { shrineScale,-shrineScale };
	healthShrine.transform.height = 1.0f;
	healthShrine.transform.width = 1.0f;
	healthShrine.transform.rotation = 0.0f;
	healthShrine.transform.mesh = &healthMesh;

	voidTexture = AEGfxTextureLoad("Assets/Void.png");
	CreateQuadMesh(50.f, 50.f, Color(1, 1, 1), voidMesh);
	voidShrine.transform.texture = &voidTexture;
	voidShrine.transform.position = { voidShrineX,voidShrineY };
	voidShrine.transform.scale = { shrineScale,-shrineScale };
	voidShrine.transform.height = 1.0f;
	voidShrine.transform.width = 1.0f;
	voidShrine.transform.rotation = 0.0f;
	voidShrine.transform.mesh = &voidMesh;

	windTexture = AEGfxTextureLoad("Assets/Wind.png");
	CreateQuadMesh(50.f, 50.f, Color(1, 1, 1), windMesh);
	windShrine.transform.texture = &windTexture;
	windShrine.transform.position = { windShrineX,windShrineY };
	windShrine.transform.scale = { shrineScale,-shrineScale };
	windShrine.transform.height = 1.0f;
	windShrine.transform.width = 1.0f;
	windShrine.transform.rotation = 0.0f;
	windShrine.transform.mesh = &windMesh;
	/*Shrine Signs*/
	shrineSignsTexture = AEGfxTextureLoad("Assets/ShrineSigns.png");
	CreateQuadMesh(1.f, 1.f, Color(1, 1, 1), shrineSignsMesh,1.f/9.f,1.f);
	shrineSigns.transform.texture = &shrineSignsTexture;
	shrineSigns.transform.position = { freezeShrineX + 250.f,freezeShrineY + 50.f};
	shrineSigns.transform.scale = { 250.f,-125.f };
	shrineSigns.transform.height = 1.0f;
	shrineSigns.transform.width = 9.0f;
	shrineSigns.transform.rotation = 0.0f;
	shrineSigns.transform.mesh = &shrineSignsMesh;
		
	CreateQuadMesh(1.f, 1.f, Color(1, 1, 1), shrineExplainMesh,1.f/9.f,1.f);
	shrineExplain.transform.texture = &shrineSignsTexture;
	shrineExplain.transform.position = { shrineSigns.transform.position.x,shrineSigns.transform.position.y - 125};
	shrineExplain.transform.scale = { 250.f,-125.f };
	shrineExplain.transform.height = 1.0f;
	shrineExplain.transform.width = 9.0f;
	shrineExplain.transform.rotation = 0.0f;
	shrineExplain.spriteIndex = 1;
	shrineExplain.transform.mesh = &shrineExplainMesh;
			
	CreateQuadMesh(1.f, 1.f, Color(1, 1, 1), windTestMesh,1.f/9.f,1.f);
	windTest.transform.texture = &shrineSignsTexture;
	windTest.transform.position = {windShrine.transform.position.x + 180.f,windShrine.transform.position.y};
	windTest.transform.scale = { 250.f,-125.f };
	windTest.transform.height = 1.0f;
	windTest.transform.width = 9.0f;
	windTest.transform.rotation = 0.0f;
	windTest.spriteIndex = 1;
	windTest.transform.mesh = &shrineExplainMesh;
	

	CreateQuadMesh(1.0f, 10.0f, Color(0.0f, 0.0f, 0.0f, 1.0f), guideLoadingBar);
	loadingBar.transform.position = { windShrineX, windShrineY + 85.f };
	loadingBar.transform.scale.x = 0.f;
	loadingBar.transform.mesh = &guideLoadingBar;
	/*Enemies*/
	archerTexture = AEGfxTextureLoad("Assets/Archer.png");
	CreateQuadMesh(50.f, 50.f, Color(1, 1, 1), archerMesh);
	archer.transform.texture = &archerTexture;
	archer.transform.position = { archerX,archerY };
	archer.transform.scale = { enemyScale,-enemyScale};
	archer.transform.height = 1.0f;
	archer.transform.width = 1.0f;
	archer.transform.rotation = 0.0f;
	archer.transform.mesh = &archerMesh;

	samuraiTexture = AEGfxTextureLoad("Assets/Samurai1.png");
	CreateQuadMesh(50.f, 50.f, Color(1, 1, 1), samuraiMesh);
	samurai.transform.texture = &samuraiTexture;
	samurai.transform.position = { samuraiX,samuraiY };
	samurai.transform.scale = { enemyScale,-enemyScale};
	samurai.transform.height = 1.0f;
	samurai.transform.width = 1.0f;
	samurai.transform.rotation = 0.0f;
	samurai.transform.mesh = &samuraiMesh;
	
	ninjaTexture = AEGfxTextureLoad("Assets/Ninja1.png");
	CreateQuadMesh(50.f, 50.f, Color(1, 1, 1), ninjaMesh);
	ninja.transform.texture = &ninjaTexture;
	ninja.transform.position = { ninjaX,ninjaY };
	ninja.transform.scale = { enemyScale,-enemyScale};
	ninja.transform.height = 1.0f;
	ninja.transform.width = 1.0f;
	ninja.transform.rotation = 0.0f;
	ninja.transform.mesh = &ninjaMesh;
	
	cannonTexture = AEGfxTextureLoad("Assets/Cannon1.png");
	CreateQuadMesh(50.f, 50.f, Color(1, 1, 1), cannonMesh);
	cannon.transform.texture = &cannonTexture;
	cannon.transform.position = { cannonX,cannonY };
	cannon.transform.scale = { enemyScale,-enemyScale};
	cannon.transform.height = 1.0f;
	cannon.transform.width = 1.0f;
	cannon.transform.rotation = 0.0f;
	cannon.transform.mesh = &cannonMesh;
	/*Enemy signs*/
	enemySignsTexture = AEGfxTextureLoad("Assets/EnemySigns.png");
	CreateQuadMesh(1.f, 1.f, Color(1, 1, 1), enemySignsMesh, 1.f / 6.f, 1.f);
	enemySigns.transform.texture = &enemySignsTexture;
	enemySigns.transform.position = { shrineSigns.transform.position.x + 400.f,shrineSigns.transform.position.y};
	enemySigns.transform.scale = { 250.f,-125.f };
	enemySigns.transform.height = 1.0f;
	enemySigns.transform.width = 6.0f;
	enemySigns.transform.rotation = 0.0f;
	enemySigns.transform.mesh = &enemySignsMesh;
	
	CreateQuadMesh(1.f, 1.f, Color(1, 1, 1), enemyExplainMesh, 1.f / 6.f, 1.f);
	enemyExplain.transform.texture = &enemySignsTexture;
	enemyExplain.transform.position = { shrineSigns.transform.position.x + 400.f,shrineSigns.transform.position.y-125};
	enemyExplain.transform.scale = { 250.f,-125.f };
	enemyExplain.transform.height = 1.0f;
	enemyExplain.transform.width = 6.0f;
	enemyExplain.transform.rotation = 0.0f;
	enemyExplain.transform.mesh = &enemyExplainMesh;

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
	click.spriteIndex = 9;
	click.transform.mesh = &clickMesh;

	AEAudioPlay(guideSong, guideAudioGroup, 1, 1, -1);

}

void Update_Guide() {
	Player_Update(&player, bulletPool);
	SetQuadPoints(player.transform);
	SetQuadPoints(windShrine.transform);

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
	if ((StaticCol_QuadQuad(player.transform,windShrine.transform)) ) {
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
	DrawMesh(&explosionShrine.transform);
	DrawMesh(&freezeShrine.transform);
	DrawMesh(&godShrine.transform);
	DrawMesh(&healthShrine.transform);
	DrawMesh(&voidShrine.transform);
	DrawMesh(&windShrine.transform);
	DrawMesh(&loadingBar.transform);

	/*Shrine Signs*/
	DrawStaticSprite(&shrineSigns.transform,0);
	DrawStaticSprite(&shrineExplain.transform,1);
	DrawStaticSprite(&windTest.transform,2);

	/*Enemies*/
	DrawMesh(&archer.transform);
	DrawMesh(&samurai.transform);
	DrawMesh(&ninja.transform);
	DrawMesh(&cannon.transform);

	/*Enemy Signs*/
	DrawStaticSprite(&enemySigns.transform,0);
	DrawStaticSprite(&enemyExplain.transform,1);

	/*Controls*/
	DrawStaticSprite(&WASD.transform,WASD.spriteIndex);
	DrawStaticSprite(&click.transform, click.spriteIndex);

	/*Draw Player*/
	Draw_Player(&player, bulletPool);
}
void Free_Guide() {
	/*Player Unload*/
	Free_Player();
	/*BG Mesh*/
	AEGfxMeshFree(GuideBGMesh);
	/*Shrine Mesh*/
	AEGfxMeshFree(explosionMesh);
	AEGfxMeshFree(freezeMesh);
	AEGfxMeshFree(godMesh);
	AEGfxMeshFree(healthMesh);
	AEGfxMeshFree(voidMesh);
	AEGfxMeshFree(windMesh);
	/*Shrine Signs Mesh*/
	AEGfxMeshFree(shrineSignsMesh);
	AEGfxMeshFree(shrineExplainMesh);
	AEGfxMeshFree(windTestMesh);
	AEGfxMeshFree(guideLoadingBar);
	/*Enemy Mesh*/
	AEGfxMeshFree(archerMesh);
	AEGfxMeshFree(samuraiMesh);
	AEGfxMeshFree(ninjaMesh);
	AEGfxMeshFree(cannonMesh);
	/*Enemy signs Mesh*/
	AEGfxMeshFree(enemySignsMesh);
	AEGfxMeshFree(enemyExplainMesh);
	/*Controls Mesh*/
	AEGfxMeshFree(WASDMesh);
	AEGfxMeshFree(clickMesh);

	/*BG Texture*/
	AEGfxTextureUnload(guideBGTexture);

	/* Shrine textures*/
	AEGfxTextureUnload(explosionTexture);
	AEGfxTextureUnload(freezeTexture);
	AEGfxTextureUnload(godTexture);
	AEGfxTextureUnload(healthTexture);
	AEGfxTextureUnload(voidTexture);
	AEGfxTextureUnload(windTexture);
	/*Shrine signs texture*/
	AEGfxTextureUnload(shrineSignsTexture);

	/*Enemy textures*/
	AEGfxTextureUnload(archerTexture);
	AEGfxTextureUnload(samuraiTexture);
	AEGfxTextureUnload(ninjaTexture);
	AEGfxTextureUnload(cannonTexture);

	/*Enemy signs texture*/
	AEGfxTextureUnload(enemySignsTexture);
	/*Controls textures*/
	AEGfxTextureUnload(controlsTexture);
	
}
