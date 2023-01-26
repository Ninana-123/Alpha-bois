
#include "draw_shrine.h"
#include "Graphics.h"
#include <chrono>

void Draw_Shrine_Init(Shrine* Shrines)
{
	Shrines -> transform.color = Color(1, 1, 0, 1);
	CreateQuadMesh(40.0f, 40.0f, Shrines->transform.color, Shrines->transform);
	Shrines->transform.position = Vector2(150.f, 150.f);

}

void Draw_Shrine_Update(Shrine* Shrines)
{
	//set upper bound and lower bound 
	int ubx = AEGfxGetWinMaxX();
	int uby = AEGfxGetWinMaxY();
	int lbx = AEGfxGetWinMinX();
	int lby = AEGfxGetWinMinY();

	//Vector2 newpos{};
	////randomize x and y values withing the set bounds
	//newpos.x = rand() % (ubx - lbx + 1) + lbx;
	//newpos.y = rand() % (uby - lby + 1) + lby;
	//Shrines->transform.position = newpos;

	float timer = 0.0f;
	float deltatime = (float)AEFrameRateControllerGetFrameTime();
	timer += deltatime;
		Vector2 newpos{};
		//randomize x and y values withing the set bounds
		newpos.x = rand() % (ubx - lbx + 1) + lbx;
		newpos.y = rand() % (uby - lby + 1) + lby;
		Shrines->transform.position = newpos;
		DrawMesh(&Shrines->transform);
		timer = 0.0f;
}