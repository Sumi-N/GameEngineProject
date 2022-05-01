#pragma once

#include "Define.h"
#include "CameraObject.h"
#include "Light.h"
#include "MeshComponent.h"
#include "EffectComponent.h"

namespace Tempest
{
	template<typename T>
	class Entity : Array<T>
	{
	public:

		void Init();
		void Update(double i_dt);

		template<typename U>
		void InitEntity(Entity<U> i_entity);
	};

	template<typename T>
	void Entity<T>::Init()
	{		
	}

	template<typename T>
	void Entity<T>::Update(double i_dt)
	{
		for (auto datum : data)
		{
			datum.Update(i_dt);
		}
		return;
	}

	template<typename T>
	template<typename U>
	void Entity<T>::InitEntity(Entity<U> i_entity)
	{
		return;
	}

	class EntitySystem
	{
	public:
		Entity<CameraObject> camera_list;
		Entity<MeshComponent> mesh_component_list;
		Entity<EffectComponent> effect_component_list;
	};


	template<typename T>
	class SceneEntity
	{
	public:
		Entity<T> proxy_list;
	};
}