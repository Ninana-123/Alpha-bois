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
	Vector2(float x, float y) {
		this->x = x;
		this->y = y;
	}

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
	bool within_dist(Vector2 pos, float dist) {
		float actualDist_sqr = (this->x - pos.x) * (this->x - pos.x) + (this->y - pos.y) * (this->y - pos.y);
		return actualDist_sqr < (dist* dist) ? true : false;
	}

};

enum DIRECTION { VERTICAL, HORIZONTAL };


bool Col_Circle_Circle(Vector2 pos1, float radius1, Vector2 pos2, float radius2);

Vector2 RandomPoint_OutsideSqaure(float minDist, float maxDist, Vector2 centerPos);

#endif // !PHYSICS_H
