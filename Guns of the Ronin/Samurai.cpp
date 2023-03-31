
#include "Samurai.h"
#include "TimeManager.h"
#include "HighScore.h"
#include "EnemyCounter.h"


//When a samurai dies 
void SamuraiRemove(int index, SamuraiPool& pool) {
	pool.activeSamurais[index]->enabled = false;
	
	if (index < (pool.activeSize - 1)) {
		Samurai* temp = pool.activeSamurais[index];
		pool.activeSamurais[index] = pool.activeSamurais[pool.activeSize - 1];
		pool.activeSamurais[pool.activeSize - 1] = temp;
	}
	pool.activeSize -= 1;
	--enemiesLeft;
	Add_Score(SAMURAI_KILLSCORE);
}



//Spawning a new samurai
void SamuraiAdd(SamuraiPool& pool, Vector2 playerPos) {
	for (int i = 0; i < SAMURAI_COUNT; i++) {
		if (pool.activeSamurais[i]->enabled == false) {
			pool.activeSamurais[i]->enabled = true;
			pool.activeSamurais[i]->health = SAMURAI_HEALTH;
			pool.activeSamurais[i]->transform.position = RandomPoint_OutsideSqaure(MIN_SPAWNDIST, MAX_SPAWNDIST, playerPos);
			pool.activeSamurais[i]->offsetPos = Vector2(AERandFloat() * 12.0f - 6.0f, AERandFloat() * 12.0f - 6.0f);
			pool.activeSamurais[i]->hitByPlayer = false;
			pool.activeSamurais[i]->timeSinceLastHit = 0;
			pool.activeSamurais[i]->dmgDealt = false;
			pool.activeSamurais[i]->anim.ResetAnim(pool.activeSamurais[i]->transform);
			pool.activeSize += 1;
			break;
		}
	}
}

void Init_SamuraiPool(SamuraiPool& pool) {
	pool.activeSize = 0;
	CreateQuadMesh(SAMURAI_WIDTH, SAMURAI_HEIGHT, Color(0, 1, 0), samuraiMesh, 0.5f, 1.0f);
	for (int i = 0; i < SAMURAI_COUNT; i++) {
		pool.samurais[i].enabled = false;
		pool.samurais[i].health = SAMURAI_HEALTH;
		pool.samurais[i].aiState = MOVING;
		pool.samurais[i].transform.mesh = &samuraiMesh;
		pool.samurais[i].transform.height = SAMURAI_HEIGHT;
		pool.samurais[i].transform.width = SAMURAI_WIDTH;
		pool.samurais[i].transform.texture = &samuraiTexture;
		pool.samurais[i].transform.colliderSize = { SAMURAI_WIDTH * .5f , SAMURAI_HEIGHT * 0.8f };
		pool.activeSamurais[i] = &pool.samurais[i];
	}
	samuraiTexture = AEGfxTextureLoad("Assets/Samurai_Combined.png");
}

void AI_Samurai(SamuraiPool& pool, Player& player, PlayerInfo& playerInfo) {

	Vector2 playerPos = player.transform.position;
	for (int i = 0; i < pool.activeSize; i++) {
		Samurai* curSamurai = pool.activeSamurais[i];

		switch (curSamurai->aiState)
		{
		case MOVING:
			curSamurai->targetPos = playerPos;
			if (curSamurai->transform.position.within_dist(playerPos, SAMURAI_ATT_RANGE)) {
				curSamurai->aiState = ATTACKING;
				curSamurai->anim.ResetAnim(player.transform);
				curSamurai->anim.PlayAnim();
				curSamurai->anim.NextFrame(curSamurai->transform);
			}
			else {
				Vector2 direction = (curSamurai->targetPos - curSamurai->transform.position - curSamurai->offsetPos).normalize();

				//If samurai was hit by player
				if (curSamurai->hitByPlayer) {
					curSamurai->timeSinceLastHit += deltaTime;
					//Move at a slower speed 
					curSamurai->transform.position += direction * SAMURAI_SLOWED_MS * deltaTime;
					//if the slow duration is over 
					if (curSamurai->timeSinceLastHit >= SAMURAI_SLOW_DURATION) {
						curSamurai->hitByPlayer = false;
						curSamurai->timeSinceLastHit = 0;
					}
				}
				else { //If was not hit by player recently
					//move at normal speed
					curSamurai->transform.position += direction * SAMURAI_MS * deltaTime;
				}

				if (direction.x > 0) {
					curSamurai->transform.scale.x = Absf(curSamurai->transform.scale.x) * -1.0f;
				}
				else {
					curSamurai->transform.scale.x = Absf(curSamurai->transform.scale.x);
				}
				//curSamurai->transform.rotation = acosf(direction.x);
			}
			break;
		case ATTACKING:
			//If the player moved outside of the attack range chase the player
			if (!curSamurai->transform.position.within_dist(playerPos, SAMURAI_ATT_RANGE)) {
				curSamurai->aiState = MOVING;
				curSamurai->anim.ResetAnim(curSamurai->transform);
				curSamurai->dmgDealt = false;
			}
			else {
				//If currently playing the attack animation
				if (curSamurai->anim.CurrentFrame() == SAMURAI_ATT_ANIM_FRAME) {
					if (!curSamurai->dmgDealt) {
						player_dmg(playerInfo, DAMAGE);
						curSamurai->dmgDealt = true;
					}
				}
				//attack animation is over, restart animation
				if (!curSamurai->anim.IsPlaying()) {
					curSamurai->anim.PlayAnim();
					curSamurai->dmgDealt = false;
				}
			}
			break;
		case BLOWNAWAY:
			Vector2 direction = (curSamurai->targetPos - curSamurai->transform.position).normalize();
			curSamurai->transform.position += direction * SAMURAI_SWEEP_MS * deltaTime;
			if (curSamurai->transform.position.within_dist(curSamurai->targetPos, 15.0f)) {
				curSamurai->aiState = MOVING;
			}
			break;
		}
		curSamurai->anim.Update_SpriteAnim(curSamurai->transform);

	}

}

void Dmg_Samurai(SamuraiPool& pool, PlayerInfo playerInfo, int index) {

	if ((pool.activeSamurais[index]->health -=playerInfo.att) <= 0) {
		SamuraiRemove(index, pool);
	}
	else {
		pool.activeSamurais[index]->hitByPlayer = true;
	}
}


//Push Samurais in the specified direction to the specific wordPos in the according axis
void Push_Samurai(SamuraiPool& pool, DIRECTION direction, float targetAxis) {
	for (int i = 0; i < pool.activeSize; i++) {
		pool.activeSamurais[i]->aiState = BLOWNAWAY;
		switch (direction)
		{
		case VERTICAL:
			pool.activeSamurais[i]->targetPos = Vector2(pool.activeSamurais[i]->transform.position.x, targetAxis);
			break;
		case HORIZONTAL:
			pool.activeSamurais[i]->targetPos = Vector2(targetAxis, pool.activeSamurais[i]->transform.position.y);
			break;
		default:
			break;
		}

	}
}


void Draw_Samurai(SamuraiPool& pool) {
	for (int i = 0; i < pool.activeSize; i++) {
		DrawMesh(&pool.activeSamurais[i]->transform);
	}
}

void Free_Samurai() {
	AEGfxMeshFree(samuraiMesh);
	AEGfxTextureUnload(samuraiTexture);
}