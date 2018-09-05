#pragma once
#include "AI.h"
#include "Player.h"
#include <stdlib.h>
#include <iostream>

static const int maxainum = 100;
static const int mapsize = 100;

class Map
{
public:

	Map(int,char*);
	~Map();

	void setAIs();
	void setAI(int);
	void setPlayer();
	void setMap(int, int);
	void moveAIs();
	void movePlayer(char);
	void detectCollision();
	void deleteAI(int);
	void newAI();
	void showMap();

	int ainum;

private:
	AI ai[maxainum];
	Player player;
	bool map[mapsize][mapsize];
};

