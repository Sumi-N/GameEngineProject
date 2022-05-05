#pragma once

#include "Define.h"
#include "Object.h"
#include "LightComponent.h"
#include "MeshComponent.h"
#include "EffectComponent.h"
#include "CameraComponent.h"
#include "BackgroundComponent.h"

namespace Tempest
{
	template<typename T>
	class Entry : public Array<T>
	{
	public:
		void Register(const T& i_data)
		{
			PushBack(i_data);
		}

		void Boot()
		{
			for (auto it = this->Begin(); it != this->End(); ++it)
			{
				(*it)->Boot();
			}
		}

		void Init()
		{			
			for (auto it = this->Begin(); it != this->End(); ++it)
			{
				(*it)->Init();
			}
		}

		void Update(float i_dt)
		{			
			for (auto it = this->Begin(); it != this->End(); ++it)
			{
				(*it)->Update(i_dt);
			}
		}

		void CleanUp()
		{		
			for (auto it = this->Begin(); it != this->End(); ++it)
			{
				(*it)->CleanUp();
			}
		}
	};

	class Entity
	{

	public:
		static Entry<Owner<Object>>              ObjectList;
		static Entry<Owner<CameraComponent>>     CameraComponentList;
		static Entry<Owner<LightComponent>>      LightComponentList;
		static Entry<Owner<MeshComponent>>       MeshComponentList;
		static Entry<Owner<EffectComponent>>     EffectComponentList;
		static Entry<Owner<BackgroundComponent>> BackgroundComponentList;
		static AnimationSystem                   Animation;
			
		static void Register (const Owner<Object>&);
		static void RegisterCameraComponent (const Owner<CameraComponent>&);
		static void RegisterMeshComponent (const Owner<MeshComponent>&);
		static void RegisterEffectComponent (const Owner<EffectComponent>&);
		static void RegisterLightComponent (const Owner<LightComponent>&);
		static void RegisterBackgroundComponent (const Owner<BackgroundComponent>&);
		static void RegisterAnimationComponent (const Owner<AnimationComponent>&);

		static Owner<Object> Query(Object*);
		static void Boot();
		static void Init();
		static void Update(float i_dt);
		static void CleanUp();
	};

}