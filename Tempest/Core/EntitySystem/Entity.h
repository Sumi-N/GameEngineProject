#pragma once

#include "Define.h"

namespace Tempest
{

	class ObjectHandler
	{

		friend class Entity;

	public:
		ObjectHandler() = default;
		ObjectHandler(Object* i_objpointer)		                  : p(i_objpointer), name("Empty") {}
		ObjectHandler(OwningPointer<Object> i_obj)                : p(i_obj),        name("Empty") {}
		ObjectHandler(OwningPointer<Object> i_obj, String i_name) : p(i_obj),        name(i_name)  {}

		String name;
	private:
		OwningPointer<Object> p;		
	};

	class Entity
	{		

	public:		
		static Array<ObjectHandler>                     ObjectList;
		static Array<OwningPointer<CameraObject>>       CamerasObjects;
		static Array<OwningPointer<PointLight>>         PointLightList;
		static Array<OwningPointer<MeshComponent>>      MeshComponentList;
		static Array<OwningPointer<EffectComponent>>    EffectComponentList;		

		static OwningPointer<CubeMap>                   Skybox;
		static OwningPointer<AmbientLight>              Ambient;
		static OwningPointer<DirectionalLight>          Directional;

		static AnimationSystem                          Animation;
		
		static OwningPointer<Object> Query(Object*);

		static void Register                  (const OwningPointer<Object>&);
		static void Register                  (const OwningPointer<Object>&, String);
		static void RegisterCamera            (const OwningPointer<CameraObject>&);
		static void RegisterSkyBox            (const OwningPointer<CubeMap>&);
		static void RegisterAmbientLight      (const OwningPointer<AmbientLight>&);
		static void RegisterDirectionalLight  (const OwningPointer<DirectionalLight>&);
		static void RegisterPointLight        (const OwningPointer<PointLight>&);
		static void RegisterMeshComponent     (const OwningPointer<MeshComponent>&);
		static void RegisterEffectComponent   (const OwningPointer<EffectComponent>&);		
		static void RegisterAnimationComponent(const OwningPointer<AnimationComponent>&);

		static void Boot();
		static void Init();
		static void Update(float i_dt);
		static void CleanUp();
		static void SwapCamera(size_t, size_t);
	};

}