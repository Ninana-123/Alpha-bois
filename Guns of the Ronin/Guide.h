#pragma once
#include <iostream>
#include "AEEngine.h"
#include "TimeManager.h"
#include "Graphics.h"
#include "Mainscene.h"
#include "GSM.h"
#include <AEGraphics.h>
#include "Player.h"
#include "Bullets.h"
#include "MainMenu.h"

#ifndef GUIDE_H
#define GUIDE_H

namespace {
	/*          BACKGROUND        */
	AEGfxVertexList* GuideBGMesh = 0;

	/*          SHRINES           */
	AEGfxVertexList* explosionMesh = 0;
	AEGfxVertexList* freezeMesh = 0;
	AEGfxVertexList* godMesh = 0;
	AEGfxVertexList* healthMesh = 0;
	AEGfxVertexList* voidMesh = 0;
	AEGfxVertexList* windMesh = 0;
	AEGfxVertexList* guideLoadingBar = 0;
	AEGfxVertexList* shrineSignsMesh= 0;
	AEGfxVertexList* shrineExplainMesh= 0;
	AEGfxVertexList* windTestMesh= 0;

	/*          ENEMIES           */
	AEGfxVertexList* archerMesh = 0;
	AEGfxVertexList* samuraiMesh = 0;
	AEGfxVertexList* ninjaMesh = 0;
	AEGfxVertexList* cannonMesh = 0;
	AEGfxVertexList* enemySignsMesh= 0;
	AEGfxVertexList* enemyExplainMesh= 0;

	/*          CONTROLS          */
	AEGfxVertexList* WASDMesh = 0;
	AEGfxVertexList* clickMesh = 0;


}

class Guide {
public:
	Transform transform;
	int spriteIndex = 0;
	float loadingBarPercent = 0;
	

};

void Init_Guide();
void Update_Guide();
void Draw_Guide();
void Free_Guide();

#endif