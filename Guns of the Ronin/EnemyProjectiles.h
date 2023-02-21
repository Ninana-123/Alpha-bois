#pragma once

#ifndef ENEMYPROJECTILES_H
#define ENEMYPROJECTILES_H

#include "Graphics.h"
#include "Physics.h"
#include <iostream>


namespace {
	enum { PROJECTILE_COUNT = 100 };
	//int PROJDAMAGE = 50;
	float PROJECTILE_HEIGHT = 20, PROJECTILE_WIDTH = 20;
	AEGfxVertexList* projectileMesh = 0;
}
class Projectile {
public:
	Transform transform;
	bool enabled;
	//int dmg;
	Vector2 direction;
	float timeSince_lastDmgDeal = 0;
};

struct ProjectilePool {
	Projectile projectile[PROJECTILE_COUNT];
	Projectile* activeProjectile[PROJECTILE_COUNT];
	int activeSize;
};

void ProjectileAdd(ProjectilePool& projectile, Vector2 archPos, Vector2 playerPos);

void Init_ProjectilePool(ProjectilePool& projectile);

void Draw_Projectile(ProjectilePool& projectile);

void Projectile_AI(ProjectilePool& projectile);

void ProjectileRemove(int index, ProjectilePool& projectile);

void Free_Projectile();

#endif 