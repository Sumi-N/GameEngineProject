#pragma  once

#include <Application/Application.h>
#include <Application/EntryPoint.h>



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