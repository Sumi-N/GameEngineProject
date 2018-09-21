#include<iostream>
#include "List.h"
#include "Object2D.h"
#include "Monster.h"
#include "Player.h"

int main() {

	int mn;
	char *p;
	char player[256];
	p = player;

	List<Monster> test;
	Monster test2;
	test2.showName();
	test.add(test2);
	List<Monster>::Iterator k;
	for (k = test.begin(); k != test.end(); k++) {
		(*k).showName();
	}

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
	player1.setPositions();

	List<Monster>::Iterator i;
	List<Monster>::Iterator j;

	player1.showPosition();

	for (i = monsters.begin(); i != monsters.end(); i++) {
		(*i).showPosition();
		(*i).showName();
	}

	for (i = monsters.begin(); i != monsters.end(); i++) {
		if ((*i).pos == player1.pos) {
			monsters.kill(*i);
			std::cout << "you hit a Monster\n" << std::endl;
		}
	}

	for (i = monsters.begin(); i != monsters.end(); i++) {
		for (j = monsters.begin(); j != monsters.end(); j++) {
			if (i == j) continue;
			if ((*i).pos == (*j).pos) {
				monsters.kill(*i);
				monsters.kill(*j);
				std::cout << "two monsters are killed\n" << std::endl;
			}
		}
	}

	for (i = monsters.begin(); i != monsters.end(); i++) {
		(*i).showPosition();
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