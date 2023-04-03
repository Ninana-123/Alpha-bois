/*
\copyright
		All content(C) 2023 DigiPen Institute of Technology Singapore.All rights
		reserved.Reproduction or disclosure of this file or its contents without the prior
		written consent of DigiPen Institute of Technology is prohibited.
*/
/*!
@file		Physics.h
@author		Zeng ZhiCheng
@Email		z.zhicheng@digipen.edu
@course		CSD 1451
@section	Section A
@date		2 April 2023
@brief		This file contains declaration of physics related classes (and definition of its member functions) and functions
*//*______________________________________________________________________*/
#pragma once


#ifndef PHYSICS_H
#define PHYSICS_H
#include <math.h>
class Vector2 {
public:
	float x;
	float y;
	Vector2() {
		x = 0;
		y = 0;
	}
	Vector2(float xIn, float yIn) : x{ xIn }, y{ yIn } { }

	//overloading + and +=
	Vector2 operator+(const Vector2& b) {
		Vector2 vector;
		vector.x = this->x + b.x;
		vector.y = this->y + b.y;
		return vector;
	}
	Vector2& operator+=(const Vector2& b) {
		this->x += b.x;
		this->y += b.y;
		return *this;
	}

	//overloading - and -=
	Vector2 operator-(const Vector2& b) {
		Vector2 vector;
		vector.x = this->x - b.x;
		vector.y = this->y - b.y;
		return vector;
	}
	Vector2& operator-=(const Vector2& b) {
		this->x -= b.x;
		this->y -= b.y;
		return *this;
	}

	//overloading * and *=
	Vector2 operator*(float const& scale) {
		Vector2 vector;
		vector.x = this->x * scale;
		vector.y = this->y * scale;
		return vector;
	}
	Vector2& operator*=(float const& scale) {
		this->x *= scale;
		this->y *= scale;
		return *this;
	}

	//overloading / and /= 
	Vector2 operator/(float const& scale) {
		Vector2 vector;
		vector.x = this->x / scale;
		vector.y = this->y / scale;
		return vector;
	}
	Vector2& operator/=(float const& scale) {
		this->x /= scale;
		this->y /= scale;
		return *this;
	}

	float magnitude() {
		return sqrtf(this->x * this->x + this->y * this->y);
	}
	Vector2 normalize() {
		Vector2 vector;
		float mag = this->magnitude();
		vector.x = this->x / mag;
		vector.y = this->y / mag;
		return vector;
	}

	//Check and returns true if distance between this Vector2 and pos is less than dist
	bool within_Dist(Vector2 pos, float dist) {
		float actualDistSqr = (this->x - pos.x) * (this->x - pos.x) + (this->y - pos.y) * (this->y - pos.y);
		return actualDistSqr < (dist* dist) ? true : false;
	}

};

enum DIRECTION { VERTICAL, HORIZONTAL };


bool Col_StaticCircleCircle(Vector2 pos1, float radius1, Vector2 pos2, float radius2);

Vector2 Random_PointOutsideSquare(float minDist, float maxDist, Vector2 centerPos);

Vector2 Bullet_Dir(float playerX, float playerY, Vector2 PlayerPos);


#endif // !PHYSICS_H
