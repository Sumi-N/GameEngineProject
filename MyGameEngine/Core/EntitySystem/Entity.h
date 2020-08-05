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
	// Cameras, the current camera is always the 0 index
	static std::vector<OwningPointer<Camera>> Cameras;
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
	static void Register(const OwningPointer<Object>&);
	static ObjectHandler Query(Object*);

	static void RegisterCamera(const OwningPointer<Camera>&);

	static void RegisterSkyBox(const OwningPointer<CubeMap>&);

	static void RegisterAmbientLight(const OwningPointer<AmbientLight>&);

	static void RegisterDirectionalLight(const OwningPointer<DirectionalLight>&);

	static void RegisterPointLight(const OwningPointer<PointLight>&);

	static void RegisterMeshComponent(const OwningPointer<MeshComponent>&);

	static void RegisterEffectComponent(const OwningPointer<EffectComponent>&);

	static void Boot();
	static void Init();
	static void Update(float i_dt);
	static void CleanUp();
	static void SwapCamera(size_t, size_t);
};