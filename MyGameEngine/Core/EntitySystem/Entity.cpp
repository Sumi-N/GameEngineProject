#pragma  once
#include "Entity.h"

std::vector<ObjectHandler>                Entity::ObjectList;
std::vector<OwningPointer<MeshComponent>> Entity::MeshComponentList;
std::vector<OwningPointer<PointLight>>    Entity::PointLightList;
OwningPointer<DirectionalLight>           Entity::Directional;
OwningPointer<AmbientLight>               Entity::Ambient;
OwningPointer<Camera>                     Entity::CurrentCamera;
OwningPointer<CubeMapMeshComponent>       Entity::SkyBox;

ObjectHandler Entity::Register(Object * i_obj)
{
	ObjectHandler objhandler(i_obj);
	ObjectList.push_back(objhandler);
	return objhandler;
}

ObjectHandler Entity::Query(Object* i_obj)
{
	for (auto it = ObjectList.begin(); it != ObjectList.end(); ++it)
	{
		if (it->p == i_obj)
		{
			return *it;
		}
	}

	DEBUG_PRINT("Couldn't find the query object pointer");
	return ObjectHandler(nullptr);
}

void Entity::RegisterCamera(Camera* i_camera)
{
	CurrentCamera = i_camera;
}

void Entity::RegisterAmbientLight(AmbientLight* i_ambient)
{
	Ambient = i_ambient;
}

void Entity::RegisterDirectionalLight(DirectionalLight* i_directional)
{
	Directional = i_directional;
}

void Entity::RegisterPointLight(PointLight* i_point)
{
	OwningPointer<PointLight> light_handler;
	light_handler = i_point;
	PointLightList.push_back(light_handler);
}

void Entity::RegisterSkyBox(CubeMapMeshComponent* i_skybox)
{
	SkyBox = i_skybox;
}

void Entity::RegisterMeshComponent(MeshComponent * i_component)
{
	OwningPointer<MeshComponent> mesh_handler;
	mesh_handler = i_component;
	MeshComponentList.push_back(mesh_handler);
}

void Entity::Boot()
{
	if (SkyBox)
	{
		SkyBox->Boot();
	}

	// Boot Object
	for (auto it = ObjectList.begin(); it != ObjectList.end(); ++it)
	{
		(*it).p->Boot();
	}

	// Boot Mesh
	for (auto it = MeshComponentList.begin(); it != MeshComponentList.end(); ++it)
	{
		(*it)->Boot();
	}

	// Boot Lights
	if (Directional)
		Directional->Boot();
	for (auto it = PointLightList.begin(); it != PointLightList.end(); ++it)
	{
		(*it)->Boot();
	}
}

void Entity::Init()
{
	if (SkyBox)
	{
		SkyBox->Init();
	}

	// Init Object
	for (auto it = ObjectList.begin(); it != ObjectList.end(); ++it)
	{
		(*it).p->Init();
	}

	// Init Mesh
	for (auto it = MeshComponentList.begin(); it != MeshComponentList.end(); ++it)
	{
		(*it)->Init();
	}

	// Init Lights
	if (Directional)
		Directional->Init();
	for (auto it = PointLightList.begin(); it != PointLightList.end(); ++it)
	{
		(*it)->Init();
	}

	if (CurrentCamera)
		CurrentCamera->Init();
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

	// Update Lights
	if(Directional)
		Directional->Update(i_dt);
	for (auto it = PointLightList.begin(); it != PointLightList.end(); ++it)
	{
		(*it)->Update(i_dt);
	}

	// Update Camera;
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
