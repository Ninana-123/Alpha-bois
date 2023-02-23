#include "Player.h"
#include "TimeManager.h"




void Player_Init(Player* Player,BulletPool &bulletPool) {
	Player->transform.color = Color(1, 1, 1, 1);
	CreateQuadMesh(50.0f, 50.0f, Player->transform.color, playerMesh);
	Player->transform.mesh = &playerMesh;
	Player->transform.position = Vector2(100.f, 100.f);
	Init_BulletPool(bulletPool);
}



void Player_Update(Player* Player,BulletPool &bulletPool) {
	if (!IsTime_Paused()) {
		

		Vector2 newPos{ };
		Vector2 vel{ };
		Vector2 acc{ };
		const float friction = 0.95f;

		Player->w_Pressed = AEInputCheckCurr(AEVK_W);
		Player->a_Pressed = AEInputCheckCurr(AEVK_A);
		Player->s_Pressed = AEInputCheckCurr(AEVK_S);
		Player->d_Pressed = AEInputCheckCurr(AEVK_D);


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
		Player->left_mouse_pressed = AEInputCheckTriggered(AEVK_LBUTTON);

		if (Player->left_mouse_pressed) {
			BulletAdd(bulletPool,Player->transform.position);
	
		}


		Player->transform.position += newPos;
		Bullet_AI(bulletPool);
	}

}

void Draw_Player(Player* player,BulletPool &bulletPool) {
	DrawMesh(&player->transform);

	Draw_Bullet(bulletPool);
}
void player_dmg(PlayerInfo& info,int dmg) {
	info.health -= dmg;
	if (info.health <= 0) {
		info.playerDead= 1;
	}
}


void Free_Player() {
	AEGfxMeshFree(playerMesh);
}