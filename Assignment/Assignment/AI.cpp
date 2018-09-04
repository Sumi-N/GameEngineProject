#include "AI.h"
#include "NameGenerator.h"
#include "Map.h"
#include <stdlib.h>

AI::AI() {

}

AI::AI(int namelength)
{
	this->namep = this->name;
	NameGenerator::returnName(this->namep, namelength);
}


AI::~AI()
{
}

void AI::setPosition(int x, int y) {
	this->x = x;
	this->y = y;
}

int AI::getPositionX() {
	return x;
}

int AI::getPositionY() {
	return y;
}

void AI::move() {
	bool up = true, down = true, right = true, left = true;
	if (this->x == 0) {
		left = false;
	}else if (this->x == Map::mapsize - 1) {
		right = false;
	}
	if (this->y == 0) {
		up = false;
	}else if (this->y == Map::mapsize - 1) {
		down = false;
	}

	if (right && left) {
		x = rand() % 2 ? x + 1 : x - 1;
	}
	else {
		x = right ? x + 1 : x - 1;
	}

	if (up && down) {
		y = rand() % 2 ? y + 1 : y - 1;
	}
	else{
		y = up ? y + 1 : y - 1;
	}
}
