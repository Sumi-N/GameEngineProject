#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>  
#include<iostream>
#include "Monster.h"
#include "MonsterController.h"
#include "Player.h"
#include "PlayerController.h"
#include "List.h"
#include "DebugLog.h"
#include <Windows.h>


int monsterchase() {
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
		if (player[i] == '\0') {
			namelength = i;
			
		}
	}

	List<MonsterController*> monstercontrollers;

	for (int i = 0; i < mn; i++) {
		Monster* monster = new Monster;
		monster->randomName(10);
		MonsterController * mcontroller = new MonsterController(*monster);
		monstercontrollers.add(mcontroller);
		delete monster;
	}
	deletelist = new int[mn];
	int * headofdelete = deletelist;


	Player sumi;
	sumi.setName(p, namelength);
	PlayerController pcontroller = PlayerController(sumi);
	

	
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
			MonsterController * mcontroller = new MonsterController(*monster);
			monstercontrollers.add(mcontroller);
			delete monster;
		}

		for (int i = 0; i < monstercontrollers.length(); i++) {
			monstercontrollers.get(i)->object.showPosition();
		}
		pcontroller.object.showPosition();
		printf("%d\n", monstercontrollers.length());

		std::cout << "press \' a\' to move right \'d\' to move left \'w\' to move up \'s\' to move down \'q\' to quit this game" << std::endl;
		std::cin >> order;

		pcontroller.moveByOrder(order);
		for (int i = 0; i < monstercontrollers.length(); i++) {
			monstercontrollers.get(i)->moveRandomly();
		}
		count = 0;
		for (int i = 0; i < monstercontrollers.length(); i++) {
			if (monstercontrollers.get(i)->object.pos == pcontroller.object.pos) {
				*(deletelist + count) = i;
				printf("monster deleted\n");
				count++;
			}
		}
		int hosei = 0;
		for (int i = 0; i < count; i++) {
			monstercontrollers.remove(monstercontrollers.get(*(deletelist + i) - hosei));
			hosei++;
		}

		count = 0;
		for (int i = 0; i < monstercontrollers.length(); i++) {
			for (int j = i; j < monstercontrollers.length(); j++) {
				if (monstercontrollers.get(i)->object.pos == monstercontrollers.get(j)->object.pos) {
					if (i == j) continue;
					*(deletelist + count) = i;
					printf("monster deleted\n");
					count++;
					break;
				}
			}
		}

		int hosei2 = 0;
		for (int i = 0; i < count; i++) {
			monstercontrollers.remove(monstercontrollers.get(*(deletelist + i) - hosei2));
			hosei2++;
		}
	}

	delete[] headofdelete;
	return 0;
}

#include <conio.h>
extern bool HeapManager_UnitTest();

int main() {
	//HeapManager_UnitTest();
	monsterchase();
	_CrtDumpMemoryLeaks();
	return 0;
}