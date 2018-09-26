#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>  
#include<iostream>
#include "Monster.h"
#include "Player.h"
#include "List.h"
#include "DebugLog.h"


int test() {
	DEBUG_PRINT("hello world");

	int mn;
	char *p;
	char player[256];
	p = player;

	std::cout << "choose the number of monster" << std::endl;
	std::cin >> mn;
	assert(typeid(mn).name() != "int");
	std::cout << "the number of monster pops up : " << mn << std::endl;
	std::cout << "type your player name" << std::endl;
	std::cin >> player;
	std::cout << "your name is " << player << std::endl;

	List<Monster*> monsters;

	for (int i = 0; i < mn; i++) {
		Monster* monster = new Monster;
		monster->randomName(10);
		monster->setPositions();
		monsters.add(monster);
	}


	Player sumi;
	sumi.setName(p);
	sumi.showName();

	
	int turncount = 0;
	char order = 'p';
	while (order != 'q') {

		if (turncount != 3) {
			turncount++;
		}
		else {
			turncount = 0;
			Monster* monster = new Monster;
			monster->randomName(10);
			monster->setPositions();
			monsters.add(monster);
		}

		for (int i = 0; i < monsters.length(); i++) {
			monsters.get(i)->showName();
			monsters.get(i)->showPosition();
		}
		sumi.showPosition();
		printf("%d\n", monsters.length());

		std::cout << "press \' a\' to move right \'d\' to move left \'w\' to move up \'s\' to move down \'q\' to quit this game" << std::endl;
		std::cin >> order;

		sumi.move(order);

		int i = 0;
		while (true) {
			if (i >= monsters.length()) break;
			monsters.get(i)->move();
			if (monsters.get(i)->pos == sumi.pos) {
				monsters.remove(monsters.get(i));
			}
			
			i++;
		}

		
		for (int i = 0; i < monsters.length(); i++) {
			for (int j = i; j < monsters.length(); j++) {
				if (monsters.get(i)->pos == monsters.get(j)->pos) {
					if (i == j) continue;
					monsters.remove(monsters.get(i));
					monsters.remove(monsters.get(j));
				}
			}
		}
	}
	return 0;
}

int main() {
	test();
	_CrtDumpMemoryLeaks();
	return 0;
}