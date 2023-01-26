
#include "draw_shrine.h"
#include "Graphics.h"
#include "DummyPlayer.h"
#include "Player.h"
#include "AEMath.h"


void Draw_Shrine_Init(Shrine* Shrines, Shrine* loading)
{
	Shrines->transform.color = Color(1, 1, 0, 1);
	CreateQuadMesh(40.0f, 40.0f, Shrines->transform.color, Shrines->transform);
	Shrines->transform.position = Vector2(150.f, 150.f);
	Shrines->hasbeenused = FALSE;
	loading->transform.color = Color(1, 0, 1, 1);
	CreateQuadMesh(40.0f, 20.0f, loading->transform.color, loading -> transform);
	loading->transform.position = Vector2(150.0f, 200.0f);

}

void Draw_Shrine_Update(Shrine* Shrines, Player* Player, Shrine* loading)
{
	AEVec2 PLAYER_Pos;
	PLAYER_Pos.x = Player->transform.position.x;
	PLAYER_Pos.y = Player->transform.position.y;
	AEVec2 Shrine_Pos;
	Shrine_Pos.x = Shrines->transform.position.x;
	Shrine_Pos.y = Shrines->transform.position.y;
	float storedloadingBarPercentage = 0.0f;
	float  storedTimeElapsed = 0.0f;
	if (AETestRectToRect(&PLAYER_Pos, 20.0f, 20.0f, &Shrine_Pos, 40.0f, 40.0f))
	{
		static float loadingBarPercentage = storedloadingBarPercentage;
		static float timeElapsed = storedTimeElapsed;
		timeElapsed += AEFrameRateControllerGetFrameTime() * 2.0f;
		if (timeElapsed >= 10.f)
		{
			loadingBarPercentage = 1.f;
		}
		else
		{
			loadingBarPercentage = timeElapsed / 10.f;
		}

		if (!Shrines->hasbeenused)
		{
			CreateQuadMesh(40.0f * loadingBarPercentage, 20.0f, loading->transform.color, loading->transform);
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
void Draw_Shrine(Shrine* Shrines, Shrine*loading)
{
	if (!Shrines->hasbeenused)
	{
		DrawMesh(&Shrines->transform);
	}
	else
	{
		DrawMesh(&Shrines->transform);
		if (loading->transform.mesh != NULL)
		{
			DrawMesh(&loading->transform);
		}
		if (loading->transform.mesh != NULL)
		{
			AEGfxMeshFree(loading->transform.mesh);
			loading->transform.mesh = NULL;
		}
		if (Shrines->transform.mesh != NULL)
		{
			AEGfxMeshFree(Shrines->transform.mesh);
			Shrines->transform.mesh = NULL;
		}
	}
}