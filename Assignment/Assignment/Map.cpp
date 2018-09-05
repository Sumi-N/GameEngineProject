#include "Map.h"

Map::Map(int ainum , char* player)
{
	this->ainum = ainum;
	this->player.playerp = player;

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

void Map::setAI(int ainum) {
	int x = rand() % mapsize;
	int y = rand() % mapsize;

	while (map[x][y]) {
		x = rand() % mapsize;
		y = rand() % mapsize;
	}

	setMap(x, y);
	ai[ainum].setPosition(x, y);
}

void Map::setPlayer() {
	int x = rand() % mapsize;
	int y = rand() % mapsize;

	while (map[x][y]) {
		x = rand() % mapsize;
		y = rand() % mapsize;
	}

	setMap(x, y);
	player.setPosition(x, y);
}

void Map::moveAIs() {
	for (int i = 0; i < ainum; i++)
	{
		setMap(ai[i].getPositionX(), ai[i].getPositionY());
		ai[i].move();
	}
	detectCollision();
	for (int i = 0; i < ainum; i++)
	{
		setMap(ai[i].getPositionX(), ai[i].getPositionY());
	}
}

void Map::movePlayer(char order) {
	player.move(order);
}

void Map::detectCollision() {
	for (int i = 0; i < ainum; i++)
	{
		if (ai[i].getPositionX() == player.getPositionX() && ai[i].getPositionY() == player.getPositionY()) {
			deleteAI(i);
			std::cout << "you hit an AI" << std::endl;
		}
	}
	for (int i = 0; i < ainum; i++)
	{
		for (int j = 0; j < ainum; j++)
		{
			if (i == j) continue;
			if (ai[i].getPositionX() == ai[j].getPositionX() && ai[i].getPositionY() == ai[j].getPositionY()) {
				deleteAI(i);
				deleteAI(j);
				std::cout << "enemied got bumped and both are diappered" << std::endl;
			}
		}
	}
}

void Map::deleteAI(int i) {
	setMap(ai[i].getPositionX(), ai[i].getPositionY());
	for (int j = i; j < ainum-1; j++) {
		ai[j] = ai[j+1];
	}
	ainum--;
}

void Map::newAI() {
	if (ainum < maxainum) {
		ainum++;
		std::cout << ainum << std::endl;
		ai[ainum - 1] = AI::AI(5);
		setAI(ainum - 1);
	}
}

void Map::showMap() {
	std::cout << player.playerp << " is at (" << player.getPositionX() << "," << player.getPositionY() << ")" << std::endl;
	for (int i = 0; i < ainum; i++)
	{
		std::cout << ai[i].name << " is at (" << ai[i].getPositionX() << "," << ai[i].getPositionY() << ")" << std::endl;
	}
	std::cout << "current AI number :" << ainum << std::endl;
}
