/*
\copyright
		All content(C) 2023 DigiPen Institute of Technology Singapore.All rights
		reserved.Reproduction or disclosure of this file or its contents without the prior
		written consent of DigiPen Institute of Technology is prohibited.
*/
/*!
@file		void.cpp
@author		Teo Sheen Yeoh
@Email		t.sheenyeoh@digipen.edu
@course		CSD 1450
@section	Section A
@date		3 March 2023
@brief		This file contains code for the credit screen.
*//*______________________________________________________________________*/
#include "Player.h"
#include "TimeManager.h"

float dirSpeed = 2.f;

enum class DirPressed { LEFT, RIGHT};
DirPressed prevDir = DirPressed::LEFT, curDir = DirPressed::RIGHT;

float timeSinceLastFired = 0.0f;

#define PLAYER_MAX_X_POS 780
#define PLAYER_MAX_Y_POS 420


void Player_Init(Player* player,BulletPool &bulletPool) {

	player->transform.color = Color(1, 1, 1, 1);
	Create_QuadMesh(PLAYER_HEIGHT, PLAYER_WIDTH, player->transform.color, playerMesh,1.0f/5.0f,1.0f);
	playerTexture = AEGfxTextureLoad("Assets/RoninSpriteSheet.png");
	player->transform.texture = &playerTexture;
	player->transform.height = PLAYER_HEIGHT;
	player->transform.width = PLAYER_WIDTH;
	player->transform.position = {0.f,0.f};
	player->transform.mesh = &playerMesh;
	player->transform.colliderSize = { 50,80 };
	player->transform.colliderOffsetPos = { 0, PLAYER_HEIGHT * -0.1f };

	Init_BulletPool(bulletPool);
}



void Player_Update(Player* player,BulletPool &bulletPool) {

	if (!Is_TimePaused()) {
		
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
				player->animation.play_Anim();
				player->animation.next_Frame(player->transform);
				player->animation.update_SpriteAnim(player->transform);
				frameTimer = 0;
			}
		}
		if (player->a_Pressed) {
			newPos.x = -player->moveSpeed * deltaTime;
			curDir = DirPressed::LEFT;
			if (curDir != prevDir) {
				Flip_TextureX(player->transform);
				prevDir = curDir;
			}
			if (frameTimer >= 0.2f) {
				player->animation.play_Anim();
				player->animation.next_Frame(player->transform);
				player->animation.update_SpriteAnim(player->transform);
				frameTimer = 0;
			}
		}

		if (player->s_Pressed) {
			newPos.y = -player->moveSpeed * deltaTime;
			if (frameTimer >= 0.2f) {
				player->animation.play_Anim();
				player->animation.next_Frame(player->transform);
				player->animation.update_SpriteAnim(player->transform);
				frameTimer = 0;
			}
		}
		if (player->d_Pressed) {
			newPos.x = player->moveSpeed * deltaTime;
			curDir = DirPressed::RIGHT;
			if (curDir != prevDir) {
				prevDir = curDir;
				Flip_TextureX(player->transform);
			}
			if (frameTimer >= 0.2f) {
				player->animation.play_Anim();
				player->animation.next_Frame(player->transform);
				player->animation.update_SpriteAnim(player->transform);
				frameTimer = 0;
			}
		}

		acc = (newPos * dirSpeed);
		vel = (vel + acc);
		newPos = (newPos + vel);

		
		player->left_mouse_pressed = AEInputCheckTriggered(AEVK_LBUTTON);
		//player->left_mouse_pressed = AEInputCheckCurr(AEVK_LBUTTON);

		timeSinceLastFired += deltaTime;

		if (player->left_mouse_pressed) {		
			if (timeSinceLastFired >= PLAYER_FIRERATE) {
				BulletAdd(bulletPool, player->transform.position);
				timeSinceLastFired = 0;
				if (!audioPlayed) {
					AEAudioPlay(playerShootSound, playerAudioGroup, 0.1f, 1.f, 0);
					audioPlayed = true;
				}
			}
		}
		else audioPlayed = false;


		player->transform.position += newPos;

		player->transform.position.x = AEClamp(player->transform.position.x, -PLAYER_MAX_X_POS, PLAYER_MAX_X_POS);
		player->transform.position.y = AEClamp(player->transform.position.y, -PLAYER_MAX_Y_POS, PLAYER_MAX_Y_POS);

		Bullet_AI(bulletPool);
	}

}

void Draw_Player(Player* player,BulletPool &bulletPool) {
	Draw_Mesh(&player->transform);
	
	Draw_Bullet(bulletPool);
}

void player_dmg(PlayerInfo& info,int dmg) {
	info.health -= dmg;
	if (info.health <= 0) {
		info.playerDead= 1;
		Pause_Time();
	}
}

void Heal_player(PlayerInfo& info) {
	info.health += 10;
}


void Free_Player() {
	AEGfxMeshFree(playerMesh);
	AEGfxTextureUnload(playerTexture);
}