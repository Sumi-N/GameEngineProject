#pragma once

#include "Define.h"

	class ObjectHandler
	{
	public:
		ObjectHandler(Object* i_objpointer) : p(i_objpointer) {}
		ObjectHandler(OwningPointer<Object> i_obj) : p(i_obj) {}
		OwningPointer<Object> p;
	private:
	};

class Entity
{
public:
	// Object list
	static std::vector<ObjectHandler> ObjectList;
	// Camera
	static OwningPointer<Camera> CurrentCamera;
	// Sky box
	static OwningPointer<CubeMap> Skybox;
	// Lights 
	static OwningPointer<AmbientLight> Ambient;
	static std::vector<OwningPointer<PointLight>> PointLightList;
	static OwningPointer<DirectionalLight> Directional;
	// Component list
	static std::vector<OwningPointer<MeshComponent>> MeshComponentList;
	static std::vector<OwningPointer<EffectComponent>> EffectComponentList;


	static void Register(Object *);
	static void Register(OwningPointer<Object>);
	static ObjectHandler Query(Object*);

	static void RegisterCamera(Camera *);
	static void RegisterCamera(OwningPointer<Camera>);

	static void RegisterSkyBox(CubeMap*);
	static void RegisterSkyBox(OwningPointer<CubeMap>);

	static void RegisterAmbientLight(AmbientLight*);
	static void RegisterAmbientLight(OwningPointer<AmbientLight>);

	static void RegisterDirectionalLight(DirectionalLight*);
	static void RegisterDirectionalLight(OwningPointer<DirectionalLight>);

	static void RegisterPointLight(PointLight*);
	static void RegisterPointLight(OwningPointer<PointLight>);

	static void RegisterMeshComponent(MeshComponent*);
	static void RegisterMeshComponent(OwningPointer<MeshComponent>);

	static void RegisterEffectComponent(EffectComponent*);
	static void RegisterEffectComponent(OwningPointer<EffectComponent>);

	static void Boot();
	static void Init();
	static void Update(float i_dt);
	static void CleanUp();
};