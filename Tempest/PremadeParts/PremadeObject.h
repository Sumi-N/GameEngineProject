#pragma once

#include "Define.h"

namespace Tempest
{

	class PremadeObjebct : public Object
	{
	public:
		PremadeObjebct() : mesh(nullptr)
		{
		}

		void Boot() override;
		void Init() override;

	protected:
		OwningPointer<MeshComponent> mesh;
	};

	inline void PremadeObjebct::Boot()
	{
		Object::Boot();

		mesh = OwningPointer<MeshComponent>::Create(mesh);
		OwningPointer<MaterialAttribute> material;
		material = OwningPointer<MaterialAttribute>::Create(material);
		mesh->SetMaterial(material);
		mesh->owner = Entity::Query(this).p;
		Entity::RegisterMeshComponent(mesh);


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

}