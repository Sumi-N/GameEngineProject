#pragma  once
#include "Entity.h"

std::vector<ObjectHandler> Entity::ObjectList;
std::vector<OwningPointer<MeshComponent>> Entity::MeshComponentList;
std::vector<OwningPointer<PointLight>> Entity::PointLightList;
std::vector<OwningPointer<DirectionalLight>> Entity::DirectionalLightList;
OwningPointer<AmbientLight> Entity::Ambient;
OwningPointer<Camera>      Entity::CurrentCamera;

ObjectHandler Entity::Register(Object * i_obj)
{
	ObjectHandler objhandler(i_obj);
	ObjectList.push_back(objhandler);
	return objhandler;
}

void Entity::RegisterCamera(Camera* i_camera)
{
	CurrentCamera = i_camera;
}

void Entity::RegisterAmbientLight(AmbientLight* i_ambient)
{
	Ambient = i_ambient;
}

void Entity::RegisterPointLight(PointLight* i_point)
{
	OwningPointer<PointLight> light_handler;
	light_handler = i_point;
	PointLightList.push_back(light_handler);
}

void Entity::RegisterDirectionalLight(DirectionalLight* i_directional)
{
	OwningPointer<DirectionalLight> light_handler;
	light_handler = i_directional;
	DirectionalLightList.push_back(light_handler);
}

void Entity::RegisterMeshComponent(MeshComponent * i_component)
{
	OwningPointer<MeshComponent> mesh_handler;
	mesh_handler = i_component;
	MeshComponentList.push_back(mesh_handler);
}

void Entity::Init()
{
	for (auto it = ObjectList.begin(); it != ObjectList.end(); ++it)
	{
		(*it).p->Init();
	}
}

void Entity::Update(float i_dt)
{
	// Update Object
	for (auto it = ObjectList.begin(); it != ObjectList.end(); ++it)
	{
		(*it).p->Update(i_dt);
	}

	// Update Mesh
	for (auto it = MeshComponentList.begin(); it != MeshComponentList.end(); ++it)
	{
		(*it)->Update(i_dt);
	}

	if(CurrentCamera)
		CurrentCamera->Update(i_dt);
}

void Entity::CleanUp()
{
	for (auto it = ObjectList.begin(); it != ObjectList.end(); ++it)
	{
		(*it).p->CleanUp();
	}
}
