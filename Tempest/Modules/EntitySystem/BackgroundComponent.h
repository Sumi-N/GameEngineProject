#pragma once

#include "Define.h"
#include "Component.h"

namespace Tempest
{
	class BackgroundComponent : public Component
	{
	public:
		BackgroundComponent() = default;
		~BackgroundComponent() = default;

		virtual void Boot() override;
		virtual void CleanUp() override {};

		void RegisterMesh(const char*);
		void RegisterShaderPath(const char** i_shader_paths);
		void RegisterTexture(const TextureType&, const char*);
		void LoadMesh();
		void LoadTexture();

		String mesh_path;
		Owner<Mesh> mesh;
		MeshType mesh_type;

		String shader_paths[5];
		String texture_path;
		TextureType    texture_type;
		Owner<TextureInfo> texture;
	};

	inline void BackgroundComponent::Boot()
	{
		LoadMesh();
		LoadTexture();
	}

	inline void BackgroundComponent::RegisterMesh(const char* i_path)
	{
		mesh_path = i_path;
		return;
	}

	inline void BackgroundComponent::RegisterShaderPath(const char** i_shader_paths)
	{
		shader_paths[0] = i_shader_paths[0];
		shader_paths[4] = i_shader_paths[4];
	}

	inline void BackgroundComponent::RegisterTexture(const TextureType& i_type, const char* i_path)
	{
		texture_path = i_path;
		texture_type = i_type;
		return;
	}

	inline void BackgroundComponent::LoadMesh()
	{
		if (File::GetExtensionName(mesh_path) == ".tm")
		{
			mesh_type = MeshType::Mesh;
			mesh = Create<Mesh>();
			auto result = Mesh::Load(mesh_path.c_str(), *mesh);
		}
		else
		{
			DEBUG_ASSERT(false);
		}

		if (!mesh)
		{
			DEBUG_ASSERT(false);
		}

		DEBUG_PRINT("Succeed loading background mesh %s", mesh_path);

		return;
	}

	inline void BackgroundComponent::LoadTexture()
	{
		texture = Create<TextureInfo>();

		Result result = TextureInfo::Load(texture_path.c_str(), *texture);

		if (result)
		{
			DEBUG_PRINT("Succeed loading background texture %s", texture_path);
		}
		else
		{
			DEBUG_PRINT("Failed loading background texture %s", texture_path);
		}
	}
}