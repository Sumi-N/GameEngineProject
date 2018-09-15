#include "Object2D.h"
#include <stdlib.h>
#include <iostream>

Object2D::Object2D()
{
	//printf("constructor for object2d is called\n");
}

Object2D::~Object2D()
{
	//printf("deconstrutor for object2d is called\n");
}

Object2D::Object2D(const Object2D &obj) {
	pos = obj.pos;
	name = obj.name;
	printf("copyconstractor of Object2D is called\n");
}

void Object2D::randomName(int length) {
	char characters[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	for (int i = 0; i < length; i++) {
		char c = characters[rand() % (sizeof(characters) - 1)];
		name.add(c); 
	}
	name.add('\0');
}

void Object2D::showPosition() {
	std::cout << "this monster is at (" << this->pos.x() << "," << this->pos.y() << ")" << std::endl;
}

void Object2D::showName(){
	randomName(5);

	List<char>::Iterator i;
	for (i = name.begin(); i != name.end(); i++) {
		printf("%c", *i);
	}
	printf("\n");

}
