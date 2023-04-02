/*
\copyright
		All content(C) 2023 DigiPen Institute of Technology Singapore.All rights
		reserved.Reproduction or disclosure of this file or its contents without the prior
		written consent of DigiPen Institute of Technology is prohibited.
*/
/*!
@file void.cpp
@author Teo Sheen Yeoh & Vance Tay
@Email t.sheenyeoh@digipen.edu & Junfengvance.t@digipen.edu
@course CSD 1450
@section Section A
@date 3 March 2023
@brief This file contains contains code on how would all the shrine work with its individual abilites 
*//*______________________________________________________________________*/
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
AEGfxTexture* assetFreeze;
AEGfxTexture* assetHeal;
AEGfxTexture* assetWind;
AEGfxTexture* assetExplosion;
AEGfxTexture* assetGod;
AEGfxTexture* assetVoid;

s32 mousePosX;
s32 mousePosY;

s32* mouseX = &mousePosX;
s32* mouseY = &mousePosY;

float HalfX;
float HalfY;



void Shrine_PoolInit(ShrinePool& pool)
{
	HalfX = (float)AEGetWindowWidth() / 2.0f;
	HalfY = (float)AEGetWindowHeight() / 2.0f;
	duration = 0;
	pool.activeSize = 0;
	CreateQuadMesh(SHRINE_WIDTH, SHRINE_HEIGHT, Color(1, 1, 0, 1), shrineMesh);
	CreateQuadMesh(LOADING_WIDTH, LOADING_HEIGHT, Color(0, 0, 0, 1), loadingBarMesh);
	for (int i = 0; i < Shrine_Count; i++)
	{
		
		pool.Shrines[i].hasBeenUsed = false;
		pool.Shrines[i].transform.height = SHRINE_HEIGHT;
		pool.Shrines[i].transform.width = SHRINE_WIDTH;
		pool.Shrines[i].transform.mesh = &shrineMesh;
		pool.Shrines[i].loading.mesh = &loadingBarMesh;
		pool.activeShrine[i] = &pool.Shrines[i];
		//pool.activeShrine[i]->loadingbarpercentage = 0.f;
		pool.activeShrine[i]->timeElapsed = 0;
		pool.activeShrine[i]->isColliding = false;

	}
	assetFreeze = AEGfxTextureLoad("Assets/Freeze.png");
	assetHeal = AEGfxTextureLoad("Assets/Health.png");
	assetWind = AEGfxTextureLoad("Assets/Wind.png");
	assetExplosion = AEGfxTextureLoad("Assets/Explosion.png");
	assetGod = AEGfxTextureLoad("Assets/God.png");
	assetVoid = AEGfxTextureLoad("Assets/Void.png");


}

float Vector_2Distance(const Vector2& a, const Vector2& b)
{
	float dx = b.x - a.x;
	float dy = b.y - a.y;
	return sqrt(dx * dx + dy * dy);
}

bool Check_Overlap_With_Active_Shrines(const ShrinePool& shrinePool, const Vector2& position)
{
	for (int i = 0; i < Shrine_Count; i++)
	{
		if (shrinePool.activeShrine[i]->hasBeenUsed && Vector_2Distance(shrinePool.activeShrine[i]->transform.position, position) < 100.0f)
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

void Shrine_Add(ShrinePool& shrinePool)
{
	if (!IsTime_Paused())
	{
		for (int i = 0; i < Shrine_Count; i++)
		{
			if (shrinePool.activeShrine[i]->hasBeenUsed == false)
			{
				shrinePool.activeShrine[i]->hasBeenUsed = true;
				shrinePool.activeSize += 1;

				// Generate a random position until it doesn't overlap with any active shrines
				Vector2 randomPosition;
				do
				{
					randomPosition = RandomPoint_OutsideSqaure(1, AEGetWindowHeight() / 2.f, Vector2(0, 0));
				} while (Check_Overlap_With_Active_Shrines(shrinePool, randomPosition));

				shrinePool.activeShrine[i]->transform.position = randomPosition;
				shrinePool.Shrines[i].loading.position = randomPosition;
				shrinePool.activeShrine[i]->timeElapsed = 0;
				shrinePool.activeShrine[i]->isColliding = false;
				shrinePool.activeShrine[i]->transform.scale = { 2, 2 };
				shrinePool.activeShrine[i]->types = static_cast<Shrine::Types>(Random(0, Shrine::TotalShrines - 1));

				// Set the texture of the shrine based on its type
				switch (shrinePool.activeShrine[i]->types)
				{
				case Shrine::Freeze:
					shrinePool.activeShrine[i]->transform.texture = &assetFreeze;
					break;

				case Shrine::Heal:
					shrinePool.activeShrine[i]->transform.texture = &assetHeal;
					break;

				case Shrine::Push:
					shrinePool.activeShrine[i]->transform.texture = &assetWind;
					break;

				case Shrine::Explosion:
					shrinePool.activeShrine[i]->transform.texture = &assetExplosion;
					break;

				case Shrine::God:
					shrinePool.activeShrine[i]->transform.texture = &assetGod;
					break;

				case Shrine::Void:
					shrinePool.activeShrine[i]->transform.texture = &assetVoid;
					break;
				}

				//std::cout << "Random shrine type: " << shrinePool.activeShrine[i]->types << std::endl;
				break;
			}
		}
	}
}



void Shrine_Delete(int index, ShrinePool& shrinePool)
{
	shrinePool.activeShrine[index]->hasBeenUsed = false;
	if (index < (shrinePool.activeSize - 1))
	{
		Shrine* temp = shrinePool.activeShrine[index];
		shrinePool.activeShrine[index] = shrinePool.activeShrine[shrinePool.activeSize - 1];
		shrinePool.activeShrine[shrinePool.activeSize - 1] = temp;
	}
	shrinePool.activeSize -= 1;
}

void Shrine_Update(ShrinePool& shrinePool, SamuraiPool& samPool, ArcherPool& archPool, NinjaPool &ninPool, Player& player, PlayerInfo& playerInfo, ExplosionPool& explosionPool, VoidPool& voidPool, CannoneerPool& canPool)
{
	duration += deltaTime;
	//std::cout << duration << std::endl;
	AEInputGetCursorPosition(mouseX, mouseY);
	*mouseX = *mouseX - 800;
	*mouseY = (*mouseY - 450) * -1;

	if (duration >= 1.f)
	{
		duration = 0;
		Shrine_Add(shrinePool);

	}

	timeSincePause += deltaTime;
	for (int i = 0; i < shrinePool.activeSize; i++)
	{
		SetQuadPoints(shrinePool.activeShrine[i]->transform);
		if (StaticCol_QuadQuad(shrinePool.activeShrine[i]->transform, player.transform))
		{
			shrinePool.activeShrine[i]->isColliding = true;
			shrinePool.activeShrine[i]->timeElapsed += deltaTime;
			if (shrinePool.activeShrine[i]->timeElapsed >= 2.f)
			{
				// Explosion shrine
				if (shrinePool.activeShrine[i]->types == Shrine::Explosion)
				{
					AEAudioPlay(explosionSound, mainsceneAudioGroup, 1.f, 1.f, 0);
					for (int l = 0; l < Explosion_Count; l++)
					{
						Explosion_Add(explosionPool);
					}
					Explosion_Update(explosionPool, archPool, canPool, ninPool);
					Shrine_Delete(i, shrinePool);
					break;
				}

				// Void shrine
				if (shrinePool.activeShrine[i]->types == Shrine::Void)
				{
					AEAudioPlay(voidSound, mainsceneAudioGroup, 0.5f, 1.f, 0);
					for (int k = 0; k < Void_Count; k++)
					{
						Void_Add(voidPool);
					}
					Void_Update(voidPool, samPool, archPool, canPool);
					Shrine_Delete(i, shrinePool);
					break;
				}

				// Freeze shrine
				if (shrinePool.activeShrine[i]->types == Shrine::Freeze)
				{
					AEAudioPlay(freezeSound, mainsceneAudioGroup, 0.5f, 1.f, 0);
					TimePauseEnemy();
					timeSincePause = 0.0f;
					Shrine_Delete(i, shrinePool);
				//std::cout << "Freeze tower" << std::endl;
					break;
				}

				// Push shrine
				if (shrinePool.activeShrine[i]->types == Shrine::Push)
				{
					AEAudioPlay(windSound, mainsceneAudioGroup, 1.f, 1.f, 0);
					Push_Enemies(samPool, archPool, HORIZONTAL, PUSH_BY, ninPool);
					Shrine_Delete(i, shrinePool);
					//std::cout << "Push tower" << std::endl;
					break;
				}

				// Heal shrine
				if (shrinePool.activeShrine[i]->types == Shrine::Heal)
				{
					if (playerInfo.health < 100) {
						AEAudioPlay(healthSound, mainsceneAudioGroup, 1.f, 1.f, 0);
						Heal_player(playerInfo);
						Shrine_Delete(i, shrinePool);
						//std::cout << "Heal tower" << std::endl;
						std::cout << playerInfo.health << std::endl;
						break;
					}
				}

				// GOD shrine
				if (shrinePool.activeShrine[i]->types == Shrine::God)
				{
					int padding = 50;
					// Check if its samurai 
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

					// Check if its archers 
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

					// Check if its ninjas 
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

					// Check if its cannons
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
						Shrine_Delete(i, shrinePool);
					}
				}

			}
			else
			{

			    // loading bar for shrine
				for (int g = 0; g < shrinePool.activeSize; g++)
				{
					shrinePool.Shrines[g].loading.position = shrinePool.activeShrine[g]->transform.position + Vector2(0, 80);
					float loadingBarPercentage = shrinePool.activeShrine[g]->timeElapsed / 5.f;
					shrinePool.Shrines[g].loading.scale = Vector2(loadingBarPercentage, 1.0f);
				}

			}
		}
		else
		{
			shrinePool.activeShrine[i]->isColliding = false;
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

		if (shrinePool.activeShrine[i]->hasBeenUsed)
		{
			DrawMesh(&shrinePool.activeShrine[i]->transform);
			if (shrinePool.activeShrine[i]->isColliding)
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

	AEGfxTextureUnload(assetFreeze);
	AEGfxTextureUnload(assetHeal);
	AEGfxTextureUnload(assetWind);
	AEGfxTextureUnload(assetExplosion);
	AEGfxTextureUnload(assetVoid);
	AEGfxTextureUnload(assetGod); 
	
}