#pragma once
#include "Define.h"

namespace Tempest
{
	class  SkyBox : public Object
	{
	public:
		void Boot() override;
		
		Owner<MeshComponent> mesh_component;
		Owner<EffectComponent> effect_component;
		Owner<BackgroundComponent> background_component;
	};

	inline void SkyBox::Boot()
	{
		Object::Boot();

		{
			mesh_component = Create<MeshComponent>();
			mesh_component->Load(PATH_SUFFIX BIN_MESH_PATH FILENAME_CUBEMAP);
			mesh_component->owner = Entity::Query(this);
		}		

		{
			const char* shaderpaths[] =
			{
				PATH_SUFFIX SHADER_PATH SKYBOX_VERT,
				nullptr,
				nullptr,
				nullptr,
				PATH_SUFFIX SHADER_PATH SKYBOX_FRAG,
			};

			Owner<TextureAttribute> texture = Create<TextureAttribute>();
			texture->Load(PATH_SUFFIX BIN_TEXTURE_PATH SKYBOX_HDR_PINTREE, TextureType::SkyBox);

			effect_component = Create<EffectComponent>();
			effect_component->RegisterShaderPath(shaderpaths);
			effect_component->SetTexture(texture);
			effect_component->owner = Entity::Query(this);
		}

		{
			background_component = Create<BackgroundComponent>();
			background_component->mesh_component = mesh_component;
			background_component->effect_component = effect_component;
			Entity::RegisterBackgroundComponent(background_component);
		}
	}
}