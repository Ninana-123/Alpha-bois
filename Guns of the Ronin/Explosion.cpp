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
@brief This file contains code on how would the explosions shrine work 
*//*______________________________________________________________________*/
#include "Explosion.h"
#include "Graphics.h"
#include "DummyPlayer.h"
#include "Player.h"
#include "AEMath.h"
#include "TimeManager.h"
#include "Samurai.h"

float timing;
void Explosion_PoolInit(ExplosionPool& explosionPool)
{
		{
			timing = 0;
			explosionPool.activeSize = 0;
			Create_QuadMesh(EXPLOSION_WIDTH, EXPLOSION_HEIGHT, Color(1, 0, 0, 1), explosionsMesh);
			for (int i = 0; i < EXPLOSION_COUNT; i++)
			{
				explosionPool.Explosions[i].hasBeenUsed = false;
				explosionPool.Explosions[i].transform.height = EXPLOSION_HEIGHT;
				explosionPool.Explosions[i].transform.width = EXPLOSION_WIDTH;
				explosionPool.Explosions[i].transform.mesh = &explosionsMesh;
				explosionPool.activeExplosion[i] = &explosionPool.Explosions[i];
				explosionPool.activeExplosion[i]->timeElapsed = 0;
				explosionPool.activeExplosion[i]->isColliding = false;
				explosionPool.activeExplosion[i]->transform.texture = &assetExplosions;
				explosionPool.activeExplosion[i]->transform.scale = { 1.5,1.5 };
			}
			assetExplosions = AEGfxTextureLoad("Assets/Explosions.png");
		}
}

float Distance_Explosion(const Vector2& a, const Vector2& b)
{
	float dx = b.x - a.x;
	float dy = b.y - a.y;
	return sqrt(dx * dx + dy * dy);
}

bool Check_Overlap_With_Active_Explosion(const ExplosionPool& explosionPool, const Vector2& position)
{
	for (int i = 0; i < EXPLOSION_COUNT; i++)
	{
		if (explosionPool.activeExplosion[i]->hasBeenUsed && Distance_Explosion(explosionPool.activeExplosion[i]->transform.position, position) < 100.0f)
		{
			return true;
		}
	}

	return false;
}

void Explosion_Add(ExplosionPool& explosionPool)
{
	for (int i = 0; i < EXPLOSION_COUNT; i++)
	{
		if (explosionPool.activeExplosion[i]->hasBeenUsed == false)
	{
			if (explosionPool.activeExplosion[i]->isColliding == true) {
				continue; // skip this explosion
			}
			explosionPool.activeExplosion[i]->hasBeenUsed = true;
			explosionPool.activeSize += 1;

			// Generate a random position until it doesn't overlap with any active shrines
			Vector2 randomPosition;
			do
			{
				randomPosition = Random_PointOutsideSquare(1, AEGetWindowHeight() / 2.f, Vector2(0, 0));
			} while (Check_Overlap_With_Active_Explosion(explosionPool, randomPosition));
			explosionPool.activeExplosion[i]->transform.position = randomPosition;
			
			explosionPool.activeExplosion[i]->timeElapsed = 0;
			explosionPool.activeExplosion[i]->isColliding = false;
			break;
		}
		}
	
}

void Explosion_Delete(int index, ExplosionPool& explosionPool)
{
		explosionPool.activeExplosion[index]->hasBeenUsed = false;
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
		Set_QuadPoints(explosionPool.activeExplosion[i]->transform);

		// Loop over all active archers in the archer pool
		for (int j = 0; j < archPool.activeSize; j++)
		{
			// Check for collision between the explosion and the archer
			if (Col_StaticQuadQuad(explosionPool.activeExplosion[i]->transform, archPool.activeArchers[j]->transform))
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
						Remove_Archer(j, archPool);
					}
				}
				archPool.activeArchers[j]->isCollidingWithExplosion = true;
			}
		}
			
		for (int z = 0; z < canPool.activeSize; z++)
		{
			if (Col_StaticQuadQuad(explosionPool.activeExplosion[i]->transform, canPool.activeCannoneers[z]->transform))
			{
				if (!canPool.activeCannoneers[z]->damagedByExplosion)
				{
					canPool.activeCannoneers[z]->health -= 50;
					canPool.activeCannoneers[z]->damagedByExplosion = true;
					//std::cout << "Health:" << canPool.activeArchers[j]->health << std::endl;
					if (canPool.activeCannoneers[z]->health <= 0)
					{
						Remove_Cannoneer(z, canPool);
					}
				}
				canPool.activeCannoneers[z]->isCollidingWithExplosion = true;
			}
		}
			
		for (int k = 0; k < ninPool.activeSize; k++)
		{
			if (Col_StaticQuadQuad(explosionPool.activeExplosion[i]->transform, ninPool.activeNinjas[k]->transform))
			{
				if (!ninPool.activeNinjas[k]->damagedByExplosion)
				{
					ninPool.activeNinjas[k]->health -= 50;
					ninPool.activeNinjas[k]->damagedByExplosion = true;
					//std::cout << "Health:" << ninPool.activeNinjas[k]->health << std::endl;
					if (ninPool.activeNinjas[k]->health <= 0)
					{
						Remove_Ninja(k, ninPool);
					}
				}
				ninPool.activeNinjas[k]->isCollidingWithExplosion = true;
			}
		}
		// Removing the explosion after 4 seconds 
		explosionPool.activeExplosion[i]->timeElapsed += deltaTime;
		if (explosionPool.activeExplosion[i]->timeElapsed >= 4.0f)
		{
			Explosion_Delete(i, explosionPool);
		}
	}

	//// Check if enemy is archers
	//for (int j = 0; j < archPool.activeSize; j++)
	//{
	//	archPool.activeArchers[j]->isCollidingWithExplosion = false;
	//	for (int i = 0; i < explosionPool.activeSize; i++)
	//	{
	//		if (Col_StaticQuadQuad(archPool.activeArchers[j]->transform, explosionPool.activeExplosion[i]->transform))
	//		{
	//			archPool.activeArchers[j]->isCollidingWithExplosion = true;
	//			Explosion_Delete(i, explosionPool);
	//		}
	//	}
	//	if (!archPool.activeArchers[j]->isCollidingWithExplosion && archPool.activeArchers[j]->damagedByExplosion)
	//	{
	//		archPool.activeArchers[j]->damagedByExplosion = false;
	//	}

	//}
	//// Check if enemy is cannons
	//for (int z= 0; z < canPool.activeSize; z++)
	//{
	//	canPool.activeCannoneers[z]->isCollidingWithExplosion = false;
	//	for (int i = 0; i < explosionPool.activeSize; i++)
	//	{
	//		if (Col_StaticQuadQuad(canPool.activeCannoneers[z]->transform, explosionPool.activeExplosion[i]->transform))
	//		{
	//			canPool.activeCannoneers[z]->isCollidingWithExplosion = true;
	//			Explosion_Delete(i, explosionPool);
	//		}
	//	}
	//	if (!canPool.activeCannoneers[z]->isCollidingWithExplosion && canPool.activeCannoneers[z]->damagedByExplosion)
	//	{
	//		canPool.activeCannoneers[z]->damagedByExplosion = false;
	//	}
	//}
	//// Check if enemy is ninjas
	//for (int k = 0; k < ninPool.activeSize; k++)
	//{
	//	ninPool.activeNinjas[k]->isCollidingWithExplosion = false;
	//	for (int i = 0; i < explosionPool.activeSize; i++)
	//	{
	//		if (Col_StaticQuadQuad(ninPool.activeNinjas[k]->transform, explosionPool.activeExplosion[i]->transform))
	//		{
	//			ninPool.activeNinjas[k]->isCollidingWithExplosion = true;
	//			Explosion_Delete(i, explosionPool);
	//		}
	//	}
	//	if (!ninPool.activeNinjas[k]->isCollidingWithExplosion && ninPool.activeNinjas[k]->damagedByExplosion)
	//	{
	//		ninPool.activeNinjas[k]->damagedByExplosion = false;
	//	}

	//}
	
}

void Draw_Explosions(ExplosionPool& explosionPool)
{
	for (int i = 0; i < explosionPool.activeSize; i++)
	{

		if (explosionPool.activeExplosion[i]->hasBeenUsed)
		{
			Draw_Mesh(&explosionPool.activeExplosion[i]->transform);
			if (explosionPool.activeExplosion[i]->isColliding)
			{
				Explosion_Delete(i, explosionPool);
			}
		}
	}
}

void Free_Explosions()
{
	
		AEGfxMeshFree(explosionsMesh);
		AEGfxTextureUnload(assetExplosions);
	
}