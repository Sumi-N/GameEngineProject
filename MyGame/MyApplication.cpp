#pragma  once

#include <Application/Application.h>
#include <Application/EntryPoint.h>
#include "TestScenes.h"



class MyApplication : public Tempest::Application
{
public:
	MyApplication();
	~MyApplication(){};
};

MyApplication::MyApplication()
{
	//TestScene::PBR_9Balls();
	//TestScene::PBR_Red_Balls();
	TestScene::PhoneBlinn_Teapots();
	//TestScene::PhoneBlinn_Lights();
	//TestScene::Normal_Debug_Plane();

	//TestScene::Two_Cameras();

	Tempest::Application::Execute();
}


Tempest::Application* Tempest::Create()
{
	return new MyApplication();
}