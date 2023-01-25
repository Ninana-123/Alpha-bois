#include "Graphics.h"
#include "Shop.h"

void LoadShop(Shop *shop) {
	shop->transform.color = Color(1, 1, 0, 1);
	shop->transform.mesh = CreateQuadMesh(40.0f, 40.0f, shop->transform.color);
	shop->transform.position = Vector2(150.f, 150.f);
}
