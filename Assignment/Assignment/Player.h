#pragma once
class Player
{
public:
	char* playerp;
	Player();
	~Player();
	void setPosition(int, int);
	int getPositionX();
	int getPositionY();
	bool move(char);

private:
	int x, y;
};

