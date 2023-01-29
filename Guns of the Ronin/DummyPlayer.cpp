
#include "DummyPlayer.h"

// dvbdkvbvkfdabkakda
void DummyPlayer_Init(DummyPlayer* dummyPlayer) {
	dummyPlayer->transform.color = Color(1, 0, 0, 1);
	CreateQuadMesh(30.0f, 30.0f, dummyPlayer->transform.color,dummyPlayer->transform);

	// Set the texture
	dummyPlayer->transform.texture = AEGfxTextureLoad("Assets/PlanetTexture.png");
}

void DummyPlayer_Update(DummyPlayer* dummyPlayer) {


	dummyPlayer->w_Pressed = AEInputCheckCurr(AEVK_W);
	dummyPlayer->a_Pressed = AEInputCheckCurr(AEVK_A);
	dummyPlayer->s_Pressed = AEInputCheckCurr(AEVK_S);
	dummyPlayer->d_Pressed = AEInputCheckCurr(AEVK_D);

	Vector2 newPos{ };
	float deltaTime = (float)AEFrameRateControllerGetFrameTime();
	if (dummyPlayer->w_Pressed) {
		newPos.y = dummyPlayer->moveSpeed * deltaTime;
	}
	if (dummyPlayer->a_Pressed) {
		newPos.x = -dummyPlayer->moveSpeed * deltaTime;
	}
	if (dummyPlayer->s_Pressed) {
		newPos.y = -dummyPlayer->moveSpeed * deltaTime;
	}
	if (dummyPlayer->d_Pressed) {
		newPos.x = dummyPlayer->moveSpeed * deltaTime;
	}

	dummyPlayer->transform.position += newPos;

	DrawMesh(&dummyPlayer->transform);
}
