#pragma once
#include "Define.h"

namespace Tempest
{
	class  SkyBox : public Object
	{
	public:
		void Boot() override;
		
		Owner<BackgroundComponent> background_component;
	};

	inline void SkyBox::Boot()
	{
		Object::Boot();

		name = "Sky Box";

		{
			background_component = Create<BackgroundComponent>();
			background_component->owner = Entity::Query(this);
			Entity::RegisterBackgroundComponent(background_component);

			background_component->RegisterMesh(PATH_SUFFIX BIN_MESH_PATH FILENAME_CUBEMAP);

			const char* shaderpaths[] =
			{
				PATH_SUFFIX SHADER_PATH SKYBOX_VERT,
				nullptr,
				nullptr,
				nullptr,
				PATH_SUFFIX SHADER_PATH SKYBOX_FRAG,
			};

			background_component->RegisterShaderPath(shaderpaths);
			background_component->RegisterTexture(TextureType::SkyBox, PATH_SUFFIX BIN_TEXTURE_PATH SKYBOX_HDR_PINTREE);
		}
	}
}