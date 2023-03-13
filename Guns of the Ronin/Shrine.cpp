
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
	assetfreeze = AEGfxTextureLoad("Assets/Freeze.png");
	assetheal = AEGfxTextureLoad("Assets/Health.png");
	assetwind = AEGfxTextureLoad("Assets/Wind.png");
	assetgod = AEGfxTextureLoad("Assets/Freeze.png");
	assetexplosion = AEGfxTextureLoad("Assets/Explosion.png");
	assetgod = AEGfxTextureLoad("Assets/God.png");
	assetvoid = AEGfxTextureLoad("Assets/Void.png");


}


int Random(int min, int max)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(min, max);
	return dis(gen);
}

void ShrineAdd(ShrinePool& shrinePool)
{
	if (!IsTime_Paused()) {
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
				shrinePool.activeShrine[i]->transform.scale = { 2, 2 };

				shrinePool.activeShrine[i]->types = static_cast<Shrine::Types>(Random(0, Shrine::TotalShrines - 1));
				//arranges PNG image according to type of shrine
				if (shrinePool.activeShrine[i]->types == Shrine::Freeze)
				{
					shrinePool.activeShrine[i]->transform.texture = &assetfreeze;
				}

				else if (shrinePool.activeShrine[i]->types == Shrine::Heal)
				{
					shrinePool.activeShrine[i]->transform.texture = &assetheal;
				}

				if (shrinePool.activeShrine[i]->types == Shrine::Explosion)
				{
					shrinePool.activeShrine[i]->transform.texture = &assetexplosion;
				}

				if (shrinePool.activeShrine[i]->types == Shrine::God)
				{
					shrinePool.activeShrine[i]->transform.texture = &assetgod;
				}

				if (shrinePool.activeShrine[i]->types == Shrine::Void)
				{
					shrinePool.activeShrine[i]->transform.texture = &assetvoid;
				}
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

void Shrine_Update(ShrinePool& shrinePool, SamuraiPool& samPool, ArcherPool archPool, NinjaPool ninPool, Player& player, PlayerInfo& playerinfo, ExplosionPool& explosionPool, int index, VoidPool& voidPool, CannoneerPool& canPool)
{
	duration += deltaTime;
	//std::cout << duration << std::endl;
	AEInputGetCursorPosition(mouseX, mouseY);
	/**mouseX = *mouseX - 800;
	*mouseY = (*mouseY - 450) * -1;*/

	if (duration >= 1.f)
	{
		duration = 0;
		ShrineAdd(shrinePool);

	}

	Vector2 PositionMouse = Vector2(*mouseX >= HalfX ? *mouseX - HalfX : -(HalfX - *mouseX), *mouseY >= HalfY ? -(*mouseY - HalfY) : HalfY - *mouseY);
	timeSincePause += deltaTime;
	for (int i = 0; i < shrinePool.activeSize; i++)
	{
		SetQuadPoints(shrinePool.activeShrine[i]->transform, 40.f, 40.f);

		//if (shrinePool.activeShrine[i]->types == Shrine::God)
		//{
		//	for (int u = 0; u < samPool.activeSize; ++u)
		//	{
		//		if (IsButtonHover(samPool.activeSamurais[u]->transform.position.x, samPool.activeSamurais[u]->transform.position.y,
		//			samPool.activeSamurais[u]->transform.width *(samPool.activeSamurais[u]->transform.scale.x), 
		//			samPool.activeSamurais[u]->transform.height *(samPool.activeSamurais[u]->transform.scale.y), (s32*)&PositionMouse.x, (s32*)&PositionMouse.y))
		//		{
		//			//std::cout << "in" << std::endl;
		//			if (AEInputCheckTriggered(AEVK_LBUTTON))
		//			{
		//				//std::cout << "pressed" << std::endl;
		//				SamuraiRemove(u, samPool);
		//			}
		//		}
		//	}
		//}
		if (StaticCol_QuadQuad(shrinePool.activeShrine[i]->transform, player.transform))
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
					if (shrinePool.activeShrine[i]->types == Shrine::Freeze)
					{
						TimePauseEnemy();
						timeSincePause = 0.0f;
						ShrineDelete(i, shrinePool);
						std::cout << "Freeze tower" << std::endl;
					}
					Explosion_Update(explosionPool, archPool, canPool, ninPool);
					ShrineDelete(i, shrinePool);

				}

				if (shrinePool.activeShrine[i]->types == Shrine::Void)
				{
					for (int k = 0; k < Void_Count; k++)
					{
						Push_Enemies(samPool, archPool, HORIZONTAL, -500, ninPool);
						ShrineDelete(i, shrinePool);
						std::cout << "Push tower" << std::endl;
					}
					Void_Update(voidPool, samPool, archPool, canPool);
					ShrineDelete(i, shrinePool);

				}

				if (shrinePool.activeShrine[i]->types == Shrine::God)
				{
					for (int u = 0; u < samPool.activeSize; ++u)
					{
						/*if (IsButtonHover(samPool.activeSamurais[u]->transform.position.x, samPool.activeSamurais[u]->transform.position.y,
							samPool.activeSamurais[u]->transform.width, samPool.activeSamurais[u]->transform.height, mouseX, mouseY))
						{*/
						//std::cout << "in" << std::endl;
						if (AEInputCheckTriggered(AEVK_LBUTTON))
						{
							//std::cout << "pressed" << std::endl;
							SamuraiRemove(u, samPool);
						}
						//ShrineDelete(i, shrinePool);
					}
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

	//AEGfxTextureUnload(assetfreeze);
	//AEGfxTextureUnload(assetheal);
	//AEGfxTextureUnload(assetwind);
}