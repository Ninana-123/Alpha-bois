
#include "Player.h"


void Player_Init(Player* Player) {
	Player->transform.color = Color(1, 1, 1, 1);
	Player->transform.mesh = CreateQuadMesh(20.0f, 20.0f, Player->transform.color);
	Player->transform.position = Vector2(100.f, 100.f);
}

//void Player_Speed()
//{
//	AEVec2Set(pos, 0.0f, 0.0f);
//	AEVec2Set(vel, 0.0f, 0.0f);
//	AEVec2Set(acc, 0.0f, 0.0f);
//
//}


void Player_Update(Player* Player) {

	const float friction = 0.95f;
	Player->w_Pressed = AEInputCheckCurr(AEVK_W);
	Player->a_Pressed = AEInputCheckCurr(AEVK_A);
	Player->s_Pressed = AEInputCheckCurr(AEVK_S);
	Player->d_Pressed = AEInputCheckCurr(AEVK_D);
	

	Vector2 newPos{ };
	Vector2 vel{};
	Vector2 acc{};
	
	float deltaTime = (float)AEFrameRateControllerGetFrameTime();
	if (Player->w_Pressed) {
		newPos.y = Player->moveSpeed * deltaTime;
	}
	if (!Player->w_Pressed) {
		vel.y *= friction;
	}
	if (Player->a_Pressed) {
		newPos.x = -Player->moveSpeed * deltaTime;
	}
	if (Player->s_Pressed) {
		newPos.y = -Player->moveSpeed * deltaTime;
	}
	if (Player->d_Pressed) {
		newPos.x = Player->moveSpeed * deltaTime;
	}

	Player->transform.position += newPos;

	DrawMesh(&Player->transform);
}
