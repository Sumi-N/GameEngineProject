#pragma once

#include <Core/Thread/EntryPoint.h>
#include <EntitySystem/Entity.h>
#include <Debug/MemoryLeakDetection.h>


#include "TestScenes.h"

int main()
{

	MEMORY_LEAK_DETECTION

	//TestScene::PBR_9Balls();
	TestScene::PBR_Red_Balls();
	//TestScene::PhoneBlinn_Teapots();
	//TestScene::PhoneBlinn_Lights();
	//TestScene::Normal_Debug_Plane();


	System::Boot();

	System::Start();

	return 0;
};