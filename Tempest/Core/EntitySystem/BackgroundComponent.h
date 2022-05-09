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
		void RegisterTexture(const Resource::TextureType&, const char*);
		void LoadMesh();
		void LoadTexture();		

		const char* mesh_path;		
		Owner<Resource::Mesh> mesh;
		Resource::MeshType mesh_type;

		const char* shader_paths[5];
		const char* texture_path;
		Resource::TextureType    texture_type;
		Owner<Resource::Texture> texture;
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
		this->shader_paths[0] = i_shader_paths[0];
		this->shader_paths[1] = i_shader_paths[1];
		this->shader_paths[2] = i_shader_paths[2];
		this->shader_paths[3] = i_shader_paths[3];
		this->shader_paths[4] = i_shader_paths[4];
	}

	inline void BackgroundComponent::RegisterTexture(const Resource::TextureType& i_type, const char* i_path)
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
			mesh = Create<Resource::Mesh>();
			auto result = Resource::Mesh::Load(mesh_path, *mesh);
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
		texture = Create<Resource::Texture>();

		Result result = Resource::Texture::Load(texture_path, *texture);

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