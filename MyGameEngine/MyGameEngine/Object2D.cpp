#include "Object2D.h"
#include <stdlib.h>
#include <iostream>

Object2D::Object2D()
{
	//printf("constructor for object2D is called\n");
	this->pos.setX(rand() % 100);
	this->pos.setY(rand() % 100);
}

Object2D::~Object2D()
{
	//printf("deconstrutor for object2D is called\n");
	delete[] headofname;
}

Object2D::Object2D(const Object2D & obj)
{
	name = new char[11];
	for (int i = 0; i <= 10; i++) {
		name[i] = obj.name[i];
	}
	headofname = name;
	*headofname = *obj.headofname;
	namelength = obj.namelength;
	pos = obj.pos;
}

Object2D & Object2D::operator=(const Object2D & obj)
{	
	name = new char[11];
	for (int i = 0; i <= 10; i++) {
		name[i] = obj.name[i];
	}
	headofname = name;
	*headofname = *obj.headofname;
	namelength = obj.namelength;
	pos = obj.pos;
	return *this;
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
	for (int i = 0; i < namelength; i++) {
		printf("%c", name[i]);
	}
	printf(" is at (%d,%d)\n", pos.x(), pos.y() );
}

void Object2D::showName(){
	for (int i = 0; i < namelength; i++) {
		printf("%c", name[i]);
	}
	printf("\n");
}

Vector2D<int, int> Object2D::getPosition()
{
	return pos;
}

void Object2D::setPosition(Vector2D<int, int> pos)
{
	this->pos = pos;
	return;
}
