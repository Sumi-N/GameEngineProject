#include "Object2D.h"
#include <stdlib.h>
#include <iostream>

Object2D::Object2D()
{
	//printf("constructor for object2D is called\n");

}

Object2D::~Object2D()
{
	//printf("deconstrutor for object2D is called\n");
	delete[] headofname;
}

void Object2D::randomName(int length) {
	namelength = length;
	char characters[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	name = new char[length+1];
	headofname = name;
	for (int i = 0; i < length; i++) {
		name[i] = characters[rand() % (sizeof(characters) - 1)];
	}
	name[length] = '\0';
}

void Object2D::showPosition() {
}

void Object2D::showDirection() {

}

void Object2D::showName(){
	for (int i = 0; i < namelength; i++) {
		printf("%c", name[i]);
	}
	printf("\n");
}