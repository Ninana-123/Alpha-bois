#include "Player.h"
#include "TimeManager.h"

float dirSpeed = 2.f;

enum class DirPressed { LEFT, RIGHT};
DirPressed prevDir = DirPressed::LEFT, curDir = DirPressed::RIGHT;

float timeSinceLastFired = 0.0f;

AEGfxVertexList* col;

void Player_Init(Player* player,BulletPool &bulletPool) {

	player->transform.color = Color(1, 1, 1, 1);
	CreateQuadMesh(PLAYER_HEIGHT, PLAYER_WIDTH, player->transform.color, playerMesh,1.0f/5.0f,1.0f);
	playerTexture = AEGfxTextureLoad("Assets/RoninSpriteSheet.png");
	player->transform.texture = &playerTexture;
	//player->transform.scale = { 100.f, 100.f };
	player->transform.height = PLAYER_HEIGHT;
	player->transform.width = PLAYER_WIDTH;
	player->transform.position = {0.f,0.f};
	player->transform.mesh = &playerMesh;
	player->transform.colliderSize = { 50,80 };
	player->transform.colliderOffsetPos = { 0, PLAYER_HEIGHT * -0.1f };

	Init_BulletPool(bulletPool);
	CreateQuadMesh(1, 1, Color(1, 0, 0), col);
}



void Player_Update(Player* player,BulletPool &bulletPool) {
	if (!IsTime_Paused()) {
		
		static float frameTimer = 0;
		frameTimer += deltaTime;


		Vector2 newPos{ };
		Vector2 vel{ };
		Vector2 acc{ };

		player->w_Pressed = AEInputCheckCurr(AEVK_W);
		player->a_Pressed = AEInputCheckCurr(AEVK_A);
		player->s_Pressed = AEInputCheckCurr(AEVK_S);
		player->d_Pressed = AEInputCheckCurr(AEVK_D);
		

		if (player->w_Pressed) {
			newPos.y = player->moveSpeed * deltaTime;
			if (frameTimer >= 0.2f) {
				player->animation.PlayAnim();
				player->animation.NextFrame(player->transform);
				player->animation.Update_SpriteAnim(player->transform);
				frameTimer = 0;
			}
		}
		if (player->a_Pressed) {
			newPos.x = -player->moveSpeed * deltaTime;
			curDir = DirPressed::LEFT;
			if (curDir != prevDir) {
				FlipTexture_x(player->transform);
				prevDir = curDir;
			}
			if (frameTimer >= 0.2f) {
				player->animation.PlayAnim();
				player->animation.NextFrame(player->transform);
				player->animation.Update_SpriteAnim(player->transform);
				frameTimer = 0;
			}
		}

		if (player->s_Pressed) {
			newPos.y = -player->moveSpeed * deltaTime;
			if (frameTimer >= 0.2f) {
				player->animation.PlayAnim();
				player->animation.NextFrame(player->transform);
				player->animation.Update_SpriteAnim(player->transform);
				frameTimer = 0;
			}
		}
		if (player->d_Pressed) {
			newPos.x = player->moveSpeed * deltaTime;
			curDir = DirPressed::RIGHT;
			if (curDir != prevDir) {
				prevDir = curDir;
				FlipTexture_x(player->transform);
			}
			if (frameTimer >= 0.2f) {
				player->animation.PlayAnim();
				player->animation.NextFrame(player->transform);
				player->animation.Update_SpriteAnim(player->transform);
				frameTimer = 0;
			}
		}

		acc = (newPos * dirSpeed);
		vel = (vel + acc);
		newPos = (newPos + vel);
		
		//player->left_mouse_pressed = AEInputCheckTriggered(AEVK_LBUTTON);
		player->left_mouse_pressed = AEInputCheckCurr(AEVK_LBUTTON);

		timeSinceLastFired += deltaTime;

		if (player->left_mouse_pressed) {
			if (timeSinceLastFired >= PLAYER_FIRERATE) {
				BulletAdd(bulletPool, player->transform.position);
				timeSinceLastFired = 0;
			}
	
		}


		player->transform.position += newPos;
		Bullet_AI(bulletPool);
	}

}

void Draw_Player(Player* player,BulletPool &bulletPool) {
	DrawMesh(&player->transform);
	
	Draw_Bullet(bulletPool);

	Draw_QuadCollider(&player->transform, col);
}

void player_dmg(PlayerInfo& info,int dmg) {
	info.health -= dmg;
	if (info.health <= 0) {
		info.playerDead= 1;
		TimePause();
	}
}

void Heal_player(PlayerInfo& info) {
	info.health += 10;
}


void Free_Player() {
	AEGfxMeshFree(playerMesh);
	AEGfxTextureUnload(playerTexture);
	AEGfxMeshFree(col);
}