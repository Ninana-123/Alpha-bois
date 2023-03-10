
#include "Shrine.h"
#include "Explosion.h"
#include "Graphics.h"
#include "DummyPlayer.h"
#include "Player.h"
#include "AEMath.h"
#include "Physics.h"
#include "TimeManager.h"
#include "EnemyController.h"
#include "random"
#include "PlayerInfo.h"
#include "Samurai.h"

float duration;
float timeSincePause = 0.0f;
AEGfxTexture *assetfreeze;
AEGfxTexture *assetheal;
AEGfxTexture *assetwind;
AEGfxTexture* assetexplosion;
AEGfxTexture* assetgod;

s32 MouseX, MouseY;


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
	/*assetfreeze = AEGfxTextureLoad("Assets/Freeze.png");
	assetheal = AEGfxTextureLoad("Assets/Health.png");
	assetwind = AEGfxTextureLoad("Assets/Wind.png");*/
	assetexplosion = AEGfxTextureLoad("Assets/Explosion.png");
	//assetgod = AEGfxTextureLoad("Assets/Freeze.png");


}


int Random(int min, int max)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(min, max);
	return dis(gen);
}

void ShrineAdd(ShrinePool & shrinePool)
{
	for (int i = 0; i < Shrine_Count; i++)
	{
		if (shrinePool.activeShrine[i]->hasbeenused == false)
		{
			shrinePool.activeShrine[i]->hasbeenused = true;
			shrinePool.activeSize += 1;
			shrinePool.activeShrine[i]->transform.position = RandomPoint_OutsideSqaure(1, AEGetWindowHeight() / 2.f, Vector2(0, 0));
			shrinePool.activeShrine[i]->loadingbarpercentage = 0.f;
			shrinePool.activeShrine[i]->loading.position = shrinePool.activeShrine[i]->transform.position;
			shrinePool.activeShrine[i]->timeElapsed = 0;
			shrinePool.activeShrine[i]->iscolliding = false;
			shrinePool.activeShrine[i]->transform.scale = { 2, 2};

			shrinePool.activeShrine[i]->types = static_cast<Shrine::Types>(Random(0, Shrine::TotalShrines - 1));
			//arranges PNG image according to type of shrine
			/*if (shrinePool.activeShrine[i]->types == Shrine::Freeze) {
				shrinePool.activeShrine[i]->transform.texture = assetfreeze;
			}

			else if (shrinePool.activeShrine[i]->types == Shrine::Heal) {
				shrinePool.activeShrine[i]->transform.texture = assetheal;
			}

			else if (shrinePool.activeShrine[i]->types == Shrine::Push) {
				shrinePool.activeShrine[i]->transform.texture = assetwind;
			}*/

			 if (shrinePool.activeShrine[i]->types == Shrine::Explosion)
			 {
				shrinePool.activeShrine[i]->transform.texture = assetexplosion;
			 }
			 /*if (shrinePool.activeShrine[i]->types == Shrine::God)
			 {
				 shrinePool.activeShrine[i]->transform.texture = assetgod;
			 }*/

			std::cout << "Random shrine type: " << shrinePool.activeShrine[i]->types << std::endl;
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

void Shrine_Update(ShrinePool& shrinePool, SamuraiPool& samPool, ArcherPool archPool, NinjaPool ninPool, Player& player, PlayerInfo& playerinfo, ExplosionPool& explosionPool, int index)
{
	duration += deltaTime;
	//std::cout << duration << std::endl;
	if (duration >= 1.f)
	{
		duration = 0;
		ShrineAdd(shrinePool);

	}

	timeSincePause += deltaTime;
	for (int i = 0; i < shrinePool.activeSize; i++)
	{
		SetQuadPoints(shrinePool.activeShrine[i]->transform, 40.f, 40.f);
		if (StaticCol_QuadQuad(shrinePool.activeShrine[i]->transform, player.transform))
		{
			shrinePool.activeShrine[i]->iscolliding = true;
			shrinePool.activeShrine[i]->timeElapsed += deltaTime;
			if (shrinePool.activeShrine[i]->timeElapsed >= 2.f)
			{
				/*if (shrinePool.activeShrine[i]->types == Shrine::Freeze)
				{
					TimePauseEnemy();
					timeSincePause = 0.0f;
					ShrineDelete(i, shrinePool);
					std::cout << "Freeze tower" << std::endl;
				}
				if (shrinePool.activeShrine[i]->types == Shrine::Push)
				{
					Push_Enemies(samPool, archPool, HORIZONTAL, -500, ninPool);
					ShrineDelete(i, shrinePool);
					std::cout << "Push tower" << std::endl;
				}
				if (shrinePool.activeShrine[i]->types == Shrine::Heal)
				{
					Heal_player(playerinfo);
					ShrineDelete(i, shrinePool);
					std::cout << "Heal tower" << std::endl;
					std::cout << playerinfo.health << std::endl;
				}*/
				if (shrinePool.activeShrine[i]->types == Shrine::Explosion)
				{
					//shrinePool.activeShrine[i]->inshrine = true; 
					explosionCount = 0;
					duration += deltaTime;
					if (duration >= 1.f)
					{
						duration = 0;
						ExplosionAdd(explosionPool);
					}
					Explosion_Update(explosionPool, samPool);
				}
				else
				{
					shrinePool.activeShrine[i]->inshrine = false;
				}
			
				/*if (shrinePool.activeShrine[i]->types == Shrine::God)
				{
					AEInputGetCursorPosition(&MouseX, &MouseY);
					for (int i = 0; i < samPool.activeSize; ++i)
					{
						if (AEInputCheckCurr(AEVK_LBUTTON))
						{
							if (MouseX == samPool.activeSamurais[i]->transform.position.x && MouseY == samPool.activeSamurais[i]->transform.position.y)
							{
								SamuraiRemove(index, samPool);
							}
						}
					}

				}*/
				
			}
			else
			{
				shrinePool.activeShrine[i]->loadingbarpercentage = shrinePool.activeShrine[i]->timeElapsed / 5.f;
				shrinePool.activeShrine[i]->loading.position = shrinePool.activeShrine[i]->transform.position + Vector2(0, 90);
				if (loadingBarMesh)
				{
					AEGfxMeshFree(loadingBarMesh);
					loadingBarMesh = 0;
				}
				CreateQuadMesh(40.0f * shrinePool.activeShrine[i]->loadingbarpercentage, 20.0f, Color(0, 0, 0, 1), loadingBarMesh);
				shrinePool.activeShrine[i]->loading.mesh = &loadingBarMesh;

			}
		}
		else
		{
			shrinePool.activeShrine[i]->iscolliding = false;
		}
	}
	if (timeSincePause >= 2.0f) {
		TimeEnemyResume();
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