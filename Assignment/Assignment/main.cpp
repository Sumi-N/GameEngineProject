#include <iostream>
#include "NameGenerator.h"
#include "Map.h"

int main() {

	int mn;
	char *p;
	char player[256];
	p = player;

	std::cout << "choose the number of monster" << std::endl;
	std::cin >> mn;
	std::cout << "the number of monster pops up : " << mn << std::endl;
	std::cout << "type your player name" << std::endl;
	std::cin >> player;
	std::cout << "your name is " << player << std::endl;

	Map* mapp = new Map(mn, p);
	mapp->setPlayer();
	mapp->setAIs();

	int turncount = 0;
	char order = 'p';
	while (order != 'q') {

		if (turncount != 3) {
			turncount++;
		}
		else {
			mapp->newAI();
			turncount = 0;
		}

		mapp->showMap();

		std::cin >> order;
		mapp->movePlayer(order);
		mapp->moveAIs();

		if (mapp->ainum == 0) {
			order = 'q';
		}
	}
	mapp->~Map();

	return 0;
}
