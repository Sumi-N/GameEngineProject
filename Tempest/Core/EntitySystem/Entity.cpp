#pragma  once
#include "Entity.h"

namespace Tempest
{
	Array<ObjectHandler>               Entity::ObjectList{};
	Array<Owner<CameraObject>>         Entity::CamerasObjects{};
	Array<Owner<PointLight>>           Entity::PointLightList{};
	Array<Owner<MeshComponent>>        Entity::MeshComponentList{};
	Array<Owner<EffectComponent>>      Entity::EffectComponentList{};	

	Owner<CubeMap>                     Entity::Skybox{};
	Owner<AmbientLight>                Entity::Ambient{};
	Owner<DirectionalLight>            Entity::Directional{};

	AnimationSystem                    Entity::Animation{};

	void Entity::Register(const Owner<Object>& i_obj)
	{
		ObjectHandler objhandler(i_obj);
		ObjectList.PushBack(objhandler);
	}

	void Entity::Register(const Owner<Object>& i_obj, String i_name)
	{
		ObjectHandler objhandler(i_obj, i_name);
		ObjectList.PushBack(objhandler);
	}

	Owner<Object> Entity::Query(Object* i_obj)
	{
		for (auto it = ObjectList.Begin(); it != ObjectList.End(); ++it)
		{
			if (it->p == i_obj)
			{
				return it->p;
			}
		}

		// Couldn't find the query object pointer
		DEBUG_ASSERT(false);
		DEBUG_PRINT("Couldn't find the query object pointer");
		return Owner<Object>();
	}

	void Entity::RegisterCamera(const Owner<CameraObject>& i_camera)
	{
		CamerasObjects.PushBack(i_camera);
	}

	void Entity::RegisterSkyBox(const Owner<CubeMap>& i_cubemap)
	{
		Skybox = i_cubemap;
	}

	void Entity::RegisterAmbientLight(const Owner<AmbientLight>& i_ambient)
	{
		Ambient = i_ambient;
	}

	void Entity::RegisterDirectionalLight(const Owner<DirectionalLight>& i_directional)
	{
		Directional = i_directional;
	}

	void Entity::RegisterPointLight(const Owner<PointLight>& i_point)
	{
		PointLightList.PushBack(i_point);
	}

	void Entity::RegisterMeshComponent(const Owner<MeshComponent>& i_component)
	{
		MeshComponentList.PushBack(i_component);
	}

	void Entity::RegisterEffectComponent(const Owner<EffectComponent>& i_component)
	{
		EffectComponentList.PushBack(i_component);
	}

	void Entity::RegisterAnimationComponent(const Owner<AnimationComponent>& i_component)
	{
		Entity::Animation.Register(i_component);
	}

	void Entity::Boot()
	{
		// Check if camera exist, if not create one
		if (Entity::CamerasObjects.Empty())
		{
			Owner<CameraObject> camera;
			Owner<CameraObject>::Create(camera);
			CamerasObjects.PushBack(camera);
		}

		// Check if ambient light exist in a scene, if not create one
		if (!Entity::Ambient)
		{
			Entity::Ambient = Owner<AmbientLight>::Create(Ambient);
			Entity::Ambient->intensity = Vec3f(0, 0, 0);
		}

		// Check if directional light exist in a scene, if not create one
		if (!Entity::Directional)
		{
			Entity::Directional = Owner<DirectionalLight>::Create(Directional);
			Entity::Directional->intensity = Vec3f(0, 0, 0);
			Entity::Directional->direction = Vec3f(0,-1, 0);
		}

		// Check if point light exist in a scene, if not create one
		if (Entity::PointLightList.Size() == 0)
		{
			Owner<PointLight> light_handler = Owner<PointLight>::Create(light_handler);
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

		Animation.Boot();
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
		for (auto it = CamerasObjects.Begin(); it != CamerasObjects.End(); ++it)
		{
			(*it)->Init();
		}

		Animation.Init();
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
		if (CamerasObjects[0])
		{
			CamerasObjects[0]->Update(i_dt);
		}

		Animation.Update(i_dt);
	}

	void Entity::CleanUp()
	{
		for (auto it = ObjectList.Begin(); it != ObjectList.End(); ++it)
		{
			(*it).p->CleanUp();
		}

		Animation.CleanUp();
	}

	void Entity::SwapCamera(size_t index1, size_t index2)
	{
		std::swap(CamerasObjects[index1], CamerasObjects[index2]);
	}

}