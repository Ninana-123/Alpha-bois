
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

AEGfxTexture* explosionTexture;
AEGfxTexture* freezeTexture;
AEGfxTexture* godTexture;
AEGfxTexture* healthTexture;
AEGfxTexture* voidTexture;
AEGfxTexture* windTexture;

float shrineScale = 4.f;

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

AEGfxTexture* archerTexture;
AEGfxTexture* samuraiTexture;
AEGfxTexture* ninjaTexture;
AEGfxTexture* cannonTexture;

float enemyScale = 4.0f;

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

	guideBGTexture = AEGfxTextureLoad("Assets/GameBG1.png");
	CreateQuadMesh(1.f, 1.f, Color(1, 1, 1), GuideBGMesh);
	guideBG.transform.texture = &guideBGTexture;
	guideBG.transform.position = { 0.0f,0.0f };
	guideBG.transform.scale = { 1600.0f,-900.0f };
	guideBG.transform.height = 1.0f;
	guideBG.transform.width = 1.0f;
	guideBG.transform.rotation = 0.0f;
	guideBG.transform.mesh = &GuideBGMesh;
	
	Player_Init(&player,bulletPool);

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

	controlsTexture = AEGfxTextureLoad("Assets/Controls.png");
	CreateQuadMesh(1.f, 1.f, Color(1, 1, 1), WASDMesh, 1.0f / 11.0f, 1.0f);
	WASD.transform.texture = &controlsTexture;
	WASD.transform.position = { -100.0f,150.0f };
	WASD.transform.scale = { 210.0f,-180.0f};
	WASD.transform.height = 1.0f;
	WASD.transform.width = 11.0f;
	WASD.transform.rotation = 0.0f;
	WASD.transform.mesh = &WASDMesh;

	CreateQuadMesh(1.f, 1.f, Color(1, 1, 1), clickMesh, 1.0f / 11.0f, 1.0f);
	click.transform.texture = &controlsTexture;
	click.transform.position = { 100.0f,150.0f };
	click.transform.scale = { 210.0f,-180.0f};
	click.transform.height = 1.0f;
	click.transform.width = 11.0f;
	click.transform.rotation = 0.0f;
	click.spriteIndex = 9;
	click.transform.mesh = &clickMesh;

	

}

void Update_Guide() {
	Player_Update(&player, bulletPool);

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


}

void Draw_Guide() {
	DrawMesh(&guideBG.transform);
	DrawMesh(&explosionShrine.transform);
	DrawMesh(&freezeShrine.transform);
	DrawMesh(&godShrine.transform);
	DrawMesh(&healthShrine.transform);
	DrawMesh(&voidShrine.transform);
	DrawMesh(&windShrine.transform);

	DrawMesh(&archer.transform);
	DrawMesh(&samurai.transform);
	DrawMesh(&ninja.transform);
	DrawMesh(&cannon.transform);

	DrawStaticSprite(&WASD.transform,WASD.spriteIndex);
	DrawStaticSprite(&click.transform, click.spriteIndex);

	Draw_Player(&player, bulletPool);
}
void Free_Guide() {
	Free_Player();

	AEGfxMeshFree(GuideBGMesh);
	AEGfxTextureUnload(guideBGTexture);
}
