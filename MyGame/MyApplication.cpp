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
	Tempest::Application::Execute();
}


Tempest::Application* Tempest::Create()
{
	return new MyApplication();
}