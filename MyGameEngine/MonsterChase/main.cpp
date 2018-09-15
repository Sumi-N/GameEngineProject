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

	List<Monster> monsters;
	for (int i = 0; i < mn; i++) {
		Monster mon;
		mon.setPositions();
		monsters.add(mon);
	}
	Player player1;

	List<Monster>::Iterator i;
	for (i = monsters.begin(); i != monsters.end(); i++) {
		(*i).showPosition();
		(*i).showName();
	}
	

	int turncount = 0;
	char order = 'p';
	while (order != 'q') {

		if (turncount != 3) {
			turncount++;
		}
		else {
			turncount = 0;
			Monster mon;
			monsters.add(mon);
		}

		std::cout << "press \' a\' to move right \'d\' to move left \'w\' to move up \'s\' to move down \'q\' to quit this game" << std::endl;
		std::cin >> order;
	}

	return 0;
}