#include "Object2D.h"
#include <stdlib.h>

Object2D::Object2D()
{
	randomName(5);
}


Object2D::~Object2D()
{
}

Object2D::Object2D(int x, int y) {
	pos.setX(x);
	pos.setY(y);
}

void Object2D::randomName(int length) {
	static const char characters[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	for (int i = 0; i < length; i++) {
		name.add(characters[rand() % (sizeof(characters) - 1)]);
	}
	name.add(0);
}
