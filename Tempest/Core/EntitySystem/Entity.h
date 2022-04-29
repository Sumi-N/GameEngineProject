#pragma once

#include "Define.h"

namespace Tempest
{

	class ObjectHandler
	{

		friend class Entity;
		friend class EntityCopy;

	public:
		ObjectHandler() = default;
		ObjectHandler(Object* i_objpointer)		          : p(i_objpointer), name("Empty") {}
		ObjectHandler(Owner<Object> i_obj)                : p(i_obj),        name("Empty") {}
		ObjectHandler(Owner<Object> i_obj, String i_name) : p(i_obj),        name(i_name)  {}

		Owner<Object> Get() { return p; };
		String name;
	private:
		Owner<Object> p;		
	};

	class Entity
	{		

	public:		
		static Array<ObjectHandler>             ObjectList;
		static Array<Owner<CameraObject>>       CamerasObjects;
		static Array<Owner<PointLight>>         PointLightList;
		static Array<Owner<MeshComponent>>      MeshComponentList;
		static Array<Owner<EffectComponent>>    EffectComponentList;		

		static Owner<CubeMap>                   Skybox;
		static Owner<AmbientLight>              Ambient;
		static Owner<DirectionalLight>          Directional;

		static AnimationSystem                          Animation;
		
		static Owner<Object> Query(Object*);

		static void Register                  (const Owner<Object>&);
		static void Register                  (const Owner<Object>&, String);
		static void RegisterCamera            (const Owner<CameraObject>&);
		static void RegisterSkyBox            (const Owner<CubeMap>&);
		static void RegisterAmbientLight      (const Owner<AmbientLight>&);
		static void RegisterDirectionalLight  (const Owner<DirectionalLight>&);
		static void RegisterPointLight        (const Owner<PointLight>&);
		static void RegisterMeshComponent     (const Owner<MeshComponent>&);
		static void RegisterEffectComponent   (const Owner<EffectComponent>&);		
		static void RegisterAnimationComponent(const Owner<AnimationComponent>&);

		static void Boot();
		static void Init();
		static void Update(float i_dt);
		static void CleanUp();
		static void SwapCamera(size_t, size_t);
	};

}