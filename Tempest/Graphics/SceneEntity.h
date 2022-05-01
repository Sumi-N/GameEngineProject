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
	if (Entity::Skybox)
	{		
		SceneEntity::SkyBoxProxy = Create<SceneProxy>();
		Owner<RenderState> renderhandler = Create<RenderState>();
		SkyBoxProxy->state = renderhandler;
		
		SkyBoxProxy->meshes.PushBack(Entity::Skybox->mesh_component->mesh);
		SkyBoxProxy->Init(static_cast<int>(Entity::Skybox->mesh_component->type));
		
		renderhandler->InitShader(Entity::Skybox->effect_component->shaderpaths);
		renderhandler->InitTexture(Entity::Skybox->effect_component->texture_attributes[0]);
	}

	for (auto it = Entity::EffectComponentList.Begin(); it != Entity::EffectComponentList.End(); ++it)
	{		
		Owner<SceneProxy> proxyhandler = Create<SceneProxy>();						
		Owner<RenderState> renderhandler = Create<RenderState>();
		proxyhandler->state = renderhandler;
		List.PushBack(proxyhandler);

		renderhandler->InitShader((*it)->shaderpaths);
		renderhandler->material = (*it)->material_attribute->material;		
		// Create buffer for textures
		for (auto it2 = (*it)->texture_attributes.Begin(); it2 != (*it)->texture_attributes.End(); ++it2)
		{
			renderhandler->InitTexture(*it2);
		}		

		for (auto it2 = Entity::MeshComponentList.Begin(); it2 != Entity::MeshComponentList.End(); ++it2)
		{
			if ((*it)->owner == (*it2)->owner)
			{
				if ((*it2)->type == MeshComponent::MeshType::Mesh)
				{					
					proxyhandler->meshes.PushBack((*it2)->mesh);
				}
				else
				{
					auto mesh = static_cast<Observer<Resource::Mesh>>((*it2)->skeleton_mesh);
					proxyhandler->meshes.PushBack(mesh);
				}
				proxyhandler->Init(static_cast<int>((*it2)->type));
			}
		}		
	}
}