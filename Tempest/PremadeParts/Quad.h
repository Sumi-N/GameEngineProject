#pragma once

#include "Define.h"
#include "PremadeObject.h"

namespace Tempest
{

	class Quad : public PremadeObjebct
	{
	public:
		void Boot() override;
		void Init() override;
	};

	inline void Quad::Boot()
	{
		PremadeObjebct::Boot();

		mesh->Load(PATH_SUFFIX MESH_PATH FILENAME_QUAD);

		const char* shaderpaths[] =
		{
			PATH_SUFFIX SHADER_PATH DEBUG_BP_BASIC_VERT,
			nullptr,
			nullptr,
			nullptr,
			PATH_SUFFIX SHADER_PATH DEBUG_BP_BASIC_FRAG,
		};

		//EffectComponent* effect = new EffectComponent();
		//effect->owner = Entity::Query(this).p;
		//effect->RegisterShaderPath(shaderpaths);
		//Entity::RegisterEffectComponent(effect);
	}

	inline void Quad::Init()
	{
		PremadeObjebct::Init();
	}

}
