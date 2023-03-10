
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
	//if (IsExplosionTriggered())
	//{
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
	//}
}

void ExplosionAdd(ExplosionPool& explosionPool)
{
	//if (IsExplosionTriggered())
	//{
	for (int i = 0; i < Explosion_Count; i++)
	{
		if (explosionPool.activeExplosion[i]->hasbeenused == false)
	{
			if (explosionPool.activeExplosion[i]->iscolliding == true) {
				continue; // skip this explosion
			}
			explosionPool.activeExplosion[i]->hasbeenused = true;
			explosionPool.activeSize += 1;
			explosionPool.activeExplosion[i]->transform.position = RandomPoint_OutsideSqaure(1, AEGetWindowHeight() / 2.f, Vector2(0, 0));
			explosionPool.activeExplosion[i]->loading.position = explosionPool.activeExplosion[i]->transform.position;
			explosionPool.activeExplosion[i]->timeElapsed = 0;
			explosionPool.activeExplosion[i]->iscolliding = false;
			break;
		}
		}
	//}
}

void ExplosionDelete(int index, ExplosionPool& explosionPool)
{
	if (IsExplosionTriggered())
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
}

void Explosion_Update(ExplosionPool& explosionPool, SamuraiPool& pool)
{
	//if (IsExplosionTriggered())
	//{
		/*durations += deltaTime;
		if (durations >= 1.f)
		{
			durations = 0;
			ExplosionAdd(explosionPool);
		}*/
	if (explosionCount < Explosion_Count)
	{

		for (int i = 0; i < explosionPool.activeSize; i++)
		{
			/*if (explosionPool.activeExplosion[i]->timeElapsed >= 1.f)
			{
				ExplosionDelete(i, explosionPool);
			}*/
			SetQuadPoints(explosionPool.activeExplosion[i]->transform, 40.f, 40.f);
			for (int j = 0; j < pool.activeSize; j++)
			{
				if (StaticCol_QuadQuad(explosionPool.activeExplosion[i]->transform, pool.activeSamurais[j]->transform))
				{
					if (!pool.activeSamurais[j]->damagedByExplosion)
					{
						pool.activeSamurais[j]->health -= 50;
						pool.activeSamurais[j]->damagedByExplosion = true;
						std::cout << "Health:" << pool.activeSamurais[j]->health << std::endl;
						if (pool.activeSamurais[j]->health <= 0) {
							SamuraiRemove(j, pool);
						}
					}
					pool.activeSamurais[j]->isCollidingWithExplosion = true;
				}
			}
		}

		for (int j = 0; j < pool.activeSize; j++)
		{
			pool.activeSamurais[j]->isCollidingWithExplosion = false;
			for (int i = 0; i < explosionPool.activeSize; i++)
			{
				if (StaticCol_QuadQuad(pool.activeSamurais[j]->transform, explosionPool.activeExplosion[i]->transform))
				{
					pool.activeSamurais[j]->isCollidingWithExplosion = true;
					ExplosionDelete(i, explosionPool);
				}
			}
			if (!pool.activeSamurais[j]->isCollidingWithExplosion && pool.activeSamurais[j]->damagedByExplosion)
			{
				pool.activeSamurais[j]->damagedByExplosion = false;
			}
		}
	}
	//}
}

void Draw_Explosions(ExplosionPool& explosionPool)
{
	//if (IsExplosionTriggered())
	//{
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
	//}
}

void Free_Explosions() {
	//if (IsExplosionTriggered())
	//{
		AEGfxMeshFree(explosionsMesh);
	//}
}