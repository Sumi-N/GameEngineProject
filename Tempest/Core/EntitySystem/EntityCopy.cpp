#include "Define.h"
#include "EntityCopy.h"

namespace Tempest 
{
	Array<ObjectHandler>               EntityCopy::ObjectListCopy{};
	Array<Owner<CameraObject>>         EntityCopy::CamerasObjectsCopy{};
	Array<Owner<PointLight>>           EntityCopy::PointLightListCopy{};
	Array<Owner<MeshComponent>>        EntityCopy::MeshComponentListCopy{};
	Array<Owner<EffectComponent>>      EntityCopy::EffectComponentListCopy{};

	Owner<CubeMap>                     EntityCopy::SkyboxCopy{};
	Owner<AmbientLight>                EntityCopy::AmbientLightCopy{};
	Owner<DirectionalLight>            EntityCopy::DirectionalLightCopy{};

	void EntityCopy::Init() 
	{		
		EntityCopy::CamerasObjectsCopy = Entity::CamerasObjects;		
		
		for (auto it = Entity::ObjectList.Begin(); it != Entity::ObjectList.End(); ++it)
		{			
			Owner<Object> copy_object_pointer = Create<Object>();
			ObjectHandler handler(copy_object_pointer);
			Object& original_object = *(*it).p;
			*copy_object_pointer = original_object;
			EntityCopy::ObjectListCopy.PushBack(handler);
		}
	
		//for (auto it = Entity::CamerasObjects.Begin(); it != Entity::CamerasObjects.End(); ++it)
		//{
		//	Owner<CameraObject> copy_object_pointer = Create<CameraObject>();			
		//	CameraObject& original_object = *(*it);
		//	*copy_object_pointer = original_object;
		//	EntityCopy::CamerasObjectsCopy.PushBack(copy_object_pointer);
		//}

		for (auto it = Entity::PointLightList.Begin(); it != Entity::PointLightList.End(); ++it)
		{
			Owner<PointLight> copy_object_pointer = Create<PointLight>();
			PointLight& original_object = *(*it);
			*copy_object_pointer = original_object;
			EntityCopy::PointLightListCopy.PushBack(copy_object_pointer);
		}

		for (auto it = Entity::MeshComponentList.Begin(); it != Entity::MeshComponentList.End(); ++it)
		{
			Owner<MeshComponent> copy_object_pointer = Create<MeshComponent>();
			MeshComponent& original_object = *(*it);
			*copy_object_pointer = original_object;
			EntityCopy::MeshComponentListCopy.PushBack(copy_object_pointer);
		}

		for (auto it = Entity::EffectComponentList.Begin(); it != Entity::EffectComponentList.End(); ++it)
		{
			Owner<EffectComponent> copy_object_pointer = Create<EffectComponent>();
			EffectComponent& original_object = *(*it);
			*copy_object_pointer = original_object;
			EntityCopy::EffectComponentListCopy.PushBack(copy_object_pointer);
		}


		EntityCopy::SkyboxCopy = Create<CubeMap>(*Entity::Skybox);
		EntityCopy::AmbientLightCopy = Create<AmbientLight>(*Entity::Ambient);
		EntityCopy::DirectionalLightCopy = Create<DirectionalLight>(*Entity::Directional);
	}
}