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
	class Entity
	{		

	public:		
		static Array<Owner<Object>>             ObjectList;
		static Array<Owner<CameraComponent>>    CameraComponentList;
		static Array<Owner<LightComponent>>     LightComponentList;
		static Array<Owner<MeshComponent>>      MeshComponentList;
		static Array<Owner<EffectComponent>>    EffectComponentList;			
		static Array<Owner<BackgroundComponent>>BackgroundComponentList;

		static AnimationSystem                  Animation;
		
		static Owner<Object> Query(Object*);

		static void Register                  (const Owner<Object>&);
		static void RegisterCameraComponent   (const Owner<CameraComponent>&);
		static void RegisterMeshComponent     (const Owner<MeshComponent>&);
		static void RegisterEffectComponent   (const Owner<EffectComponent>&);		
		static void RegisterLightComponent    (const Owner<LightComponent>&);
		static void RegisterBackgroundComponent(const Owner<BackgroundComponent>&);
		static void RegisterAnimationComponent(const Owner<AnimationComponent>&);

		static void Boot();
		static void Init();
		static void Update(float i_dt);
		static void CleanUp();		
	};

}