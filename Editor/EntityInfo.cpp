#include "EntityInfo.h"

namespace Tempest {

	extern int SelectedIndex;
	extern EntityInfo::ComponentFlags SelectedFlag;
	extern Object SelectedObject;
	extern CameraComponent SelectedCamera;
	extern LightComponent SelectedLight;
	extern MeshComponent SelectedMesh;
	extern EffectComponent SelecctedEffect;

	namespace EntityInfo {
		
		size_t GetTotalObjectSize()
		{
			return Entity::ObjectList.Size();
		}

		Object GetObjectByIndex(int index)
		{
			return *Entity::ObjectList[index];
		}

		String GetObjectNameByIndex(int index)
		{
			return Entity::ObjectList[index]->name;
		}

		ComponentFlags GetAttachedComponentsByIndex(int index)
		{
			ComponentFlags result = ComponentFlags::None;
			
			ObservingPointer<Object> object = Entity::ObjectList[index];

			for (int i = 0; i < Entity::CameraComponentList.Size(); i++)
			{
				if (object == Entity::CameraComponentList[i]->owner)
				{
					result = static_cast<ComponentFlags>(result | ComponentFlags::CameraFlag);
					SelectedCamera = *Entity::CameraComponentList[i];
				}
			}

			for (int i = 0; i < Entity::LightComponentList.Size(); i++)
			{
				if (object == Entity::LightComponentList[i]->owner)
				{
					result = static_cast<ComponentFlags>(result | ComponentFlags::LightFlag);
					SelectedLight = *Entity::LightComponentList[i];
				}
			}

			for (int i = 0; i < Entity::EffectComponentList.Size(); i++)
			{
				if (object == Entity::EffectComponentList[i]->owner) {
					result = static_cast<ComponentFlags>(result | ComponentFlags::EffectFlag);
					SelecctedEffect = *Entity::EffectComponentList[i];
				}
			}

			for (int i = 0; i < Entity::MeshComponentList.Size(); i++)
			{
				if (object == Entity::MeshComponentList[i]->owner) {
					result = static_cast<ComponentFlags>(result | ComponentFlags::MeshFlag);
					SelectedMesh = *Entity::MeshComponentList[i];
				}
			}

			return result;
		}
	}
}
