#pragma once

#include "Define.h"

namespace Tempest
{

	class ObjectHandler
	{
	public:
		ObjectHandler() = default;
		ObjectHandler(Object* i_objpointer)		   : p(i_objpointer) {}
		ObjectHandler(OwningPointer<Object> i_obj) : p(i_obj)        {}

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

		static OwningPointer<CubeMap>          Skybox;
		static OwningPointer<AmbientLight>     Ambient;
		static OwningPointer<DirectionalLight> Directional;


		
		static ObjectHandler Query(Object*);

		static void Register                  (const OwningPointer<Object>&);
		static void RegisterCamera            (const OwningPointer<CameraObject>&);
		static void RegisterSkyBox            (const OwningPointer<CubeMap>&);
		static void RegisterAmbientLight      (const OwningPointer<AmbientLight>&);
		static void RegisterDirectionalLight  (const OwningPointer<DirectionalLight>&);
		static void RegisterPointLight        (const OwningPointer<PointLight>&);
		static void RegisterMeshComponent     (const OwningPointer<MeshComponent>&);
		static void RegisterEffectComponent   (const OwningPointer<EffectComponent>&);		

		static void Boot();
		static void Init();
		static void Update(float i_dt);
		static void CleanUp();
		static void SwapCamera(size_t, size_t);
	};

}