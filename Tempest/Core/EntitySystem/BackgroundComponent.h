#pragma once

#include "Define.h"
#include "Component.h"
#include "MeshComponent.h"
#include "EffectComponent.h"

namespace Tempest
{
	class BackgroundComponent : public Component
	{
	public:
		BackgroundComponent() = default;

		Owner<MeshComponent> mesh_component;
		Owner<EffectComponent> effect_component;
	};
}