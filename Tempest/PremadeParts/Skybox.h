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

		name = "Sky Box";

		{
			mesh_component = Create<MeshComponent>();
			mesh_component->Load(PATH_SUFFIX BIN_MESH_PATH FILENAME_CUBEMAP);
			mesh_component->owner = Entity::Query(this);
			Entity::RegisterMeshComponent(mesh_component);
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

			effect_component = Create<EffectComponent>();
			effect_component->RegisterShaderPath(shaderpaths);
			effect_component->RegisterTexture(TextureType::SkyBox, PATH_SUFFIX BIN_TEXTURE_PATH SKYBOX_HDR_PINTREE);
			effect_component->owner = Entity::Query(this);
			Entity::RegisterEffectComponent(effect_component);
		}

		{
			background_component = Create<BackgroundComponent>();
			background_component->mesh_component = mesh_component;
			background_component->effect_component = effect_component;
			Entity::RegisterBackgroundComponent(background_component);
		}
	}
}