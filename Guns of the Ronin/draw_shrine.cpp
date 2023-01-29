
#include "draw_shrine.h"
#include "Graphics.h"
#include "DummyPlayer.h"
#include "Player.h"
#include "AEMath.h"
#include "TimeManager.h"

//float storedloadingBarPercentage = 0.0f;
//float  storedTimeElapsed = 0.0f;
//static float loadingBarPercentage = storedloadingBarPercentage;
float duration;

void Shrinepool_Init(ShrinePool& pool)
{
	duration = 0;
	pool.activeSize = 0;
	for (int i = 0; i < Shrine_Count; i++)
	{
		pool.Shrines[i].hasbeenused = false;
		CreateQuadMesh(40.0f, 40.0f, Color(1, 1, 0, 1), pool.Shrines[i].transform);
		pool.activeShrine[i] = &pool.Shrines[i];
		CreateQuadMesh(40.0f, 20.0f, Color(0, 0, 0, 1), pool.Shrines[i].loading);
		pool.activeShrine[i]->loadingbarpercentage = 0.f;
		pool.activeShrine[i]->timeElapsed = 0;
		pool.activeShrine[i]->iscolliding = false;
	}

	
}

void ShrineAdd(ShrinePool& shrinePool)
{

	for (int i = 0; i < Shrine_Count; i++)
	{
		if (shrinePool.activeShrine[i]->hasbeenused == false)
		{
			shrinePool.activeShrine[i]->hasbeenused = true;
			shrinePool.activeSize += 1;
			shrinePool.activeShrine[i]->transform.position = RandomPoint_OutsideSqaure(1, AEGetWindowHeight()/2.f, Vector2 (0,0));
			shrinePool.activeShrine[i]->loadingbarpercentage = 0.f;
			shrinePool.activeShrine[i]->loading.position = shrinePool.activeShrine[i]->transform.position;
			shrinePool.activeShrine[i]->timeElapsed = 0;
			shrinePool.activeShrine[i]->iscolliding = false;
			break;
		}
	}

}

void ShrineDelete(int index, ShrinePool& shrinePool)
{
	shrinePool.activeShrine[index]->hasbeenused = false;
	if (index < (shrinePool.activeSize - 1))
	{
		Shrine* temp = shrinePool.activeShrine[index];
		shrinePool.activeShrine[index] = shrinePool.activeShrine[shrinePool.activeSize - 1];
		shrinePool.activeShrine[shrinePool.activeSize - 1] = temp;
	}
	shrinePool.activeSize -= 1;
}

void Shrine_Update(ShrinePool& shrinePool, Player& player)
{
	duration += deltaTime;
	std::cout << duration << std::endl;
	if (duration >= 1.f)
	{
		duration = 0;
		ShrineAdd(shrinePool);
		
	}
	
	for (int i = 0; i < shrinePool.activeSize; i++)
	{
		SetQuadPoints(player.transform, 50, 50);
		SetQuadPoints(shrinePool.activeShrine[i]->transform, 40.f, 40.f);
		if (StaticCol_QuadQuad(shrinePool.activeShrine[i]->transform, player.transform))
		{
			shrinePool.activeShrine[i]->iscolliding = true;
			shrinePool.activeShrine[i]->timeElapsed += deltaTime;
			if (shrinePool.activeShrine[i]->timeElapsed >= 5.f)
			{
				ShrineDelete(i, shrinePool);
			}
			else
			{
				shrinePool.activeShrine[i]->loadingbarpercentage = shrinePool.activeShrine[i]->timeElapsed / 5.f;
				shrinePool.Shrines[i].loading.position = shrinePool.activeShrine[i]->transform.position + Vector2(0, 20);
				CreateQuadMesh(40.0f * shrinePool.activeShrine[i]->loadingbarpercentage, 20.0f, Color(0, 0, 0, 1), shrinePool.Shrines[i].loading);
			}
		}
		else
		{
			shrinePool.activeShrine[i] ->iscolliding = false;
		}
	}
}
void Draw_Shrine(ShrinePool& shrinePool)
{
	for (int i = 0; i < shrinePool.activeSize; i++)
	{

		if (shrinePool.activeShrine[i]->hasbeenused)
		{
			DrawMesh(&shrinePool.activeShrine[i]->transform);
			if (shrinePool.activeShrine[i]->iscolliding)
			{
				DrawMesh(&shrinePool.activeShrine[i]->loading);
			}
		}
		
	}
	
}
