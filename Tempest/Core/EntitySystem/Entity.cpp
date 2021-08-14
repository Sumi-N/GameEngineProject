#pragma  once
#include "Entity.h"

namespace Tempest
{

	Array<ObjectHandler>                       Entity::ObjectList{};
	Array<OwningPointer<Camera>>               Entity::Cameras{};
	Array<OwningPointer<PointLight>>           Entity::PointLightList{};
	Array<OwningPointer<MeshComponent>>        Entity::MeshComponentList{};
	Array<OwningPointer<EffectComponent>>      Entity::EffectComponentList{};

	OwningPointer<CubeMap>                     Entity::Skybox{};
	OwningPointer<AmbientLight>                Entity::Ambient{};
	OwningPointer<DirectionalLight>            Entity::Directional{};

	void Entity::Register(const OwningPointer<Object>& i_obj)
	{
		ObjectHandler objhandler(i_obj);
		ObjectList.PushBack(objhandler);
	}

	ObjectHandler Entity::Query(Object* i_obj)
	{
		for (auto it = ObjectList.Begin(); it != ObjectList.End(); ++it)
		{
			if (it->p == i_obj)
			{
				return *it;
			}
		}

		// Couldn't find the query object pointer
		DEBUG_ASSERT(false);
		DEBUG_PRINT("Couldn't find the query object pointer");
		return ObjectHandler(nullptr);
	}

	void Entity::RegisterCamera(const OwningPointer<Camera>& i_camera)
	{
		Cameras.PushBack(i_camera);
	}

	void Entity::RegisterSkyBox(const OwningPointer<CubeMap>& i_cubemap)
	{
		Skybox = i_cubemap;
	}

	void Entity::RegisterAmbientLight(const OwningPointer<AmbientLight>& i_ambient)
	{
		Ambient = i_ambient;
	}

	void Entity::RegisterDirectionalLight(const OwningPointer<DirectionalLight>& i_directional)
	{
		Directional = i_directional;
	}

	void Entity::RegisterPointLight(const OwningPointer<PointLight>& i_point)
	{
		PointLightList.PushBack(i_point);
	}

	void Entity::RegisterMeshComponent(const OwningPointer<MeshComponent>& i_component)
	{
		MeshComponentList.PushBack(i_component);
	}

	void Entity::RegisterEffectComponent(const OwningPointer<EffectComponent>& i_component)
	{
		EffectComponentList.PushBack(i_component);
	}

	void Entity::Boot()
	{
		// Check if camera exist, if not create one
		if (Entity::Cameras.Empty())
		{
			OwningPointer<Camera> camera;
			OwningPointer<Camera>::Create(camera);
			Cameras.PushBack(camera);
		}

		// Check if ambient light exist in a scene, if not create one
		if (!Entity::Ambient)
		{
			Entity::Ambient = OwningPointer<AmbientLight>::Create(Ambient);
			Entity::Ambient->intensity = Vec3f(0, 0, 0);
		}

		// Check if directional light exist in a scene, if not create one
		if (!Entity::Directional)
		{
			Entity::Directional = OwningPointer<DirectionalLight>::Create(Directional);
			Entity::Directional->intensity = Vec3f(0, 0, 0);
			Entity::Directional->direction = Vec3f(0,-1, 0);
		}

		// Check if point light exist in a scene, if not create one
		if (Entity::PointLightList.Size() == 0)
		{
			OwningPointer<PointLight> light_handler = OwningPointer<PointLight>::Create(light_handler);
			PointLightList.PushBack(light_handler);
		}

		//Boot sky box
		if (Skybox)
		{
			Skybox->Boot();
		}

		// Boot Lights
		if (Directional)
			Directional->Boot();
		for (auto it = PointLightList.Begin(); it != PointLightList.End(); ++it)
		{
			(*it)->Boot();
		}

		// Boot Object
		for (auto it = ObjectList.Begin(); it != ObjectList.End(); ++it)
		{
			(*it).p->Boot();
		}

		// Boot Mesh
		for (auto it = MeshComponentList.Begin(); it != MeshComponentList.End(); ++it)
		{
			(*it)->Boot();
		}

		// Boot Effect
		for (auto it = EffectComponentList.Begin(); it != EffectComponentList.End(); ++it)
		{
			(*it)->Boot();
		}
	}

	void Entity::Init()
	{
		// Init Object
		for (auto it = ObjectList.Begin(); it != ObjectList.End(); ++it)
		{
			(*it).p->Init();
		}

		// Init Mesh
		for (auto it = MeshComponentList.Begin(); it != MeshComponentList.End(); ++it)
		{
			(*it)->Init();
		}

		// Init Lights
		if (Directional)
			Directional->Init();
		for (auto it = PointLightList.Begin(); it != PointLightList.End(); ++it)
		{
			(*it)->Init();
		}

		// Init Cameras
		for (auto it = Cameras.Begin(); it != Cameras.End(); ++it)
		{
			(*it)->Init();
		}
	}

	void Entity::Update(float i_dt)
	{
		//Update Sky box
		if (Skybox)
		{
			Skybox->Update(i_dt);
		}

		// Update Object
		for (auto it = ObjectList.Begin(); it != ObjectList.End(); ++it)
		{
			(*it).p->Update(i_dt);
		}

		// Update Mesh
		for (auto it = MeshComponentList.Begin(); it != MeshComponentList.End(); ++it)
		{
			(*it)->Update(i_dt);
		}

		// Update Lights
		if (Directional)
			Directional->Update(i_dt);
		for (auto it = PointLightList.Begin(); it != PointLightList.End(); ++it)
		{
			(*it)->Update(i_dt);
		}

		// Update the main camera;
		if (Cameras[0])
		{
			Cameras[0]->Update(i_dt);
		}
	}

	void Entity::CleanUp()
	{
		for (auto it = ObjectList.Begin(); it != ObjectList.End(); ++it)
		{
			(*it).p->CleanUp();
		}
	}

	void Entity::SwapCamera(size_t index1, size_t index2)
	{
		std::swap(Cameras[index1], Cameras[index2]);
	}

}