
#include "draw_shrine.h"
#include "Graphics.h"
#include "DummyPlayer.h"
#include "Player.h"
#include "AEMath.h"

float storedloadingBarPercentage = 0.0f;
float  storedTimeElapsed = 0.0f;
static float loadingBarPercentage = storedloadingBarPercentage;
static float timeElapsed = storedTimeElapsed;

void Shrinepool_Init(ShrinePool& pool)
{
	pool.activeSize = 0;
	for (int i = 0; i < Shrine_Count; i++)
	{
		pool.Shrines[i].hasbeenused = false;
		CreateQuadMesh(40.0f, 40.0f, Color(1, 1, 0, 1), pool.Shrines[i]->transform);
		pool.activeShrine[i] = &pool.Shrines[i];
	}
}



void Shrine_Update(ShrinePool* Shrines, Player* Player)
{
	AEVec2 PLAYER_Pos;
	PLAYER_Pos.x = Player->transform.position.x;
	PLAYER_Pos.y = Player->transform.position.y;
	AEVec2 Shrine_Pos;
	Shrine_Pos.x = Shrines->transform.position.x;
	Shrine_Pos.y = Shrines->transform.position.y;
	
	if (AETestRectToRect(&PLAYER_Pos, 20.0f, 20.0f, &Shrine_Pos, 40.0f, 40.0f))
	{
		
		timeElapsed += AEFrameRateControllerGetFrameTime() * 2.0f;
		if (timeElapsed >= 10.f)
		{
			loadingBarPercentage = 1.f;
		}
		else
		{
			loadingBarPercentage = timeElapsed / 10.f;
		}

		 if (loadingBarPercentage >= 1.0)
		 {
			 Shrines->hasbeenused = true;
			 storedloadingBarPercentage = loadingBarPercentage;
			 storedTimeElapsed = timeElapsed;
			 timeElapsed = 0.0f;
			 
		 }
	}
	else
	{
		float timeElapsed = 0.0f;
	}

}
void Draw_Shrine(ShrinePool* Shrines, Shrine*loading)
{
	for (int i = 0; i < Shrines->activeSize; i++)
	{

		if (Shrines->hasbeenused = true)
		{
			CreateQuadMesh(40.0f * loadingBarPercentage, 20.0f, loading->transform.color, loading->transform);
		}
	}
}