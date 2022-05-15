#pragma once

#include "Define.h"
#include "PremadeObject.h"
#include <ResourceManagement/FBXImporter.h>
#include <PremadeParts/Define.h>

namespace Tempest
{

	class Cube : public PremadeObjebct
	{
	public:
		void Boot() override;
		void Init() override;
	};

	inline void Cube::Boot()
	{
		PremadeObjebct::Boot();

		mesh_component->Load(PATH_SUFFIX BIN_MESH_PATH FILENAME_CUBEMAP);

		const char* shaderpaths[] =
		{
			PATH_SUFFIX SHADER_PATH DEBUG_PBR_BASIC_VERT,
			nullptr,
			nullptr,
			nullptr,
			PATH_SUFFIX SHADER_PATH DEBUG_PBR_BASIC_FRAG,
		};

		OwningPointer<EffectComponent> effect = OwningPointer<EffectComponent>::Create(effect);
		effect->owner = Entity::Query(this);

		//effect->SetTexture(diffuse);
		//effect->SetTexture(speclar);

		effect->RegisterShaderPath(shaderpaths);
		Entity::RegisterEffectComponent(effect);

		this->Translate(Vec3f(0, -10, -40));
		this->scale = Vec3f(0.1f, 0.1f, 0.1f);
		//this->rot.x = -90;

		//SHOW_DEBUG_POLYGON
		//SHOW_DEBUG_NORMAL_VECTOR
	}

	inline void Cube::Init()
	{
		PremadeObjebct::Init();
	}

}