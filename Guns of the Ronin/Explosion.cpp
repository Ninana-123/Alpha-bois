/*
\copyright
		All content(C) 2023 DigiPen Institute of Technology Singapore.All rights
		reserved.Reproduction or disclosure of this file or its contents without the prior
		written consent of DigiPen Institute of Technology is prohibited.
*/
/*!
@file void.cpp
@author Teo Sheen Yeoh
@Email t.sheenyeoh@digipen.edu
@course CSD 1450
@section Section A
@date 3 March 2023
@brief This file contains code for the credit screen.
*//*______________________________________________________________________*/
#include "Explosion.h"
#include "Graphics.h"
#include "DummyPlayer.h"
#include "Player.h"
#include "AEMath.h"
#include "TimeManager.h"
#include "Samurai.h"

float durations;
void Explosionpool_Init(ExplosionPool& explosionPool)
{
		{
			durations = 0;
			explosionPool.activeSize = 0;
			CreateQuadMesh(EXPLOSION_WIDTH, EXPLOSION_HEIGHT, Color(1, 0, 0, 1), explosionsMesh);
			for (int i = 0; i < Explosion_Count; i++)
			{
				explosionPool.Explosions[i].hasbeenused = false;
				explosionPool.Explosions[i].transform.height = EXPLOSION_HEIGHT;
				explosionPool.Explosions[i].transform.width = EXPLOSION_WIDTH;
				explosionPool.Explosions[i].transform.mesh = &explosionsMesh;
				explosionPool.activeExplosion[i] = &explosionPool.Explosions[i];
				explosionPool.activeExplosion[i]->timeElapsed = 0;
				explosionPool.activeExplosion[i]->iscolliding = false;
				explosionPool.activeExplosion[i]->transform.texture = &assetexplosions;
				explosionPool.activeExplosion[i]->transform.scale = { 1.5,1.5 };
			}
			assetexplosions = AEGfxTextureLoad("Assets/Explosions.png");
		}
}

float DistanceExplosion(const Vector2& a, const Vector2& b)
{
	float dx = b.x - a.x;
	float dy = b.y - a.y;
	return sqrt(dx * dx + dy * dy);
}

bool CheckOverlapWithActiveExplosion(const ExplosionPool& explosionPool, const Vector2& position)
{
	for (int i = 0; i < Explosion_Count; i++)
	{
		if (explosionPool.activeExplosion[i]->hasbeenused && DistanceExplosion(explosionPool.activeExplosion[i]->transform.position, position) < 100.0f)
		{
			return true;
		}
	}

	return false;
}

void ExplosionAdd(ExplosionPool& explosionPool)
{
	for (int i = 0; i < Explosion_Count; i++)
	{
		if (explosionPool.activeExplosion[i]->hasbeenused == false)
	{
			if (explosionPool.activeExplosion[i]->iscolliding == true) {
				continue; // skip this explosion
			}
			explosionPool.activeExplosion[i]->hasbeenused = true;
			explosionPool.activeSize += 1;

			// Generate a random position until it doesn't overlap with any active shrines
			Vector2 randomPosition;
			do
			{
				randomPosition = RandomPoint_OutsideSqaure(1, AEGetWindowHeight() / 2.f, Vector2(0, 0));
			} while (CheckOverlapWithActiveExplosion(explosionPool, randomPosition));
			explosionPool.activeExplosion[i]->transform.position = randomPosition;
			
			explosionPool.activeExplosion[i]->timeElapsed = 0;
			explosionPool.activeExplosion[i]->iscolliding = false;
			break;
		}
		}
	
}

void ExplosionDelete(int index, ExplosionPool& explosionPool)
{
		explosionPool.activeExplosion[index]->hasbeenused = false;
		if (index < (explosionPool.activeSize - 1))
		{
			Explosion* temp = explosionPool.activeExplosion[index];
			explosionPool.activeExplosion[index] = explosionPool.activeExplosion[explosionPool.activeSize - 1];
			explosionPool.activeExplosion[explosionPool.activeSize - 1] = temp;
		}
		explosionPool.activeSize -= 1;
	
}

void Explosion_Update(ExplosionPool& explosionPool, ArcherPool& archPool, CannoneerPool& canPool, NinjaPool& ninPool)
{
		

	// Loop over all active explosions in the explosion pool
	for (int i = 0; i < explosionPool.activeSize; i++)
	{
		SetQuadPoints(explosionPool.activeExplosion[i]->transform);

		// Loop over all active archers in the archer pool
		for (int j = 0; j < archPool.activeSize; j++)
		{
			// Check for collision between the explosion and the archer
			if (StaticCol_QuadQuad(explosionPool.activeExplosion[i]->transform, archPool.activeArchers[j]->transform))
			{
				// If the archer has not already been damaged by this explosion, subtract health
				if (!archPool.activeArchers[j]->damagedByExplosion)
				{
					archPool.activeArchers[j]->health -= 50;
					archPool.activeArchers[j]->damagedByExplosion = true;
					//std::cout << "Health:" << archPool.activeArchers[j]->health << std::endl;
					// If the archer's health is now zero or less, remove it from the pool
					if (archPool.activeArchers[j]->health <= 0) 
					{
						ArcherRemove(j, archPool);
					}
				}
				archPool.activeArchers[j]->isCollidingWithExplosion = true;
			}
		}
			
		for (int z = 0; z < canPool.activeSize; z++)
		{
			if (StaticCol_QuadQuad(explosionPool.activeExplosion[i]->transform, canPool.activeCannoneers[z]->transform))
			{
				if (!canPool.activeCannoneers[z]->damagedByExplosion)
				{
					canPool.activeCannoneers[z]->health -= 50;
					canPool.activeCannoneers[z]->damagedByExplosion = true;
					//std::cout << "Health:" << canPool.activeArchers[j]->health << std::endl;
					if (canPool.activeCannoneers[z]->health <= 0)
					{
						CannoneerRemove(z, canPool);
					}
				}
				canPool.activeCannoneers[z]->isCollidingWithExplosion = true;
			}
		}
			
		for (int k = 0; k < ninPool.activeSize; k++)
		{
			if (StaticCol_QuadQuad(explosionPool.activeExplosion[i]->transform, ninPool.activeNinjas[k]->transform))
			{
				if (!ninPool.activeNinjas[k]->damagedByExplosion)
				{
					ninPool.activeNinjas[k]->health -= 50;
					ninPool.activeNinjas[k]->damagedByExplosion = true;
					//std::cout << "Health:" << ninPool.activeNinjas[k]->health << std::endl;
					if (ninPool.activeNinjas[k]->health <= 0)
					{
						NinjaRemove(k, ninPool);
					}
				}
				ninPool.activeNinjas[k]->isCollidingWithExplosion = true;
			}
		}
		// Removing the explosion after 4 seconds 
		explosionPool.activeExplosion[i]->timeElapsed += deltaTime;
		if (explosionPool.activeExplosion[i]->timeElapsed >= 4.0f)
		{
			ExplosionDelete(i, explosionPool);
		}
	}

	for (int j = 0; j < archPool.activeSize; j++)
	{
		archPool.activeArchers[j]->isCollidingWithExplosion = false;
		for (int i = 0; i < explosionPool.activeSize; i++)
		{
			if (StaticCol_QuadQuad(archPool.activeArchers[j]->transform, explosionPool.activeExplosion[i]->transform))
			{
				archPool.activeArchers[j]->isCollidingWithExplosion = true;
				ExplosionDelete(i, explosionPool);
			}
		}
		if (!archPool.activeArchers[j]->isCollidingWithExplosion && archPool.activeArchers[j]->damagedByExplosion)
		{
			archPool.activeArchers[j]->damagedByExplosion = false;
		}

	}

	for (int z= 0; z < canPool.activeSize; z++)
	{
		canPool.activeCannoneers[z]->isCollidingWithExplosion = false;
		for (int i = 0; i < explosionPool.activeSize; i++)
		{
			if (StaticCol_QuadQuad(canPool.activeCannoneers[z]->transform, explosionPool.activeExplosion[i]->transform))
			{
				canPool.activeCannoneers[z]->isCollidingWithExplosion = true;
				ExplosionDelete(i, explosionPool);
			}
		}
		if (!canPool.activeCannoneers[z]->isCollidingWithExplosion && canPool.activeCannoneers[z]->damagedByExplosion)
		{
			canPool.activeCannoneers[z]->damagedByExplosion = false;
		}
	}

	for (int k = 0; k < ninPool.activeSize; k++)
	{
		ninPool.activeNinjas[k]->isCollidingWithExplosion = false;
		for (int i = 0; i < explosionPool.activeSize; i++)
		{
			if (StaticCol_QuadQuad(ninPool.activeNinjas[k]->transform, explosionPool.activeExplosion[i]->transform))
			{
				ninPool.activeNinjas[k]->isCollidingWithExplosion = true;
				ExplosionDelete(i, explosionPool);
			}
		}
		if (!ninPool.activeNinjas[k]->isCollidingWithExplosion && ninPool.activeNinjas[k]->damagedByExplosion)
		{
			ninPool.activeNinjas[k]->damagedByExplosion = false;
		}

	}
	
}

void Draw_Explosions(ExplosionPool& explosionPool)
{
	for (int i = 0; i < explosionPool.activeSize; i++)
	{

		if (explosionPool.activeExplosion[i]->hasbeenused)
		{
			DrawMesh(&explosionPool.activeExplosion[i]->transform);
			if (explosionPool.activeExplosion[i]->iscolliding)
			{
				ExplosionDelete(i, explosionPool);
			}
		}
	}
}

void Free_Explosions()
{
	
		AEGfxMeshFree(explosionsMesh);
		AEGfxTextureUnload(assetexplosions);
	
}