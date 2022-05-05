//#pragma once
//
//#include "Define.h"
//#include "MeshComponent.h"
//#include "EffectComponent.h"
//#include "LightComponent.h"
//#include "CameraComponent.h"
//
//namespace Tempest
//{
//	template<typename T>
//	class Entity : Array<T>
//	{
//	public:
//		void Register(const T& i_data)
//		{			
//			PushBack(i_data);
//		}
//
//		void Boot()
//		{
//		}
//
//		void Init()
//		{
//		}
//
//		void Update(double i_dt)
//		{
//		}
//
//		void CleanUp()
//		{
//		}
//	};	
//	
//	class EntityComponent
//	{
//	public:
//		Entity<Object> object_list;
//		Entity<MeshComponent> mesh_component_list;
//		Entity<EffectComponent> effect_component_list;		
//		Entity<LightComponent> light_component_list;
//	};
//}