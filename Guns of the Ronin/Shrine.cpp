
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

float duration;
float timeSincePause = 0.0f;
AEGfxTexture* assetfreeze;
AEGfxTexture* assetheal;
AEGfxTexture* assetwind;
AEGfxTexture* assetexplosion;
AEGfxTexture* assetgod;
AEGfxTexture* assetvoid;

s32 mousePosX;
s32 mousePosY;

s32* mouseX = &mousePosX;
s32* mouseY = &mousePosY;

float HalfX;
float HalfY;



void Shrinepool_Init(ShrinePool& pool)
{
	HalfX = (float)AEGetWindowWidth() / 2.0f;
	HalfY = (float)AEGetWindowHeight() / 2.0f;
	duration = 0;
	pool.activeSize = 0;
	CreateQuadMesh(SHRINE_WIDTH, SHRINE_HEIGHT, Color(1, 1, 0, 1), shrineMesh);
	CreateQuadMesh(LOADING_WIDTH, LOADING_HEIGHT, Color(0, 0, 0, 1), loadingBarMesh);
	for (int i = 0; i < Shrine_Count; i++)
	{
		
		pool.Shrines[i].hasbeenused = false;
		pool.Shrines[i].transform.height = SHRINE_HEIGHT;
		pool.Shrines[i].transform.width = SHRINE_WIDTH;
		pool.Shrines[i].transform.mesh = &shrineMesh;
		pool.Shrines[i].loading.mesh = &loadingBarMesh;
		pool.activeShrine[i] = &pool.Shrines[i];
		//pool.activeShrine[i]->loadingbarpercentage = 0.f;
		pool.activeShrine[i]->timeElapsed = 0;
		pool.activeShrine[i]->iscolliding = false;

	}
	assetfreeze = AEGfxTextureLoad("Assets/Freeze.png");
	assetheal = AEGfxTextureLoad("Assets/Health.png");
	assetwind = AEGfxTextureLoad("Assets/Wind.png");
	assetexplosion = AEGfxTextureLoad("Assets/Explosion.png");
	assetgod = AEGfxTextureLoad("Assets/God.png");
	assetvoid = AEGfxTextureLoad("Assets/Void.png");


}

float Vector2Distance(const Vector2& a, const Vector2& b)
{
	float dx = b.x - a.x;
	float dy = b.y - a.y;
	return sqrt(dx * dx + dy * dy);
}

bool CheckOverlapWithActiveShrines(const ShrinePool& shrinePool, const Vector2& position)
{
	for (int i = 0; i < Shrine_Count; i++)
	{
		if (shrinePool.activeShrine[i]->hasbeenused && Vector2Distance(shrinePool.activeShrine[i]->transform.position, position) < 100.0f)
		{
			return true;
		}
	}

	return false;
}

int Random(int min, int max)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(min, max);
	return dis(gen);
}

//void ShrineAdd(ShrinePool& shrinePool)
//{
//	if (!IsTime_Paused())
//	{
//		for (int i = 0; i < Shrine_Count; i++)
//		{
//			if (shrinePool.activeShrine[i]->hasbeenused == false)
//			{
//				if (shrinePool.Shrines[i].transform.position.within_dist(shrinePool.Shrines[i].transform.position, 100.0f))
//				{
//					shrinePool.activeShrine[i]->hasbeenused = true;
//					shrinePool.activeSize += 1;
//					shrinePool.activeShrine[i]->transform.position = RandomPoint_OutsideSqaure(1, AEGetWindowHeight() / 2.f, Vector2(0, 0));
//					//shrinePool.Shrines[i].loadingbarpercentage = 0.f;
//					//shrinePool.activeShrine[i]->loading.position = shrinePool.activeShrine[i]->transform.position;
//					shrinePool.Shrines[i].loading.position = shrinePool.activeShrine[i]->transform.position;
//					shrinePool.activeShrine[i]->timeElapsed = 0;
//					shrinePool.activeShrine[i]->iscolliding = false;
//					shrinePool.activeShrine[i]->transform.scale = { 2, 2 };
//
//					shrinePool.activeShrine[i]->types = static_cast<Shrine::Types>(Random(0, Shrine::TotalShrines - 1));
//					//arranges PNG image according to type of shrine
//					if (shrinePool.activeShrine[i]->types == Shrine::Freeze)
//					{
//						shrinePool.activeShrine[i]->transform.texture = &assetfreeze;
//					}
//
//					else if (shrinePool.activeShrine[i]->types == Shrine::Heal)
//					{
//						shrinePool.activeShrine[i]->transform.texture = &assetheal;
//					}
//
//					else if (shrinePool.activeShrine[i]->types == Shrine::Push)
//					{
//						shrinePool.activeShrine[i]->transform.texture = &assetwind;
//					}
//
//					if (shrinePool.activeShrine[i]->types == Shrine::Explosion)
//					{
//						shrinePool.activeShrine[i]->transform.texture = &assetexplosion;
//					}
//
//					if (shrinePool.activeShrine[i]->types == Shrine::God)
//					{
//						shrinePool.activeShrine[i]->transform.texture = &assetgod;
//					}
//
//					if (shrinePool.activeShrine[i]->types == Shrine::Void)
//					{
//						shrinePool.activeShrine[i]->transform.texture = &assetvoid;
//					}
//					std::cout << "Random shrine type: " << shrinePool.activeShrine[i]->types << std::endl;
//					break;
//				}
//			}
//		}
//	}
//}

void ShrineAdd(ShrinePool& shrinePool)
{
	if (!IsTime_Paused())
	{
		for (int i = 0; i < Shrine_Count; i++)
		{
			if (shrinePool.activeShrine[i]->hasbeenused == false)
			{
				shrinePool.activeShrine[i]->hasbeenused = true;
				shrinePool.activeSize += 1;

				// Generate a random position until it doesn't overlap with any active shrines
				Vector2 randomPosition;
				do
				{
					randomPosition = RandomPoint_OutsideSqaure(1, AEGetWindowHeight() / 2.f, Vector2(0, 0));
				} while (CheckOverlapWithActiveShrines(shrinePool, randomPosition));

				shrinePool.activeShrine[i]->transform.position = randomPosition;
				shrinePool.Shrines[i].loading.position = randomPosition;
				shrinePool.activeShrine[i]->timeElapsed = 0;
				shrinePool.activeShrine[i]->iscolliding = false;
				shrinePool.activeShrine[i]->transform.scale = { 2, 2 };
				shrinePool.activeShrine[i]->types = static_cast<Shrine::Types>(Random(0, Shrine::TotalShrines - 1));

				// Set the texture of the shrine based on its type
				switch (shrinePool.activeShrine[i]->types)
				{
				case Shrine::Freeze:
					shrinePool.activeShrine[i]->transform.texture = &assetfreeze;
					break;

				case Shrine::Heal:
					shrinePool.activeShrine[i]->transform.texture = &assetheal;
					break;

				case Shrine::Push:
					shrinePool.activeShrine[i]->transform.texture = &assetwind;
					break;

				case Shrine::Explosion:
					shrinePool.activeShrine[i]->transform.texture = &assetexplosion;
					break;

				case Shrine::God:
					shrinePool.activeShrine[i]->transform.texture = &assetgod;
					break;

				case Shrine::Void:
					shrinePool.activeShrine[i]->transform.texture = &assetvoid;
					break;
				}

				//std::cout << "Random shrine type: " << shrinePool.activeShrine[i]->types << std::endl;
				break;
			}
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

void Shrine_Update(ShrinePool& shrinePool, SamuraiPool& samPool, ArcherPool& archPool, NinjaPool &ninPool, Player& player, PlayerInfo& playerinfo, ExplosionPool& explosionPool, int index, VoidPool& voidPool, CannoneerPool& canPool)
{
	duration += deltaTime;
	//std::cout << duration << std::endl;
	AEInputGetCursorPosition(mouseX, mouseY);
	*mouseX = *mouseX - 800;
	*mouseY = (*mouseY - 450) * -1;

	if (duration >= 1.f)
	{
		duration = 0;
		ShrineAdd(shrinePool);

	}

	timeSincePause += deltaTime;
	for (int i = 0; i < shrinePool.activeSize; i++)
	{
		//SetQuadPoints(shrinePool.activeShrine[i]->transform, 150.f, 150.f);
		SetQuadPoints(shrinePool.activeShrine[i]->transform);
		if (StaticCol_QuadQuad(shrinePool.activeShrine[i]->transform, player.transform))
		{
			shrinePool.activeShrine[i]->iscolliding = true;
			shrinePool.activeShrine[i]->timeElapsed += deltaTime;
			if (shrinePool.activeShrine[i]->timeElapsed >= 2.f)
			{
				
				if (shrinePool.activeShrine[i]->types == Shrine::Explosion)
				{
					AEAudioPlay(explosionSound, mainsceneAudioGroup, 0.5f, 1.f, 0);
					for (int i = 0; i < Explosion_Count; i++)
					{
						ExplosionAdd(explosionPool);
					}
					Explosion_Update(explosionPool, archPool, canPool, ninPool);
					ShrineDelete(i, shrinePool);
					break;
				}

				if (shrinePool.activeShrine[i]->types == Shrine::Void)
				{
					AEAudioPlay(voidSound, mainsceneAudioGroup, 0.5f, 1.f, 0);
					for (int k = 0; k < Void_Count; k++)
					{
						VoidAdd(voidPool);
					}
					Void_Update(voidPool, samPool, archPool, canPool);
					ShrineDelete(i, shrinePool);
					break;
				}
				if (shrinePool.activeShrine[i]->types == Shrine::Freeze)
				{
					AEAudioPlay(freezeSound, mainsceneAudioGroup, 0.5f, 1.f, 0);
					TimePauseEnemy();
					timeSincePause = 0.0f;
					ShrineDelete(i, shrinePool);
				//std::cout << "Freeze tower" << std::endl;
					break;
				}

				if (shrinePool.activeShrine[i]->types == Shrine::Push)
				{
					AEAudioPlay(windSound, mainsceneAudioGroup, 0.5f, 1.f, 0);
					Push_Enemies(samPool, archPool, HORIZONTAL, -500, ninPool);
					ShrineDelete(i, shrinePool);
					//std::cout << "Push tower" << std::endl;
					break;
				}

				if (shrinePool.activeShrine[i]->types == Shrine::Heal)
				{
					if (playerinfo.health < 100) {
						AEAudioPlay(healthSound, mainsceneAudioGroup, 1.f, 1.f, 0);
						Heal_player(playerinfo);
						ShrineDelete(i, shrinePool);
						//std::cout << "Heal tower" << std::endl;
						std::cout << playerinfo.health << std::endl;
						break;
					}
				}

				
				if (shrinePool.activeShrine[i]->types == Shrine::God)
				{
					
					int padding = 50;
					for (int u = 0; u < samPool.activeSize; ++u)
					{
						if (AEInputCheckTriggered(AEVK_LBUTTON))
						{
							if (*mouseX >= samPool.activeSamurais[u]->transform.position.x - padding &&
								*mouseX <= samPool.activeSamurais[u]->transform.position.x + samPool.activeSamurais[u]->transform.width + padding &&
								*mouseY >= samPool.activeSamurais[u]->transform.position.y - padding &&
								*mouseY <= samPool.activeSamurais[u]->transform.position.y + samPool.activeSamurais[u]->transform.height + padding)
							{
								AEAudioPlay(godSound, mainsceneAudioGroup, 0.5f, 1.f, 0);
								SamuraiRemove(u, samPool);
								break;
							}
						}
					}
					for (int z = 0; z < archPool.activeSize; ++z)
					{
						if (AEInputCheckTriggered(AEVK_LBUTTON))
						{
							if (*mouseX >= archPool.activeArchers[z]->transform.position.x - padding &&
								*mouseX <= archPool.activeArchers[z]->transform.position.x + archPool.activeArchers[z]->transform.width + padding &&
								*mouseY >= archPool.activeArchers[z]->transform.position.y - padding &&
								*mouseY <= archPool.activeArchers[z]->transform.position.y + archPool.activeArchers[z]->transform.height + padding)
							{
							//std::cout << "Archer Clicked" << std::endl;
								ArcherRemove(z, archPool);
								break;
							}
						}
					}

					for (int k = 0; k < ninPool.activeSize; ++k)
					{
						if (*mouseX >= ninPool.activeNinjas[k]->transform.position.x - padding &&
							*mouseX <= ninPool.activeNinjas[k]->transform.position.x + ninPool.activeNinjas[k]->transform.width + padding &&
							*mouseY >= ninPool.activeNinjas[k]->transform.position.y - padding &&
							*mouseY <= ninPool.activeNinjas[k]->transform.position.y + ninPool.activeNinjas[k]->transform.height + padding)
						{
							if (AEInputCheckTriggered(AEVK_LBUTTON))
							{

								NinjaRemove(k, ninPool);
								break;
							}
						}
					}

					for (int c = 0; c < canPool.activeSize; ++c)
					{
						if (*mouseX >= canPool.activeCannoneers[c]->transform.position.x - padding &&
							*mouseX <= canPool.activeCannoneers[c]->transform.position.x + canPool.activeCannoneers[c]->transform.width + padding &&
							*mouseY >= canPool.activeCannoneers[c]->transform.position.y - padding &&
							*mouseY <= canPool.activeCannoneers[c]->transform.position.y + canPool.activeCannoneers[c]->transform.height + padding)
						{
							if (AEInputCheckTriggered(AEVK_LBUTTON))
							{

								CannoneerRemove(c, canPool);
								break;
							}
						}
					}

					// Decrease timer every frame
					shrinePool.activeShrine[i]->deleteTimer -= deltaTime;
					// If timer reaches zero, delete shrine
					if (shrinePool.activeShrine[i]->deleteTimer <= 0.0)
					{
						ShrineDelete(i, shrinePool);
					}
				}

			}
			else
			{

			    // loading
				for (int i = 0; i < shrinePool.activeSize; i++)
				{
					shrinePool.Shrines[i].loading.position = shrinePool.activeShrine[i]->transform.position + Vector2(0, 80);
					float loadingbarpercentage = shrinePool.activeShrine[i]->timeElapsed / 5.f;
					shrinePool.Shrines[i].loading.scale = Vector2(loadingbarpercentage, 1.0f);
				}

			}
		}
		else
		{
			shrinePool.activeShrine[i]->iscolliding = false;
		}
	}
	if (timeSincePause >= 2.0f)
	{
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
				DrawMesh(&shrinePool.Shrines[i].loading);
			}
		}

	}

}

void Free_Shrines()
{
	AEGfxMeshFree(shrineMesh);

	if (loadingBarMesh) 
	{
		AEGfxMeshFree(loadingBarMesh);
	}

	AEGfxTextureUnload(assetfreeze);
	AEGfxTextureUnload(assetheal);
	AEGfxTextureUnload(assetwind);
	AEGfxTextureUnload(assetexplosion);
	AEGfxTextureUnload(assetvoid);
	AEGfxTextureUnload(assetgod); 
	
}