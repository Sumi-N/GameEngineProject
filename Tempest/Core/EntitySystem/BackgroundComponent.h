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
		~BackgroundComponent() = default;

		virtual void CleanUp() override {};

		Owner<MeshComponent> mesh_component;
		Owner<EffectComponent> effect_component;
	};
}