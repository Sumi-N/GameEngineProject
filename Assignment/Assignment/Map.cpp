#include "Map.h"
#include "AI.h"
#include <stdlib.h>

Map::Map(int ainum)
{
	this->ainum = ainum;
	for (int i = 0; i < mapsize; i++) {
		for (int j = 0; j < mapsize; j++)
		{
			map[i][j] = false;
		}
	}

	for (int i = 0; i < ainum; i++)
	{
		ai[i] = AI::AI(5);
	}
}

Map::~Map()
{
}

void Map::setMap(int x, int y) {
	map[x][y] = !map[x][y];
}

void Map::setAIs() {
	for (int i = 0; i < ainum ; i++)
	{
		int x = rand() % mapsize;
		int y = rand() % mapsize;

		while (map[x][y]) {
			x = rand() % mapsize;
			y = rand() % mapsize;
		}

		setMap(x, y);
		ai[i].setPosition(x, y);

	}
}

void Map::moveAIs() {
	for (int i = 0; i < ainum; i++)
	{
		setMap(ai[i].getPositionX, ai[i].getPositionY);
		ai[i].move();
	}
	detectCollision();
	for (int i = 0; i < ainum; i++)
	{
		setMap(ai[i].getPositionX, ai[i].getPositionY);
		ai[i].move();
	}
}

void Map::detectCollision() {
	for (int i = 0; i < ainum; i++)
	{
		for (int j = 0; j < ainum; j++)
		{
			if (i == j) continue;
			if (ai[i].getPositionX == ai[j].getPositionX && ai[i].getPositionY == ai[j].getPositionY) {

			}
		}
	}
}
