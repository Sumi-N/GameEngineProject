#pragma  once

#include <Application/Application.h>
#include <Application/EntryPoint.h>
#include "TestScenes.h"



class MyApplication : public Application
{
public:
	MyApplication();
	~MyApplication(){};
};

MyApplication::MyApplication()
{
	//TestScene::Importer();
	//TestScene::PBR_9Balls();
	TestScene::PBR_Red_Balls();
	//TestScene::PhoneBlinn_Teapots();
	//TestScene::PhoneBlinn_Lights();
	//TestScene::Normal_Debug_Plane();

	//TestScene::Two_Cameras();

	Execute();
}


Application* Create()
{
	return new MyApplication();
}