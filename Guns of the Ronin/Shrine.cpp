
#include "Shrine.h"
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
	CreateQuadMesh(SHRINE_WIDTH, SHRINE_HEIGHT, Color(1, 1, 0, 1), shrineMesh);
	for (int i = 0; i < Shrine_Count; i++)
	{
		pool.Shrines[i].hasbeenused = false;
		pool.Shrines[i].transform.height = SHRINE_HEIGHT;
		pool.Shrines[i].transform.width = SHRINE_WIDTH;
		pool.Shrines[i].transform.mesh = &shrineMesh;
		pool.Shrines[i].loading.mesh = &loadingBarMesh;
		pool.activeShrine[i] = &pool.Shrines[i];
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
	//std::cout << duration << std::endl;
	if (duration >= 1.f)
	{
		duration = 0;
		ShrineAdd(shrinePool);
		
	}
	
	for (int i = 0; i < shrinePool.activeSize; i++)
	{
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
				shrinePool.Shrines[i].loading.position = shrinePool.activeShrine[i]->transform.position + Vector2(0, 50);
				if (loadingBarMesh)
				{
					AEGfxMeshFree(loadingBarMesh);
					loadingBarMesh = 0;
				}
				CreateQuadMesh(40.0f * shrinePool.activeShrine[i]->loadingbarpercentage, 20.0f, Color(0, 0, 0, 1), loadingBarMesh);
				shrinePool.Shrines[i].loading.mesh = &loadingBarMesh;

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

void Free_Shrines() {
	AEGfxMeshFree(shrineMesh);
	if (loadingBarMesh) {
		AEGfxMeshFree(loadingBarMesh);

	}
}