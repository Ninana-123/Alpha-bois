
#include "draw_shrine.h"
#include "Graphics.h"

void Draw_Shrine_Init(Shrine* Shrines)
{
	Shrines -> transform.color = Color(1, 1, 0, 1);
	Shrines -> transform.mesh = CreateQuadMesh(40.0f, 40.0f, Shrines->transform.color);
	Shrines->transform.position = Vector2(150.f, 150.f);

}
//ASBVIJASBJILBLFBASBFASB
// BIASBIASJBFJI;ASBF;ASBGBI;ASBG;ASBG;BASGBAGAS

void Draw_Shrine_Update(Shrine* Shrines)
{
	
	DrawMesh(&Shrines -> transform);
}

void Draw_Shrine_Exit()
{

}