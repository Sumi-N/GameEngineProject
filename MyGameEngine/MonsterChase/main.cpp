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

int WINAPI wWinMain(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, PWSTR pCmdLine, int i_nCmdShow) {

	// IMPORTANT: first we need to initialize GLib
	bool bSuccess = GLib::Initialize(i_hInstance, i_nCmdShow, "GLibTest", -1, 1200, 600);

	if (bSuccess)
	{
		// IMPORTANT (if we want keypress info from GLib): Set a callback for notification of key presses
		//GLib::SetKeyStateChangeCallback(TestKeyCallback);
		//GLib::SetKeyStateChangeCallback(MakeAccelation);

		// Create a couple of sprites using our own helper routine CreateSprite
		SpriteRenderer GoodGuy;
		GoodGuy.createSprite("..\\GlibTest\\data\\GoodGuy.dds");
		SpriteRenderer BadGuy;
		BadGuy.createSprite("..\\GlibTest\\data\\BadGuy.dds");

		bool bQuit = false;


		Timer::Init();

		Physics2D cal;
		Vector2D<double, double> pos = Vector2D<double, double>(0, 0);
		Vector2D<double, double> vel = Vector2D<double,double>(0,0);
		Vector2D<double, double> acc = Vector2D<double, double>(0.0005, 0);
		static GLib::Point2D	Offset = { -220.0f, -100.0f };
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
					static float			moveDist = .01f;
					static float			moveDir = moveDist;

					pos.x = Offset.x;
					pos.y = Offset.y;
					cal.Update(pos,vel,acc,dt);
					Offset.x = (float)pos.x;
					Offset.y = (float)pos.y;

					// Tell GLib to render this sprite at our calculated location
					GLib::Sprites::RenderSprite(*(GoodGuy.sprite), Offset, 0.0f);
				}
				if (BadGuy.sprite)
				{
					static float			moveDist = .02f;
					static float			moveDir = -moveDist;

					static GLib::Point2D	Offset = { 180.0f, -100.0f };

					if (Offset.x > 200.0f)
						moveDir = -moveDist;
					else if (Offset.x < 160.0f)
						moveDir = moveDist;

					Offset.x += moveDir;

					// Tell GLib to render this sprite at our calculated location
					GLib::Sprites::RenderSprite(*(BadGuy.sprite), Offset, 0.0f);
				}

				// Tell GLib we're done rendering sprites
				GLib::Sprites::EndRendering();
				// IMPORTANT: Tell GLib we're done rendering
				GLib::EndRendering();
			}
		} while (bQuit == false);

		if (GoodGuy.sprite)
			GLib::Sprites::Release(GoodGuy.sprite);
		if (BadGuy.sprite)
			GLib::Sprites::Release(BadGuy.sprite);

		// IMPORTANT:  Tell GLib to shutdown, releasing resources.
		GLib::Shutdown();
	}

#if defined _DEBUG
	_CrtDumpMemoryLeaks();
#endif // _DEBUG
}
