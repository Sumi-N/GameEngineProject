#include "EntityInfo.h"

namespace Tempest {

	extern int SelectedObjectIndex;
	extern EntityInfo::ComponentFlags SelectingComponent;
	extern Object SelectedObject;
	extern CameraComponent SelectedCamera;
	extern LightComponent SelectedLight; 
	extern MeshComponent SelectedMesh;
	extern EffectComponent SelecctedEffect;
	extern Observer<EffectComponent> SelectingDebugEffect;

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

		ComponentFlags GetAttachedComponentsInfoByIndex(int index)
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
					if (Entity::EffectComponentList[i]->is_debug_function)
					{
						SelectingDebugEffect = Entity::EffectComponentList[i];
					}
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
