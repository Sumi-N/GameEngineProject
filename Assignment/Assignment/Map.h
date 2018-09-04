#pragma once
class Map
{
public:
	static const int maxainum = 100;
	static const int mapsize = 100;

	Map(int);
	~Map();

	void setAIs();
	void setMap(int, int);
	void moveAIs();
	void detectCollision();

private:
	int ainum;
	AI ai[maxainum];
	bool map[mapsize][mapsize];
};

