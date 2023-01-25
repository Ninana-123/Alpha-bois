
#include "Physics.h"


Vector2 test() {
	Vector2 a{ 5, 5 };
	Vector2 b{ 10, 10 };
	return a + b;
}

bool Col_Circle_Circle(Vector2 pos1, float radius1, Vector2 pos2, float radius2) {
	if ((pos1 - pos2).magnitude() < (radius1 + radius2)) {
		return true;
	}
	return false;
}
