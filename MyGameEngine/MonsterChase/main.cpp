#define _CRTDBG_MAP_ALLOC  
#include "Monster.h"
#include "MonsterController.h"
#include "Player.h"
#include "PlayerController.h"
#include "List.h"
#include "DebugLog.h"
#include "Allocator.h"
#include "Time.h"
#include "Physics2D.h"
#include "SpriteRenderer.h"

#include <Windows.h>
#include <crtdbg.h>  
#include <iostream>

#include "../GLib/GLib.h"

int monsterchase() {

	double a = 5.32;
	int b;
	b = static_cast<int>(a);
	printf("%d\n", b);

	int mn;
	int *deletelist;
	char *p;
	char player[256];
	p = player;

	std::cout << "choose the number of monster" << std::endl;
	std::cin >> mn;
	assert(typeid(mn).name() != "int");
	std::cout << "the number of monster pops up : " << mn << std::endl;
	std::cout << "type your player name" << std::endl;
	std::cin >> player;

	List<MonsterController*> monstercontrollers;

	for (int i = 0; i < mn; i++) {
		Monster* monster = new Monster;
		monster->randomName(2);
		MonsterController * mcontroller = new MonsterController(monster);
		monstercontrollers.add(mcontroller);
	}
	deletelist = new int[mn];
	int * headofdelete = deletelist;

	Player * sumi = new Player;
	sumi->setName(p);
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
			MonsterController * mcontroller = new MonsterController(monster);
			monstercontrollers.add(mcontroller);
		}

		for (int i = 0; i < monstercontrollers.length(); i++) {
			monstercontrollers.get(i)->object->show();
		}
		pcontroller.object->show();
		printf("%d\n", monstercontrollers.length());

		std::cout << "press \' a\' to move right \'d\' to move left \'w\' to move up \'s\' to move down \'q\' to quit this game" << std::endl;
		std::cin >> order;

		pcontroller.moveByOrder(order);
		for (int i = 0; i < monstercontrollers.length(); i++) {
			monstercontrollers.get(i)->moveRandomly();
		}
		count = 0;
		for (int i = 0; i < monstercontrollers.length(); i++) {
			if (monstercontrollers.get(i)->object->pos == pcontroller.object->pos) {
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
				if (monstercontrollers.get(i)->object->pos == monstercontrollers.get(j)->object->pos) {
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
#include "CharacterString_UnitTest.h"

/*
int main() {
	//HeapManager_UnitTest();
	monsterchase();
	//UnitTest::CharacterString_UnitTest();
	_CrtDumpMemoryLeaks();
	return 0;
}
*/

Object2D * obj1 = new Object2D();
Object2D * obj2 = new Object2D();
Physics2D * phy1 = new Physics2D(obj1);

void TestKeyCallback(unsigned int i_VKeyID, bool bWentDown)
{
#ifdef _DEBUG
	const size_t	lenBuffer = 65;
	char			Buffer[lenBuffer];

	//sprintf_s(Buffer, lenBuffer, "VKey 0x%04x went %s\n", i_VKeyID, bWentDown ? "down" : "up");
	sprintf_s(Buffer, lenBuffer, "VKey %d went %s\n", i_VKeyID, bWentDown ? "down" : "up");
	OutputDebugStringA(Buffer);
#endif // __DEBUG

	if (i_VKeyID == 32) {
		phy1->addForce(Vector2D<double, double>(25, 0));
	}
}

int WINAPI wWinMain(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, PWSTR pCmdLine, int i_nCmdShow) {
	// IMPORTANT: first we need to initialize GLib
	bool bSuccess = GLib::Initialize(i_hInstance, i_nCmdShow, "GLibTest", -1, 1200, 600);

	if (bSuccess)
	{
		Timer::Init();
		obj1->setPosition(-220, -100);
		obj2->setPosition(180, -100);

		// Create a couple of sprites using our own helper routine CreateSprite
		SpriteRenderer GoodGuy;
		GoodGuy.createSprite("..\\GlibTest\\data\\GoodGuy.dds");
		SpriteRenderer BadGuy;
		BadGuy.createSprite("..\\GlibTest\\data\\BadGuy.dds");

		GoodGuy.obj = obj1;
		BadGuy.obj = obj2;

		// IMPORTANT (if we want keypress info from GLib): Set a callback for notification of key presses
		GLib::SetKeyStateChangeCallback(TestKeyCallback);

		bool bQuit = false;
		do
		{
			Timer::Run();

			// IMPORTANT: We need to let GLib do it's thing. 
			GLib::Service(bQuit);

			if (!bQuit)
			{
				// IMPORTANT: Tell GLib that we want to start rendering
				GLib::BeginRendering();
				// Tell GLib that we want to render some sprites
				GLib::Sprites::BeginRendering();

				if (GoodGuy.sprite)
				{
					phy1->update(Time::dt);
					GoodGuy.update();
				}
				if (BadGuy.sprite)
				{
					// Tell GLib to render this sprite at our calculated location
					BadGuy.update();
				}

				// Tell GLib we're done rendering sprites
				GLib::Sprites::EndRendering();
				// IMPORTANT: Tell GLib we're done rendering
				GLib::EndRendering();
			}
		} while (bQuit == false);

		GoodGuy.release();
		BadGuy.release();

		// IMPORTANT:  Tell GLib to shutdown, releasing resources.
		GLib::Shutdown();
	}

#if defined _DEBUG
	_CrtDumpMemoryLeaks();
#endif // _DEBUG
}
