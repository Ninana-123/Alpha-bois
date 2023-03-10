
#include "Void.h"
#include "Graphics.h"
#include "DummyPlayer.h"
#include "Player.h"
#include "AEMath.h"
#include "TimeManager.h"
#include "Samurai.h"
#include "vector"

float Durations;

void Voidpool_Init(VoidPool& voidPool)
{
			Durations = 0;
			voidPool.activeSize = 0;
			CreateQuadMesh(VOID_WIDTH, VOID_HEIGHT, Color(1, 1, 0, 1), voidMesh);
			for (int i = 0; i < Void_Count; i++)
			{
				voidPool.Voids[i].hasbeenused = false;
				voidPool.Voids[i].transform.height = VOID_HEIGHT;
				voidPool.Voids[i].transform.width = VOID_WIDTH;
				voidPool.Voids[i].transform.mesh = &voidMesh;
				voidPool.activeVoid[i] = &voidPool.Voids[i];
				voidPool.activeVoid[i]->timeElapsed = 0;
				voidPool.activeVoid[i]->iscolliding = false;
				voidPool.activeVoid[i]->transform.texture = &assetblackhole;
				voidPool.activeVoid[i]->transform.scale = { 1,1 };
			}
			assetblackhole = AEGfxTextureLoad("Assets/Blackhole1.png");

		
}

void VoidAdd(VoidPool& voidPool)
{
	for (int i = 0; i < Void_Count; i++)
	{
		if (voidPool.activeVoid[i]->hasbeenused == false)
		{
			if (voidPool.activeVoid[i]->iscolliding == true) 
			{
				continue; // skip this explosion
			}
			voidPool.activeVoid[i]->hasbeenused = true;
			voidPool.activeSize += 1;
			voidPool.activeVoid[i]->transform.position = RandomPoint_OutsideSqaure(1, AEGetWindowHeight() / 2.f, Vector2(0, 0));
			voidPool.activeVoid[i]->loading.position = voidPool.activeVoid[i]->transform.position;
			voidPool.activeVoid[i]->timeElapsed = 0;
			voidPool.activeVoid[i]->iscolliding = false;
			break;
		}
	}
}

void VoidDelete(int index, VoidPool& voidPool)
{
	
		voidPool.activeVoid[index]->hasbeenused = false;
		if (index < (voidPool.activeSize - 1))
		{
			Void* temp = voidPool.activeVoid[index];
			voidPool.activeVoid[index] = voidPool.activeVoid[voidPool.activeSize - 1];
			voidPool.activeVoid[voidPool.activeSize - 1] = temp;
		}
		voidPool.activeSize -= 1;
	
}

void Void_Update(VoidPool& voidPool, SamuraiPool& samPool, ArcherPool& archPool)
{
	
		/*Durations += deltaTime;
		if (Durations >= 1.f)
		{
			Durations = 0;
			VoidAdd(voidPool);
		}*/
		/*if (voidCount < Void_Count)
		{*/

		// Loop through all active voids in the VoidPool
	for (int i = 0; i < voidPool.activeSize; i++)
	{
		// Check for collision with samurais
		// Create an empty vector to store the indices of the collided samurais
		std::vector<int> collidedSamurais;
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

		// Remove the collided samurais outside of the inner loop
		// Loop backwards through the indices of the collided samurais
		for (int j = collidedSamurais.size() - 1; j >= 0; j--)
		{
			// Remove the collided samurai from the SamuraiPool
			SamuraiRemove(collidedSamurais[j], samPool);
		}

		// Remove the void if there are no collided samurais
		// If the vector of collided samurais is empty
		if (collidedSamurais.empty())
		{
			// Check if the void has been active for more than 1 second
			if (voidPool.activeVoid[i]->timeElapsed >= 1.f)
			{
				// If the void has been active for more than 1 second, remove it from the VoidPool
				VoidDelete(i, voidPool);
			}
			else
			{
				// If the void has been active for less than 1 second, set its quad points
				SetQuadPoints(voidPool.activeVoid[i]->transform, 40.f, 40.f);
			}
		}
		else
		{
			// If there are collided samurais, remove the void from the VoidPool
			VoidDelete(i, voidPool);
		}
	}

//}
}
void Draw_Void(VoidPool& voidPool)
{
	//if (IsExplosionTriggered())
	//{
		for (int i = 0; i < voidPool.activeSize; i++)
		{

			if (voidPool.activeVoid[i]->hasbeenused)
			{
				DrawMesh(&voidPool.activeVoid[i]->transform);
				if (voidPool.activeVoid[i]->iscolliding)
				{
					VoidDelete(i, voidPool);
				}
			}

		}
	
}

void Free_Void()
{
	
		AEGfxMeshFree(voidMesh);

}