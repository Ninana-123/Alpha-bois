#pragma once

#ifndef BULLETS_H
#define BULLETS_H

#include "Graphics.h"
#include "Physics.h"
#include <iostream>


namespace {
	enum { BULLET_COUNT = 10 };
	//int PROJDAMAGE = 50;
}
class Bullet {
public:
	Transform transform;
	bool enabled;
	//int dmg;
	Vector2 direction;
};

struct BulletPool {
	Bullet bullets[BULLET_COUNT];
	Bullet* activeBullets[BULLET_COUNT];
	int activeSize;
};

void BulletAdd(BulletPool& bullet,Vector2 playerPos);

void Init_BulletPool(BulletPool& bullet);

void Draw_Bullet(BulletPool& bullet);

void Bullet_AI(BulletPool& pool);

void BulletRemove(int index, BulletPool& pool);

#endif 