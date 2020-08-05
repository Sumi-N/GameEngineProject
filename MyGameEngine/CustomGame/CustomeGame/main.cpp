#pragma once

#include <Core/Thread/EntryPoint.h>
#include <Logging/MemoryLeakDetection.h>

#include "TestScenes.h"

int main()
{

	MEMORY_LEAK_DETECTION
	//Entity::RegisterCamera(ObjectFactory<MyCamera>::Create());
	//TestScene::PBR_9Balls();
	//TestScene::PBR_Red_Balls();
	//TestScene::PhoneBlinn_Teapots();
	//TestScene::PhoneBlinn_Lights();
	//TestScene::Normal_Debug_Plane();
	TestScene::Two_Cameras();


	System::Boot();

	System::Start();

	return 0;
};