#pragma once

#include "Define.h"

namespace Tempest
{

	class PremadeObjebct : public Object
	{
	public:
		PremadeObjebct() : mesh_component(nullptr) {}

		virtual void Boot() override;
		virtual void Init() override;
		OwningPointer<MeshComponent> GetMeshComponent();

	protected:
		OwningPointer<MeshComponent> mesh_component;
	};

	inline void PremadeObjebct::Boot()
	{
		Object::Boot();

		mesh_component = OwningPointer<MeshComponent>::Create(mesh_component);
		OwningPointer<MaterialAttribute> material;
		material = OwningPointer<MaterialAttribute>::Create(material);
		mesh_component->SetMaterial(material);
		mesh_component->owner = Entity::Query(this).p;
		Entity::RegisterMeshComponent(mesh_component);


#if defined(_DEBUG) && !defined(NDEBUG)
		//SHOW_DEBUG_POLYGON
		//SHOW_DEBUG_NORMAL_COLOR
		//SHOW_DEBUG_NORMAL_VECTOR
		//SHOW_DEBUG_VIEWDIRECTION
		//SHOW_DEBUG_LIGHTDIRECTION
		//SHOW_DEBUG_BP_BASIC

#endif // DEBUG

	}

	inline void PremadeObjebct::Init()
	{
		Object::Init();
	}

	inline OwningPointer<MeshComponent> PremadeObjebct::GetMeshComponent()
	{
		if (mesh_component)
		{
			return mesh_component;
		}
		else
		{
			DEBUG_ASSERT(false);
			return OwningPointer<MeshComponent>();
		}
	}

}