#pragma once

#include "Define.h"

	class ObjectHandler
	{
	public:
		ObjectHandler(Object* i_objpointer)
		{
			p = i_objpointer;
		}
		OwningPointer<Object> p;
	private:
	};

class Entity
{
public:
	// Object list
	static std::vector<ObjectHandler> ObjectList;
	// Component list
	static std::vector<OwningPointer<MeshComponent>> MeshComponentList;
	static std::vector<OwningPointer<EffectComponent>> EffectComponentList;
	// Light lists
	static std::vector<OwningPointer<PointLight>> PointLightList;
	static OwningPointer<DirectionalLight> Directional;
	static OwningPointer<AmbientLight> Ambient;;
	// Camera
	static OwningPointer<Camera> CurrentCamera;

	static ObjectHandler Register(Object *);
	static ObjectHandler Query(Object*);

	static void RegisterCamera(Camera *);
	static void RegisterAmbientLight(AmbientLight*);
	static void RegisterDirectionalLight(DirectionalLight*);
	static void RegisterPointLight(PointLight*);
	static void RegisterMeshComponent(MeshComponent*);
	static void RegisterEffectComponent(EffectComponent*);

	static void Boot();
	static void Init();
	static void Update(float i_dt);
	static void CleanUp();
};