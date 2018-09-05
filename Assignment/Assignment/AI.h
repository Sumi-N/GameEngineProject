#pragma once
#include "NameGenerator.h"
#include <stdlib.h>

class AI
{
private:
	int x, y;
	int map[100][100];

public:
	char* namep;
	char name[256];
	AI();
	AI(int);
	~AI();

	void setPosition(int, int);
	void move();
	int getPositionX();
	int getPositionY();
};

