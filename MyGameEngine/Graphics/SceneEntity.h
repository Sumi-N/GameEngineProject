#pragma once

#include "Define.h"
#include "SceneProxy.h"
#include "RenderState.h"

class SceneEntity
{
public:
	static std::vector<OwningPointer<SceneProxy>> List;
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

		SkyBoxProxy->mesh   = Entity::Skybox->mesh;
		SkyBoxProxy->Init();

		RenderState* state = new RenderState();
		state->InitShader(Entity::Skybox->effect->shaderpaths);
		state->InitTexture(Entity::Skybox->effect->textures[0]);

		OwningPointer<RenderState> renderhandler;
		renderhandler = state;
		SkyBoxProxy->AddRenderState(renderhandler);
	}

	// Create scene format from entity
	for (auto it = Entity::MeshComponentList.begin(); it != Entity::MeshComponentList.end(); ++it)
	{
		SceneProxy * proxy = new SceneProxy();
		proxy->mesh = *it;
		proxy->Init();

		OwningPointer<SceneProxy> proxyhandler;
		proxyhandler = proxy;

		// Create render state
		for (auto it2 = Entity::EffectComponentList.begin(); it2 != Entity::EffectComponentList.end(); ++it2)
		{
			if ((*it)->owner == (*it2)->owner)
			{
				RenderState *  state = new RenderState();
				state->InitShader((*it2)->shaderpaths);

				// Create buffer for texture
				for (auto it3 = (*it2)->textures.begin(); it3 != (*it2)->textures.end(); ++it3)
				{
					state->InitTexture(*it3);
				}

				OwningPointer<RenderState> renderhandler;
				renderhandler = state;
				proxy->AddRenderState(renderhandler);
			}
		}

		List.push_back(proxyhandler);
	}
}