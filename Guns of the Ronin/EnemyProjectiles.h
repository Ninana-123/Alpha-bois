#pragma once

#ifndef ENEMYPROJECTILES_h
#define ENEMYPROJECTILES_h

#include "Graphics.h"
#include "Physics.h"
#include <iostream>
#include "Archer.h"


namespace {
	enum { PROJECTILE_COUNT = 50 };
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