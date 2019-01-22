#define _CRTDBG_MAP_ALLOC  
#include "Monster.h"
#include "MonsterController.h"
#include "Player.h"
#include "PlayerController.h"
#include "List.h"
#include "DebugLog.h"
#include "HeapManager.h"
#include "Allocator.h"
#include "Time.h"
#include "Physics2D.h"

#include <Windows.h>
#include <crtdbg.h>  
#include <iostream>

#include "../GLib/GLib.h"

int monsterchase() {

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

	List<MonsterController*> monstercontrollers;

	for (int i = 0; i < mn; i++) {
		Monster* monster = new(pHeapManager) Monster;
		monster->randomName(10);
		MonsterController * mcontroller = new(pHeapManager) MonsterController(*monster);
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
			Monster* monster = new(pHeapManager) Monster;
			monster->randomName(10);
			MonsterController * mcontroller = new(pHeapManager) MonsterController(*monster);
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

/*
int main() {
	//HeapManager_UnitTest();
	monsterchase();
	_CrtDumpMemoryLeaks();
	return 0;
}
*/

void TestKeyCallback(unsigned int i_VKeyID, bool bWentDown)
{
#ifdef _DEBUG
	const size_t	lenBuffer = 65;
	char			Buffer[lenBuffer];

	//sprintf_s(Buffer, lenBuffer, "VKey 0x%04x went %s\n", i_VKeyID, bWentDown ? "down" : "up");
	sprintf_s(Buffer, lenBuffer, "VKey %d went %s\n", i_VKeyID, bWentDown ? "down" : "up");
	OutputDebugStringA(Buffer);
#endif // __DEBUG
}

void MakeAccelation(unsigned int i_VkeyID, bool bWentDown) {
	if (i_VkeyID == 32) {
		//DEBUG_PRINT("not hello");
		//acc = 0.01;
	}
}

void * LoadFile(const char * i_pFilename, size_t & o_sizeFile)
{
	assert(i_pFilename != NULL);

	FILE * pFile = NULL;

	errno_t fopenError = fopen_s(&pFile, i_pFilename, "rb");
	if (fopenError != 0)
		return NULL;

	assert(pFile != NULL);

	int FileIOError = fseek(pFile, 0, SEEK_END);
	assert(FileIOError == 0);

	long FileSize = ftell(pFile);
	assert(FileSize >= 0);

	FileIOError = fseek(pFile, 0, SEEK_SET);
	assert(FileIOError == 0);

	uint8_t * pBuffer = new uint8_t[FileSize];
	assert(pBuffer);

	size_t FileRead = fread(pBuffer, 1, FileSize, pFile);
	assert(FileRead == FileSize);

	fclose(pFile);

	o_sizeFile = FileSize;

	return pBuffer;
}

GLib::Sprites::Sprite * CreateSprite(const char * i_pFilename)
{
	assert(i_pFilename);

	size_t sizeTextureFile = 0;

	// Load the source file (texture data)
	void * pTextureFile = LoadFile(i_pFilename, sizeTextureFile);

	// Ask GLib to create a texture out of the data (assuming it was loaded successfully)
	GLib::Texture * pTexture = pTextureFile ? GLib::CreateTexture(pTextureFile, sizeTextureFile) : nullptr;

	// exit if something didn't work
	// probably need some debug logging in here!!!!
	if (pTextureFile)
		delete[] pTextureFile;

	if (pTexture == nullptr)
		return NULL;

	unsigned int width = 0;
	unsigned int height = 0;
	unsigned int depth = 0;

	// Get the dimensions of the texture. We'll use this to determine how big it is on screen
	bool result = GLib::GetDimensions(pTexture, width, height, depth);
	assert(result == true);
	assert((width > 0) && (height > 0));

	// Define the sprite edges
	GLib::Sprites::SpriteEdges	Edges = { -float(width / 2.0f), float(height), float(width / 2.0f), 0.0f };
	GLib::Sprites::SpriteUVs	UVs = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 0.0f, 1.0f }, { 1.0f, 1.0f } };
	GLib::RGBA							Color = { 255, 255, 255, 255 };

	// Create the sprite
	GLib::Sprites::Sprite * pSprite = GLib::Sprites::CreateSprite(Edges, 0.1f, Color, UVs);
	if (pSprite == nullptr)
	{
		GLib::Release(pTexture);
		return nullptr;
	}

	// Bind the texture to sprite
	GLib::Sprites::SetTexture(*pSprite, *pTexture);

	return pSprite;
}

int WINAPI wWinMain(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, PWSTR pCmdLine, int i_nCmdShow) {
	// IMPORTANT: first we need to initialize GLib
	bool bSuccess = GLib::Initialize(i_hInstance, i_nCmdShow, "GLibTest", -1, 1200, 600);

	if (bSuccess)
	{
		// IMPORTANT (if we want keypress info from GLib): Set a callback for notification of key presses
		GLib::SetKeyStateChangeCallback(TestKeyCallback);
		GLib::SetKeyStateChangeCallback(MakeAccelation);

		// Create a couple of sprites using our own helper routine CreateSprite
		GLib::Sprites::Sprite * pGoodGuy = CreateSprite("..\\GlibTest\\data\\GoodGuy.dds");
		GLib::Sprites::Sprite * pBadGuy = CreateSprite("..\\GlibTest\\data\\BadGuy.dds");

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

				if (pGoodGuy)
				{
					static float			moveDist = .01f;
					static float			moveDir = moveDist;

					pos.setX(Offset.x);
					pos.setY(Offset.y);
					cal.Update(pos,vel,acc,dt);
					Offset.x = (float)(pos.x());
					Offset.y = (float)(pos.y());
					//DEBUG_PRINT("the velocity is %f",vel.x());
					//if (Offset.x < -220.0f)
					//	moveDir = moveDist;
					//else if (Offset.x > -140.0f)
					//	moveDir = -moveDist;

					//Offset.x += moveDir;

					// Tell GLib to render this sprite at our calculated location
					GLib::Sprites::RenderSprite(*pGoodGuy, Offset, 0.0f);
				}
				if (pBadGuy)
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
					GLib::Sprites::RenderSprite(*pBadGuy, Offset, 0.0f);
				}

				// Tell GLib we're done rendering sprites
				GLib::Sprites::EndRendering();
				// IMPORTANT: Tell GLib we're done rendering
				GLib::EndRendering();
			}
		} while (bQuit == false);

		if (pGoodGuy)
			GLib::Sprites::Release(pGoodGuy);
		if (pBadGuy)
			GLib::Sprites::Release(pBadGuy);

		// IMPORTANT:  Tell GLib to shutdown, releasing resources.
		GLib::Shutdown();
	}

#if defined _DEBUG
	_CrtDumpMemoryLeaks();
#endif // _DEBUG
}