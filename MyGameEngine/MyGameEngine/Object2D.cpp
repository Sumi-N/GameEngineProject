#include "Object2D.h"
#include <stdlib.h>
#include <iostream>

Object2D::Object2D()
{
	//printf("constructor for object2d is called\n");
}

/*
Object2D::Object2D(int namelength)
{
	randomName(namelength);

	//for debagging
	List<char>::Iterator it;
	it = name.begin();
	while (it != name.end()) {
		std::cout << *it << std::endl;
		it++;
	}
}
*/


Object2D::~Object2D()
{
	//printf("deconstrutor for object2d is called\n");
}

Object2D::Object2D(int x, int y) {
	pos.setX(x);
	pos.setY(y);
}

void Object2D::randomName(int length) {
	char characters[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	for (int i = 0; i < length; i++) {
		char c = characters[rand() % (sizeof(characters) - 1)];
		name.add(c);
	}
	name.add('\0');
}
