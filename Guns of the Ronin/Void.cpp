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
@brief This file contains code that shows how would the void shrine work
*//*______________________________________________________________________*/
#include "Void.h"
#include "Graphics.h"
#include "DummyPlayer.h"
#include "Player.h"
#include "AEMath.h"
#include "TimeManager.h"
#include "Samurai.h"
#include "vector"


float durations;
void Void_PoolInit(VoidPool& voidPool)
{
	durations = 0;
	voidPool.activeSize = 0;
	CreateQuadMesh(VOID_WIDTH, VOID_HEIGHT, Color(1, 1, 0, 1), voidMesh, 1/4.0f ,1.0f);
	for (int i = 0; i < Void_Count; i++)
	{
		voidPool.Voids[i].hasBeenUsed = false;
		voidPool.Voids[i].transform.height = VOID_HEIGHT;
		voidPool.Voids[i].transform.width = VOID_WIDTH;
		voidPool.Voids[i].transform.mesh = &voidMesh;
		voidPool.activeVoid[i] = &voidPool.Voids[i];
		voidPool.activeVoid[i]->timeElapsed = 0;
		voidPool.activeVoid[i]->isColliding = false;
		voidPool.activeVoid[i]->transform.texture = &assetBlackHole;
		voidPool.activeVoid[i]->transform.scale = { 1.5,1.5 };
	}
	assetBlackHole = AEGfxTextureLoad("Assets/BlackholeSpriteSheet.png");

		
}


float Distance_Void(const Vector2& a, const Vector2& b)
{
	float dx = b.x - a.x;
	float dy = b.y - a.y;
	return sqrt(dx * dx + dy * dy);
}

bool Check_Overlap_With_Active_Void(const VoidPool& voidPool, const Vector2& position)
{
	for (int i = 0; i < Void_Count; i++)
	{
		if (voidPool.activeVoid[i]->hasBeenUsed && Distance_Void(voidPool.activeVoid[i]->transform.position, position) < 100.0f)
		{
			return true;
		}
	}

	return false;
}

void Void_Add(VoidPool& voidPool)
{
	for (int i = 0; i < Void_Count; i++)
	{
		if (voidPool.activeVoid[i]->hasBeenUsed == false)
		{
			if (voidPool.activeVoid[i]->isColliding == true) 
			{
				continue; // skip this explosion
			}
			voidPool.activeVoid[i]->hasBeenUsed = true;
			voidPool.activeSize += 1;

			// Generate a random position until it doesn't overlap with any active shrines
			Vector2 randomPosition;
			do
			{
				randomPosition = RandomPoint_OutsideSqaure(1, AEGetWindowHeight() / 2.f, Vector2(0, 0));
			} while (Check_Overlap_With_Active_Void(voidPool, randomPosition));
			voidPool.activeVoid[i]->transform.position = randomPosition;


			//voidPool.activeVoid[i]->transform.position = RandomPoint_OutsideSqaure(1, AEGetWindowHeight() / 2.f, Vector2(0, 0));
			//voidPool.activeVoid[i]->loading.position = voidPool.activeVoid[i]->transform.position;
			voidPool.activeVoid[i]->timeElapsed = 0;
			voidPool.activeVoid[i]->isColliding = false;
			break;
		}
	}
}

void Void_Delete(int index, VoidPool& voidPool)
{
	
		voidPool.activeVoid[index]->hasBeenUsed = false;
		if (index < (voidPool.activeSize - 1))
		{
			Void* temp = voidPool.activeVoid[index];
			voidPool.activeVoid[index] = voidPool.activeVoid[voidPool.activeSize - 1];
			voidPool.activeVoid[voidPool.activeSize - 1] = temp;
		}
		voidPool.activeSize -= 1;
	
}

void Void_Update(VoidPool& voidPool, SamuraiPool& samPool, ArcherPool& archPool, CannoneerPool& canPool)
{
	
	// Animation
	for (int i = 0; i < Void_Count; i++)
	{
		static float frameTimer = 0;
		frameTimer += deltaTime;
		if (frameTimer >= 0.3f) {
			voidPool.Voids[i].bgAnim.PlayAnim();
			voidPool.Voids[i].bgAnim.NextFrame(voidPool.Voids[i].transform);
			voidPool.Voids[i].bgAnim.Update_SpriteAnim(voidPool.Voids[i].transform);
			frameTimer = 0;
		}
	}

	// Loop through all active voids in the VoidPool
	for (int i = 0; i < voidPool.activeSize; i++)
	{
		voidPool.activeVoid[i]->timeElapsed += deltaTime;
		// Check for collision with enemies
		// Create empty vectors to store the indices of the collided enemies
		std::vector<int> collidedSamurais;
		std::vector<int> collidedCannoners;
		std::vector<int> collidedArchers;

		// Loop through all active samurais in the SamuraiPool
		for (int j = 0; j < samPool.activeSize; j++)
		{
			// Check if the void and the samurai intersect
			if (StaticCol_QuadQuad(voidPool.activeVoid[i]->transform, samPool.activeSamurais[j]->transform))
			{
				// If there is a collision, add the index of the collided samurai to the vector
				collidedSamurais.push_back(j);
			}
		}

		// Loop through all active cannoners in the CannonerPool
		for (int j = 0; j < canPool.activeSize; j++)
		{
			// Check if the void and the cannoner intersect
			if (StaticCol_QuadQuad(voidPool.activeVoid[i]->transform, canPool.activeCannoneers[j]->transform))
			{
				// If there is a collision, add the index of the collided cannoner to the vector
				collidedCannoners.push_back(j);
			}
		}

		// Loop through all active archers in the ArcherPool
		for (int j = 0; j < archPool.activeSize; j++)
		{
			// Check if the void and the archer intersect
			if (StaticCol_QuadQuad(voidPool.activeVoid[i]->transform, archPool.activeArchers[j]->transform))
			{
				// If there is a collision, add the index of the collided archer to the vector
				collidedArchers.push_back(j);
			}
		}

		// Remove the collided enemies outside of the inner loop
		// Loop backwards through the indices of the collided samurais
		for (int j = (int) collidedSamurais.size() - 1; j >= 0; j--)
		{
			// Remove the collided samurai from the SamuraiPool
			Remove_Samurai(collidedSamurais[j], samPool);
		}
		// Loop backwards through the indices of the collided cannoners
		for (int j = (int) collidedCannoners.size() - 1; j >= 0; j--)
		{
			// Remove the collided cannoner from the CannonerPool
			CannoneerRemove(collidedCannoners[j], canPool);
		}
		// Loop backwards through the indices of the collided archers
		for (int j = (int) collidedArchers.size() - 1; j >= 0; j--)
		{
			// Remove the collided archer from the ArcherPool
			Remove_Archer(collidedArchers[j], archPool);
		}

		// Remove the void if there are no collided samurais
		// If the vector of collided samurais is empty
		if (collidedSamurais.empty() && collidedCannoners.empty() && collidedArchers.empty())
		{
			// Check if the void has been active for more than 4 seconds else remove them
			if (voidPool.activeVoid[i]->timeElapsed >= 4.f)
			{
				// If the void has been active for more than 1 second, remove it from the VoidPool
				Void_Delete(i, voidPool);
			}
			else
			{
				// If the void has been active for less than 1 second, set its quad points
				//SetQuadPoints(voidPool.activeVoid[i]->transform, 40.f, 40.f);
				SetQuadPoints(voidPool.activeVoid[i]->transform);
			}
		}
		else
		{
			// If there are collided samurais, remove the void from the VoidPool
			Void_Delete(i, voidPool);
		}
	}
}
void Draw_Void(VoidPool& voidPool)
{
	for (int i = 0; i < voidPool.activeSize; i++)
	{

		if (voidPool.activeVoid[i]->hasBeenUsed)
		{
			DrawMesh(&voidPool.activeVoid[i]->transform);
			if (voidPool.activeVoid[i]->isColliding)
			{
				Void_Delete(i, voidPool);
			}
		}

	}
}

void Free_Void()
{
	
	AEGfxMeshFree(voidMesh);
	AEGfxTextureUnload(assetBlackHole);

}