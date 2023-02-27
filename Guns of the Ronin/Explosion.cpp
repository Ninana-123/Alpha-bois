
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
		


	}

	
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
			explosionPool.activeExplosion[i]->transform.position = RandomPoint_OutsideSqaure(1, AEGetWindowHeight()/2.f, Vector2 (0,0));
			explosionPool.activeExplosion[i]->loading.position = explosionPool.activeExplosion[i]->transform.position;
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

void Explosion_Update(ExplosionPool& explosionPool, SamuraiPool& pool)
{
	
	
	durations += deltaTime;
	if (durations >= 100000.f)
	{
		durations = 0;
		ExplosionAdd(explosionPool);
	}

	for (int i = 0; i < explosionPool.activeSize; i++)
	{
		SetQuadPoints(explosionPool.activeExplosion[i]->transform, 40.f, 40.f);
		for (int j = 0; j < pool.activeSize; j++)
		{
			if (StaticCol_QuadQuad(explosionPool.activeExplosion[i]->transform, pool.activeSamurais[j]->transform))
			{
				explosionPool.activeExplosion[i]->iscolliding = true;
				explosionPool.activeExplosion[i]->timeElapsed += deltaTime;
				if (explosionPool.activeExplosion[i]->timeElapsed >= 1.f)
				{
					ExplosionDelete(i, explosionPool);
					SamuraiRemove(j, pool);
				}
				
				
			}
			else
			{
				explosionPool.activeExplosion[i]->iscolliding = false;
			}
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

void Free_Explosions() {
	AEGfxMeshFree(explosionsMesh);
	
}