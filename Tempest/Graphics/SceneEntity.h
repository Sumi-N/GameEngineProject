#pragma once

#include "Define.h"
#include "SceneProxy.h"
#include "RenderState.h"

using namespace Tempest;

class SceneEntity
{
public:
	static Array<Owner<SceneProxy>> List;
	static Owner<SceneProxy> SkyBoxProxy;
	static void Init();
};

inline void SceneEntity::Init()
{
	// Init sky-box cube map
	{		
		SceneEntity::SkyBoxProxy = Create<SceneProxy>();
		Owner<RenderState> renderhandler = Create<RenderState>();
		SkyBoxProxy->state = renderhandler;
		
		SkyBoxProxy->meshes.PushBack(Entity::BackgroundComponentList[0]->mesh);
		SkyBoxProxy->Init(static_cast<int>(Entity::BackgroundComponentList[0]->mesh_type));
		
		renderhandler->InitShader(Entity::BackgroundComponentList[0]->shader_paths);
		renderhandler->InitTexture(
			Entity::BackgroundComponentList[0]->texture_type,
			Entity::BackgroundComponentList[0]->texture);
	}

	for (auto it = Entity::EffectComponentList.Begin(); it != Entity::EffectComponentList.End(); ++it)
	{		
		Owner<SceneProxy> proxyhandler = Create<SceneProxy>();						
		Owner<RenderState> renderhandler = Create<RenderState>();
		proxyhandler->state = renderhandler;
		List.PushBack(proxyhandler);

		renderhandler->InitShader((*it)->shaderpaths);		
		// Create buffer for textures
		auto it_type = (*it)->texture_types.begin();
		for (auto it_tex = (*it)->textures.begin(); it_tex != (*it)->textures.end(); ++it_tex, ++ it_type)
		{
			if(*it_tex)
				renderhandler->InitTexture(*it_type, *it_tex);
		}

		for (auto it2 = Entity::MeshComponentList.Begin(); it2 != Entity::MeshComponentList.End(); ++it2)
		{
			if ((*it)->owner == (*it2)->owner)
			{
				if ((*it2)->mesh_type == Resource::MeshType::Mesh)
				{					
					proxyhandler->meshes.PushBack((*it2)->mesh);
				}
				else
				{
					auto mesh = static_cast<Observer<Resource::Mesh>>((*it2)->mesh);
					proxyhandler->meshes.PushBack(mesh);
				}
				proxyhandler->Init(static_cast<int>((*it2)->mesh_type));
			}
		}		
	}
}