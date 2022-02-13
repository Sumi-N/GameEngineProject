#include "EntityInfo.h"

namespace Tempest {
	namespace EntityInfo {
		size_t GetTotalObjectSize()
		{
			return Entity::ObjectList.Size();
		}

		String GetObjectNameByIndex(int index)
		{
			return Entity::ObjectList[index].name;
		}

		Vec3f GetObjectPositionByIndex(int index)
		{
			return Entity::ObjectList[index].Get()->pos;
		}

		Vec3f GetObjectRotationByIndex(int index)
		{
			return Entity::ObjectList[index].Get()->rot;
		}

		Vec3f GetObjectScaleByIndex(int index)
		{
			return Entity::ObjectList[index].Get()->scale;
		}

		ComponentFlags GetAttachedComponentsByIndex(int index)
		{
			ComponentFlags result = ComponentFlags::None;

			ObjectHandler handler = Entity::ObjectList[index];
			ObservingPointer<Object> object = handler.Get();

			for (int i = 0; i < Entity::EffectComponentList.Size(); i++)
			{
				if (object == Entity::EffectComponentList[i]->owner) {
					result = static_cast<ComponentFlags>(result | ComponentFlags::Effect);
				}
			}

			for (int i = 0; i < Entity::MeshComponentList.Size(); i++)
			{
				if (object == Entity::MeshComponentList[i]->owner) {
					result = static_cast<ComponentFlags>(result | ComponentFlags::Mesh);
				}
			}

			return result;
		}
	}
}
