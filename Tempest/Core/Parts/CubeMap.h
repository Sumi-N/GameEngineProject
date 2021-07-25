#pragma once

#include "Define.h"
#include "Object.h"
#include "MeshComponent.h"
#include "EffectComponent.h"

namespace Tempest
{

	class CubeMap : public Object
	{
	public:
		CubeMap() : mesh_component(nullptr), effect(nullptr)
		{
		}
		virtual ~CubeMap()
		{
		}
		virtual void Boot() override;
		OwningPointer<MeshComponent> mesh_component;
		OwningPointer<EffectComponent> effect;
	};

	inline void CubeMap::Boot()
	{
		Object::Boot();
	}

}
