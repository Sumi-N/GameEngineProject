#pragma  once

#include <Application/Application.h>
#include <Application/EntryPoint.h>
#include "MyCameraObject.h"



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
	Owner<Object> camera = Create<MyCameraObject>();
	Entity::Register(camera);

	Owner<Object> model = Create<Object>();
	model->Translate(Vec3f(0, -20, -70));
	model->scale = 0.35f;
	Owner<MeshComponent> mesh_component = Create<MeshComponent>();
	mesh_component->owner = model;
	Entity::RegisterMeshComponent(mesh_component);
 	Entity::Register(model);

	return new MyApplication();
}