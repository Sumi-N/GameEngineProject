#pragma  once
#include "Entity.h"

namespace Tempest
{
	Entry<Owner<Object>>               Entity::ObjectList{};
	Entry<Owner<CameraComponent>>      Entity::CameraComponentList{};
	Entry<Owner<LightComponent>>       Entity::LightComponentList{};
	Entry<Owner<MeshComponent>>        Entity::MeshComponentList{};
	Entry<Owner<EffectComponent>>      Entity::EffectComponentList{};
	Entry<Owner<BackgroundComponent>>  Entity::BackgroundComponentList{};
	AnimationSystem                    Entity::Animation{};

	void Entity::Register(const Owner<Object>& i_obj)
	{
		ObjectList.PushBack(i_obj);
	}

	void Entity::RegisterCameraComponent(const Owner<CameraComponent>& i_camera)
	{
		CameraComponentList.PushBack(i_camera);
	}

	void Entity::RegisterMeshComponent(const Owner<MeshComponent>& i_component)
	{
		MeshComponentList.PushBack(i_component);
	}

	void Entity::RegisterEffectComponent(const Owner<EffectComponent>& i_component)
	{
		EffectComponentList.PushBack(i_component);
	}

	void Entity::RegisterLightComponent(const Owner<LightComponent>& i_point)
	{
		LightComponentList.PushBack(i_point);
	}

	void Entity::RegisterBackgroundComponent(const Owner<BackgroundComponent>& i_component)
	{
		BackgroundComponentList.PushBack(i_component);
	}

	void Entity::RegisterAnimationComponent(const Owner<AnimationComponent>& i_component)
	{
		Entity::Animation.Register(i_component);
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

	void Entity::Boot()
	{
		ObjectList.Boot();
		CameraComponentList.Boot();
		LightComponentList.Boot();
		MeshComponentList.Boot();
		EffectComponentList.Boot();
		BackgroundComponentList.Boot();

		Animation.Boot();
	}

	void Entity::Init()
	{
		ObjectList.Init();
		CameraComponentList.Init();
		LightComponentList.Init();
		MeshComponentList.Init();
		EffectComponentList.Init();
		BackgroundComponentList.Init();

		Animation.Init();
	}

	void Entity::Update(float i_dt)
	{
		ObjectList.Update(i_dt);
		CameraComponentList.Update(i_dt);
		LightComponentList.Update(i_dt);
		MeshComponentList.Update(i_dt);
		EffectComponentList.Update(i_dt);
		BackgroundComponentList.Update(i_dt);

		Animation.Update(i_dt);
	}

	void Entity::CleanUp()
	{
		ObjectList.CleanUp();
		CameraComponentList.CleanUp();
		LightComponentList.CleanUp();
		MeshComponentList.CleanUp();
		EffectComponentList.CleanUp();
		BackgroundComponentList.CleanUp();

		Animation.CleanUp();
	}

	void Entity::Reset()
	{
		ObjectList.Clear();
		CameraComponentList.Clear();
		LightComponentList.Clear();
		MeshComponentList.Clear();
		EffectComponentList.Clear();
		BackgroundComponentList.Clear();

		Animation.Clear();
	}
}