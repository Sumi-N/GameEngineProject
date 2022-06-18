#pragma once

#include "Define.h"
#include "Component.h"

namespace Tempest
{
	class EffectComponent : public Component
	{
	public:
		EffectComponent() = default;
		~EffectComponent() = default;

		virtual void Boot() override;
		void RegisterShaderPath(const char**);
		void RegisterTexture(Resource::TextureType i_type, const char* i_path);
		void LoadTexture();

	public:
		String shaderpaths[5];

		Resource::Material material;

		std::array<String, 5>                   texture_paths;
		std::array<Resource::TextureType, 5>    texture_types;
		std::array<Owner<Resource::Texture>, 5> textures;
	};

	inline void EffectComponent::Boot()
	{
		LoadTexture();
	}

	inline void EffectComponent::RegisterShaderPath(const char** shaderpaths)
	{
		this->shaderpaths[0] = shaderpaths[0];
		this->shaderpaths[1] = shaderpaths[1];
		this->shaderpaths[2] = shaderpaths[2];
		this->shaderpaths[3] = shaderpaths[3];
		this->shaderpaths[4] = shaderpaths[4];
	}

	inline void EffectComponent::RegisterTexture(Resource::TextureType i_type, const char* i_path)
	{
		for (int i = 0; i < 5; i++)
		{
			if (texture_paths[i].empty())
			{
				texture_paths[i] = i_path;
				texture_types[i] = i_type;
				return;
			}
		}

		DEBUG_ASSERT(false);
	}

	inline void EffectComponent::LoadTexture()
	{
		for (int i = 0; i < 5; i++)
		{
			if (texture_paths[i].empty())
			{
				continue;
			}

			textures[i] = Create<Resource::Texture>();

			Result result = Resource::Texture::Load(texture_paths[i].c_str(), *textures[i]);

			if (result)
			{
				DEBUG_PRINT("Succeed loading texture %s", texture_paths[i]);
			}
			else
			{
				DEBUG_PRINT("Failed loading texture %s", texture_paths[i]);
			}
		}
	}
}