#pragma once
#include "Map.h";
class AI
{
private:
	char* namep;
	char name[256];
	int x, y;
	int map[Map::mapsize][Map::mapsize];

public:
	AI();
	AI(int);
	~AI();

	void setPosition(int, int);
	void move();
	int getPositionX();
	int getPositionY();
};

