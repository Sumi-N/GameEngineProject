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
		CubeMap() : mesh(nullptr), effect(nullptr)
		{
		}
		virtual ~CubeMap()
		{
		}
		virtual void Boot() override;
		OwningPointer<MeshComponent> mesh;
		OwningPointer<EffectComponent> effect;
	};

	inline void CubeMap::Boot()
	{
		Object::Boot();
	}

}
