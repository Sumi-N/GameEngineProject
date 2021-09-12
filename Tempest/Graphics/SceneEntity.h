#pragma once

#include "Define.h"
#include "SceneProxy.h"
#include "RenderState.h"

using namespace Tempest;

class SceneEntity
{
public:
	static Array<OwningPointer<SceneProxy>> List;
	static OwningPointer<SceneProxy> SkyBoxProxy;
	static void Init();
};

inline void SceneEntity::Init()
{
	// Init sky-box cube map
	if (Entity::Skybox)
	{
		SceneProxy* proxy = new SceneProxy();
		SceneEntity::SkyBoxProxy = proxy;

		SkyBoxProxy->mesh = Entity::Skybox->mesh_component->mesh;
		SkyBoxProxy->Init(static_cast<int>(Entity::Skybox->mesh_component->type));

		RenderState* state = new RenderState();
		state->InitShader(Entity::Skybox->effect_component->shaderpaths);
		state->InitTexture(Entity::Skybox->effect_component->texture_attributes[0]);

		OwningPointer<RenderState> renderhandler;
		renderhandler = state;
		SkyBoxProxy->AddRenderState(renderhandler);
	}

	// Create scene format from entity
	for (auto it = Entity::MeshComponentList.Begin(); it != Entity::MeshComponentList.End(); ++it)
	{
		SceneProxy * proxy = new SceneProxy();
		if ((*it)->type == MeshComponent::MeshType::Mesh)
		{
			proxy->mesh = (*it)->mesh;
		}
		else
		{
			proxy->skeleton_mesh = (*it)->skeleton_mesh;
		}
		proxy->Init(static_cast<int>((*it)->type));

		OwningPointer<SceneProxy> proxyhandler;
		proxyhandler = proxy;

		// Create render state
		for (auto it2 = Entity::EffectComponentList.Begin(); it2 != Entity::EffectComponentList.End(); ++it2)
		{
			if ((*it)->owner == (*it2)->owner)
			{
				RenderState * state = new RenderState();
				state->InitShader((*it2)->shaderpaths);
				state->material = (*it2)->material_attribute->material;

				// Create buffer for texture
				for (auto it3 = (*it2)->texture_attributes.Begin(); it3 != (*it2)->texture_attributes.End(); ++it3)
				{
					state->InitTexture(*it3);
				}

				OwningPointer<RenderState> renderhandler;
				renderhandler = state;
				proxy->AddRenderState(renderhandler);
			}
		}

		List.PushBack(proxyhandler);
	}
}