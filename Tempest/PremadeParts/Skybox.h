#pragma once
#include "Define.h"

namespace Tempest
{

	class  SkyBox : public CubeMap
	{
	public:
		void Boot() override;
	};

	inline void SkyBox::Boot()
	{
		CubeMap::Boot();

		OwningPointer<MeshComponent>::Create(mesh);
		mesh->Load(PATH_SUFFIX MESH_PATH FILENAME_CUBEMAP);


		OwningPointer<TextureAttribute> texture = OwningPointer<TextureAttribute>::Create(texture);
		texture->Load(PATH_SUFFIX TEXTURE_PATH SKYBOX_HDR_FROZEN_WATERFALL, TextureType::SkyBox);

		const char* shaderpaths[] =
		{
			PATH_SUFFIX SHADER_PATH SKYBOX_VERT,
			nullptr,
			nullptr,
			nullptr,
			PATH_SUFFIX SHADER_PATH SKYBOX_FRAG,
		};

		OwningPointer<EffectComponent>::Create(effect);
		effect->owner = Entity::Skybox;
		effect->RegisterShaderPath(shaderpaths);
		effect->SetTexture(texture);
	}

}