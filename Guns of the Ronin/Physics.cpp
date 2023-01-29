
#include "Physics.h"
#include <AEEngine.h>
#include <stdio.h>
#include <time.h>
#include <iostream>


bool Col_Circle_Circle(Vector2 pos1, float radius1, Vector2 pos2, float radius2) {
	if ((pos1 - pos2).magnitude() < (radius1 + radius2)) {
		return true;
	}
	return false;
}



Vector2 RandomPoint_OutsideSqaure(float minDist, float maxDist, Vector2 centerPos) {

	int randGrid = rand() % 8 + 1;
	//std::cout << randGrid;
	float x = 0, y = 0;
	float randX = AERandFloat(), randY = AERandFloat();
	float gridWidth = maxDist - minDist;
	//Break the entire area into 9 smaller rectangles (imagine number pad)
	//then the area around centerPos would be 5 on the number pad, skip tis grid then
	//Generate a randompos within one of the randomized grids 1-8
	//	1	2	3
	//	4		5
	//	6	7	8
	switch (randGrid) {
	case 1:
		x = centerPos.x - minDist - gridWidth + randX * gridWidth;
		y = centerPos.y + minDist + gridWidth - randY * gridWidth;
		break;
	case 2:
		x = centerPos.x - minDist + randX * minDist * 2;
		y = centerPos.y + minDist + gridWidth - randY * gridWidth;
		break;
	case 3:
		x = centerPos.x + minDist + randX * gridWidth;
		y = centerPos.y + minDist + gridWidth - randY * gridWidth;
		break;
	case 4:
		x = centerPos.x - minDist - gridWidth + randX * gridWidth;
		y = centerPos.y + minDist - randY * minDist * 2;
		break;
	case 5:
		x = centerPos.x + minDist + randX * gridWidth;
		y = centerPos.y + minDist - randY * minDist * 2;
		break;
	case 6:
		x = centerPos.x - minDist - gridWidth + randX * gridWidth;
		y = centerPos.y - minDist - randY * gridWidth;
		break;
	case 7:
		x = centerPos.x - minDist + randX * minDist * 2;
		y = centerPos.y - minDist - randY * gridWidth;
		break;
	case 8:
		x = centerPos.x + minDist + randX * gridWidth;
		y = centerPos.y - minDist - randY * gridWidth;
		break;
	}
	return Vector2(x, y);
}
Vector2 BulletDir(float mouseX, float mouseY, Vector2 PlayerPos) {
	Vector2 direction;
	direction.x = mouseX - PlayerPos.x;
	direction.y = mouseY - PlayerPos.y;
	return direction.normalize();
}

