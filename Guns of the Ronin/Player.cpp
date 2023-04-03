/*
\copyright
		All content(C) 2023 DigiPen Institute of Technology Singapore.All rights
		reserved.Reproduction or disclosure of this file or its contents without the prior
		written consent of DigiPen Institute of Technology is prohibited.
*/
/*!
@file void.cpp
@author Teo Sheen Yeoh
@Email t.sheenyeoh@digipen.edu
@course CSD 1450
@section Section A
@date 3 March 2023
@brief This file contains code for the credit screen.
*//*______________________________________________________________________*/
#include "Player.h"
#include "TimeManager.h"

enum class DirPressed { LEFT, RIGHT};
DirPressed prevDir = DirPressed::LEFT, curDir = DirPressed::RIGHT;

float timeSinceLastFired = 0.0f;

void Init_Player(Player* player,BulletPool &bulletPool) {

	player->transform.color = Color(1, 1, 1, 1);
	CreateQuadMesh(PLAYER_HEIGHT, PLAYER_WIDTH, player->transform.color, playerMesh, PLAYER_SPRITE_HEIGHT / PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT);
	playerTexture = AEGfxTextureLoad("Assets/RoninSpriteSheet.png");
	player->transform.texture = &playerTexture;
	player->transform.height = PLAYER_HEIGHT;
	player->transform.width = PLAYER_WIDTH;
	player->transform.position = {0.f,0.f};
	player->transform.mesh = &playerMesh;
	player->transform.colliderSize = { PLAYER_COLLIDER_X,PLAYER_COLLIDER_Y };
	player->transform.colliderOffsetPos = { 0, PLAYER_HEIGHT * -0.1f };

	Init_BulletPool(bulletPool);
}



void Update_Player(Player* player,BulletPool &bulletPool) {

	if (!IsTime_Paused()) {
		
		static float frameTimer = 0;
		frameTimer += deltaTime;


		Vector2 newPos{ };
		Vector2 vel{ };
		Vector2 acc{ };

		player->wPressed = AEInputCheckCurr(AEVK_W);
		player->aPressed = AEInputCheckCurr(AEVK_A);
		player->sPressed = AEInputCheckCurr(AEVK_S);
		player->dPressed = AEInputCheckCurr(AEVK_D);
		

		if (player->wPressed) {
			
			newPos.y = PLAYER_MOVEMENT_SPEED * deltaTime;
			if (frameTimer >= 0.2f) {
				player->animation.PlayAnim();
				player->animation.NextFrame(player->transform);
				player->animation.Update_SpriteAnim(player->transform);
				frameTimer = 0;
			}
		}
		if (player->aPressed) {
			newPos.x = -PLAYER_MOVEMENT_SPEED * deltaTime;
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

		if (player->sPressed) {
			newPos.y = -PLAYER_MOVEMENT_SPEED * deltaTime;
			if (frameTimer >= 0.2f) {
				player->animation.PlayAnim();
				player->animation.NextFrame(player->transform);
				player->animation.Update_SpriteAnim(player->transform);
				frameTimer = 0;
			}
		}
		if (player->dPressed) {
			newPos.x = PLAYER_MOVEMENT_SPEED * deltaTime;
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

		acc = (newPos * PLAYER_DIRECTION_SPEED);
		vel = (vel + acc);
		newPos = (newPos + vel);

		
		player->leftMousePressed = AEInputCheckTriggered(AEVK_LBUTTON);
		//player->left_mouse_pressed = AEInputCheckCurr(AEVK_LBUTTON);

		timeSinceLastFired += deltaTime;

		if (player->leftMousePressed) {
			if (!audioPlayed) {
				AEAudioPlay(playerShootSound, playerAudioGroup, 0.1f, 1.f, 0);
				audioPlayed = true;
			}
			if (timeSinceLastFired >= PLAYER_FIRE_RATE) {
				Add_Bullet(bulletPool, player->transform.position);
				timeSinceLastFired = 0;
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
	DrawMesh(&player->transform);
	
	Draw_Bullet(bulletPool);
}

void Damage_Player(PlayerInfo& info,int dmg) {
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
}