#include "StaticLibTest.h"
#include "Object2D.h"
#include<iostream>
#include "List.h"
#include "CollisionDetection.h"
#include "Monster.h"
#include "Player.h"

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

	Monster* monsters = new Monster[mn]();
	Player player1;
	

	int turncount = 0;
	char order = 'p';
	while (order != 'q') {

		if (turncount != 3) {
			turncount++;
		}
		else {
			turncount = 0;
		}


		std::cout << "press \' a\' to move right \'d\' to move left \'w\' to move up \'s\' to move down \'q\' to quit this game" << std::endl;
		std::cin >> order;
	}

	return 0;
}