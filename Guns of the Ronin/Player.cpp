#include "Player.h"

struct Projectile {
	Vector2 position;
	Vector2 velocity;
	Vector2 accelration;
	Transform transform;
};
s32 mouseX, mouseY;

void Player_Init(Player* Player) {
	Player->transform.color = Color(1, 1, 1, 1);
	CreateQuadMesh(50.0f, 50.0f, Player->transform.color,Player->transform);
	Player->transform.position = Vector2(100.f, 100.f);
}



void Player_Update(Player* Player) {

	Vector2 newPos{ };
	Vector2 vel{ };
	Vector2 acc{ };
	const float friction = 0.95f;

	Player->w_Pressed = AEInputCheckCurr(AEVK_W);
	Player->a_Pressed = AEInputCheckCurr(AEVK_A);
	Player->s_Pressed = AEInputCheckCurr(AEVK_S);
	Player->d_Pressed = AEInputCheckCurr(AEVK_D);
	Player->right_mouse_pressed = AEInputCheckTriggered(AEVK_LBUTTON);




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
	if (!Player->a_Pressed) {
		vel.x *= friction;
	}
	if (Player->s_Pressed) {
		newPos.y = -Player->moveSpeed * deltaTime;
	}
	if (!Player->s_Pressed) {
		vel.y *= friction;
	}
	if (Player->d_Pressed) {
		newPos.x = Player->moveSpeed * deltaTime;
	}
	if (!Player->s_Pressed) {
		vel.x *= friction;
	}

	acc = (newPos * 2);
	vel = (vel + acc);
	newPos = (newPos + vel);

	if (Player->right_mouse_pressed) {
		AEInputGetCursorPosition(&mouseX, &mouseY);
		Vector2 mousePos{ static_cast<float>(mouseX),static_cast<float>(mouseY) };
		std::cout << mouseX << ',' << mouseY << std::endl;
		Projectile projectile;
		projectile.position = Player->transform.position;
		Vector2 direction = mousePos - Player->transform.position;
		Vector2 normalizedDirection = direction.normalize();
		projectile.velocity = normalizedDirection * 5.0f;
		projectile.accelration = Vector2{ };
		for (unsigned int i = 0; i < 5; i++) {
			projectile.velocity += projectile.accelration * deltaTime;
			projectile.position += projectile.velocity * deltaTime;
		}
		
		CreateQuadMesh(500.f, 500.f, Color(1, 1, 1, 1),projectile.transform);
		projectile.transform.position = projectile.position;
		DrawMesh(&projectile.transform);
	}


	Player->transform.position += newPos;

	DrawMesh(&Player->transform);
}