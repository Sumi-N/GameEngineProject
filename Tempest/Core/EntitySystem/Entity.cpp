#pragma  once
#include "Entity.h"

namespace Tempest
{
	Array<Owner<Object>>               Entity::ObjectList{};
	Array<Owner<CameraComponent>>      Entity::CameraComponentList{};
	Array<Owner<LightComponent>>       Entity::LightComponentList{};
	Array<Owner<MeshComponent>>        Entity::MeshComponentList{};
	Array<Owner<EffectComponent>>      Entity::EffectComponentList{};
	Array<Owner<BackgroundComponent>>  Entity::BackgroundComponentList{};

	AnimationSystem                    Entity::Animation{};

	void Entity::Register(const Owner<Object>& i_obj)
	{		
		ObjectList.PushBack(i_obj);
	}

	Owner<Object> Entity::Query(Object* i_obj)
	{
		for (auto it = ObjectList.Begin(); it != ObjectList.End(); ++it)
		{
			if (*it == i_obj)
			{
				return *it;
			}
		}

		// Couldn't find the query object pointer
		DEBUG_ASSERT(false);
		DEBUG_PRINT("Couldn't find the query object pointer");
		return Owner<Object>();
	}

	void Entity::RegisterCameraComponent(const Owner<CameraComponent>& i_camera)
	{
		CameraComponentList.PushBack(i_camera);
	}

	void Entity::RegisterLightComponent(const Owner<LightComponent>& i_point)
	{
		LightComponentList.PushBack(i_point);
	}

	void Entity::RegisterMeshComponent(const Owner<MeshComponent>& i_component)
	{
		MeshComponentList.PushBack(i_component);
	}

	void Entity::RegisterEffectComponent(const Owner<EffectComponent>& i_component)
	{
		EffectComponentList.PushBack(i_component);
	}

	void Entity::RegisterBackgroundComponent(const Owner<BackgroundComponent>& i_component)
	{
		BackgroundComponentList.PushBack(i_component);
	}

	void Entity::RegisterAnimationComponent(const Owner<AnimationComponent>& i_component)
	{
		Entity::Animation.Register(i_component);
	}	

	void Entity::Boot()
	{
		// Check if camera exist, if not create one
		if (Entity::CameraComponentList.Empty())
		{
			//Owner<CameraObject> camera;
			//Owner<CameraObject>::Create(camera);
			//CamerasObjects.PushBack(camera);
		}

		// Check if ambient light exist in a scene, if not create one
		//if (!Entity::Ambient)
		//{
		//	Entity::Ambient = Owner<AmbientLight>::Create(Ambient);
		//	Entity::Ambient->intensity = Vec3f(0, 0, 0);
		//}

		//// Check if directional light exist in a scene, if not create one
		//if (!Entity::Directional)
		//{
		//	Entity::Directional = Owner<DirectionalLight>::Create(Directional);
		//	Entity::Directional->intensity = Vec3f(0, 0, 0);
		//	Entity::Directional->direction = Vec3f(0,-1, 0);
		//}

		//// Check if point light exist in a scene, if not create one
		//if (Entity::PointLightList.Size() == 0)
		//{
		//	Owner<PointLight> light_handler = Owner<PointLight>::Create(light_handler);
		//	PointLightList.PushBack(light_handler);
		//}


		for (auto it = LightComponentList.Begin(); it != LightComponentList.End(); ++it)
		{
			(*it)->Boot();
		}

		for (auto it = CameraComponentList.Begin(); it != CameraComponentList.End(); ++it)
		{
			(*it)->Boot();
		}

		// Boot Object
		for (auto it = ObjectList.Begin(); it != ObjectList.End(); ++it)
		{
			(*it)->Boot();
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
			(*it)->Init();
		}

		// Init Mesh
		for (auto it = MeshComponentList.Begin(); it != MeshComponentList.End(); ++it)
		{
			(*it)->Init();
		}

		// Init Light
		for (auto it = LightComponentList.Begin(); it != LightComponentList.End(); ++it)
		{
			(*it)->Init();
		}
		
		// Init Effect
		for (auto it = EffectComponentList.Begin(); it != EffectComponentList.End(); ++it)
		{
			(*it)->Init();
		}

		// Init Cameras
		for (auto it = CameraComponentList.Begin(); it != CameraComponentList.End(); ++it)
		{
			(*it)->Init();
		}

		Animation.Init();
	}

	void Entity::Update(float i_dt)
	{		
		// Update Object
		for (auto it = ObjectList.Begin(); it != ObjectList.End(); ++it)
		{
			(*it)->Update(i_dt);
		}

		// Update Mesh
		for (auto it = MeshComponentList.Begin(); it != MeshComponentList.End(); ++it)
		{
			(*it)->Update(i_dt);
		}

		// Update Light
		for (auto it = MeshComponentList.Begin(); it != MeshComponentList.End(); ++it)
		{
			(*it)->Update(i_dt);
		}

		// Update Effect
		for (auto it = EffectComponentList.Begin(); it != EffectComponentList.End(); ++it)
		{
			(*it)->Update(i_dt);
		}

		// Update Cameras
		for (auto it = CameraComponentList.Begin(); it != CameraComponentList.End(); ++it)
		{
			(*it)->Update(i_dt);
		}

		Animation.Update(i_dt);
	}

	void Entity::CleanUp()
	{
		for (auto it = ObjectList.Begin(); it != ObjectList.End(); ++it)
		{
			(*it)->CleanUp();
		}

		Animation.CleanUp();
	}
}