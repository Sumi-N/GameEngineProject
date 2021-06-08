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

		mesh->Load(PATH_SUFFIX BIN_MESH_PATH "SK_PlayerCharacter.tmd");

		//OwningPointer<TextureAttribute> diffuse = OwningPointer<TextureAttribute>::Create(diffuse);
		//OwningPointer<TextureAttribute> speclar = OwningPointer<TextureAttribute>::Create(speclar);

		//diffuse->Load(PATH_SUFFIX TEXTURE_PATH "NotFree/tex_fuku2_Anon.png", TextureType::PB_Diffuse);
		//speclar->Load(PATH_SUFFIX TEXTURE_PATH "NotFree/tex_fuku2_Anon.png", TextureType::PB_Specular);


		const char* shaderpaths[] =
		{
			PATH_SUFFIX SHADER_PATH DEBUG_PBR_BASIC_VERT,
			nullptr,
			nullptr,
			nullptr,
			PATH_SUFFIX SHADER_PATH DEBUG_PBR_BASIC_FRAG,
		};

		OwningPointer<EffectComponent> effect = OwningPointer<EffectComponent>::Create(effect);
		effect->owner = Entity::Query(this).p;

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

		mesh->material_attribute->material->metalic = 0.99f;
		mesh->material_attribute->material->roughness = 0.1f;
	}

}