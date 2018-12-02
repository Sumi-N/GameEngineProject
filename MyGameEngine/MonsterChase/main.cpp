#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>  
#include<iostream>
#include "Monster.h"
#include "Player.h"
#include "List.h"
#include "DebugLog.h"
#include <Windows.h>


int test() {
	DEBUG_PRINT("hello world");

	int mn;
	int *deletelist;
	char *p;
	char player[256];
	int namelength;
	p = player;

	std::cout << "choose the number of monster" << std::endl;
	std::cin >> mn;
	assert(typeid(mn).name() != "int");
	std::cout << "the number of monster pops up : " << mn << std::endl;
	std::cout << "type your player name" << std::endl;
	std::cin >> player;
	//std::cout << "your name is " << player << std::endl;

	for (int i = 0; i < 256; i++) {
		if (player[i] == '\0' || player[i] == ' ') {
			namelength = i;
			break;
		}
	}

	char * newp = new char[namelength + 1]();
	for (int i = 0; i<namelength; i++) {
		newp[i] = player[i];
	}
	newp[namelength] = '\n';

	List<Monster*> monsters;

	for (int i = 0; i < mn; i++) {
		Monster* monster = new Monster;
		monster->randomName(10);
		monster->setPositions();
		monsters.add(monster);
	}
	deletelist = new int[mn];
	int * headofdelete = deletelist;


	Player sumi;
	sumi.setName(newp);
	sumi.setPositions();
	sumi.showName();
	sumi.namelength = namelength+1;
	//printf("hello %d\n", namelength);

	
	int turncount = 0;
	char order = 'p';
	int count;
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
		for (int i = 0; i < monsters.length(); i++) {
			monsters.get(i)->move();
		}

		count = 0;
		for (int i = 0; i < monsters.length(); i++) {
			if (monsters.get(i)->pos == sumi.pos) {
				*(deletelist + count) = i;
				//printf("player vs the monster who will deleted is %d\n",i);
				count++;
			}
		}
		int hosei = 0;
		for (int i = 0; i < count; i++) {
			monsters.remove(monsters.get(*(deletelist + i) - hosei));
			//printf("player vs the monster is actually deleted is %d\n",*(deletelist + i) - hosei);
		}

		count = 0;
		for (int i = 0; i < monsters.length(); i++) {
			for (int j = i; j < monsters.length(); j++) {
				if (monsters.get(i)->pos == monsters.get(j)->pos) {
					if (i == j) continue;
					*(deletelist + count) = i;
					//printf("the monster who will deleted is %d\n", i);
					count++;
					break;
				}
			}
		}

		for (int i = 0; i < count; i++) {
			monsters.remove(monsters.get(*(deletelist + i)));
			//printf("the monster is actually deleted is %d\n", *(deletelist + i) + hosei2);
		}
	}

	delete[] headofdelete;
	return 0;
}

#include <conio.h>
extern bool HeapManager_UnitTest();

int main() {
	test();
	//_CrtDumpMemoryLeaks();
	//HeapManager_UnitTest();
	//_getch();
	return 0;
}