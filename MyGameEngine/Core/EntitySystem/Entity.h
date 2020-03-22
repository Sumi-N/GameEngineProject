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
	static std::vector<ObjectHandler> ObjectList;
	static std::vector<OwningPointer<MeshComponent>> MeshComponentList;
	static std::vector<OwningPointer<PointLight>> PointLightList;
	static OwningPointer<DirectionalLight> Directional;
	static OwningPointer<AmbientLight> Ambient;;
	static OwningPointer<Camera> CurrentCamera;

	static ObjectHandler Register(Object *);
	static void RegisterCamera(Camera *);
	static void RegisterAmbientLight(AmbientLight*);
	static void RegisterPointLight(PointLight*);
	static void RegisterDirectionalLight(DirectionalLight*);
	static void RegisterMeshComponent(MeshComponent*);
	static void Init();
	static void Update(float i_dt);
	static void CleanUp();
};