#include "Player.h"
#include "TimeManager.h"

float dirSpeed = 2.f;


void Player_Init(Player* player,BulletPool &bulletPool) {

	player->transform.color = Color(1, 1, 1, 1);
	CreateQuadMesh(1.0f, 1.0f, player->transform.color, playerMesh,1.0f/5.0f,1.0f);
	playerTexture = AEGfxTextureLoad("Assets/RoninSpriteSheet.png");
	player->transform.texture = &playerTexture;
	player->transform.scale = { 100.f, 100.f };
	player->transform.height = 1.0f;
	player->transform.width = 4.0f;
	player->transform.position = {0.f,0.f};
	player->transform.mesh = &playerMesh;


	Init_BulletPool(bulletPool);
}



void Player_Update(Player* player,BulletPool &bulletPool) {
	if (!IsTime_Paused()) {
		
		static float frameTimer = 0;
		frameTimer += deltaTime;

		bool textureFlipped = false;

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
		if (player->a_Pressed && !(textureFlipped)) {
			newPos.x = -player->moveSpeed * deltaTime;
			FlipTexture_x(player->transform);
			textureFlipped = true;
			if (frameTimer >= 0.2f) {
				player->animation.PlayAnim();
				player->animation.NextFrame(player->transform);
				player->animation.Update_SpriteAnim(player->transform);
				frameTimer = 0;
			}
		}
		else if(!player->a_Pressed) {
			textureFlipped = false;
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
		if (player->d_Pressed && !(textureFlipped)) {
			newPos.x = player->moveSpeed * deltaTime;
			FlipTexture_x(player->transform);
			textureFlipped = true;
			if (frameTimer >= 0.2f) {
				player->animation.PlayAnim();
				player->animation.NextFrame(player->transform);
				player->animation.Update_SpriteAnim(player->transform);
				frameTimer = 0;
			}
		}
		else { 
			textureFlipped = false; 
		}

		acc = (newPos * dirSpeed);
		vel = (vel + acc);
		newPos = (newPos + vel);
		player->left_mouse_pressed = AEInputCheckTriggered(AEVK_LBUTTON);

		if (player->left_mouse_pressed) {
			BulletAdd(bulletPool,player->transform.position);
	
		}


		player->transform.position += newPos;
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

void Heal_player(PlayerInfo& info) {
	info.health += 10;
}


void Free_Player() {
	AEGfxMeshFree(playerMesh);
	AEGfxTextureUnload(playerTexture);
}