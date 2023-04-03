/*
\copyright
		All content(C) 2023 DigiPen Institute of Technology Singapore.All rights
		reserved.Reproduction or disclosure of this file or its contents without the prior
		written consent of DigiPen Institute of Technology is prohibited.
*/
/*!
@file			Physics.cpp
@author			Zeng ZhiCheng
@Email			z.zhicheng@digipen.edu
@course			CSD 1451
@section		Section A
@date			2 April 2023
@brief			This file contains definition of physics related classes (and definition of its member functions) and functions
*//*______________________________________________________________________*/
#include "Physics.h"
#include <AEEngine.h>
#include <stdio.h>
#include <time.h>
#include <iostream>


//Check for static collision between 2 circles
bool Col_StaticCircleCircle(Vector2 pos1, float radius1, Vector2 pos2, float radius2) {
	if ((pos1 - pos2).magnitude() < (radius1 + radius2)) {
		return true;
	}
	return false;
}


//Get a random point that is outside of a square of width minDist but within a bigger square of width maxDist 
Vector2 Random_PointOutsideSquare(float minDist, float maxDist, Vector2 centerPos) {

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

//Get the direction of a bullet
Vector2 Bullet_Dir(float mouseX, float mouseY, Vector2 PlayerPos) {
	Vector2 direction;
	direction.x = mouseX - PlayerPos.x;
	direction.y = mouseY - PlayerPos.y;
	return direction.normalize();
}

