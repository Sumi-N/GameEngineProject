#pragma once

#include "Define.h"
#include "SceneProxy.h"
#include "RenderState.h"
#include "CubeMapProxy.h"

// Forward declaration
struct  GraphicRequiredData;

//struct SceneFormat
//{
//	SceneFormat(SceneProxy* i_proxy)
//	{
//		proxy = i_proxy;
//	}
//
//	SceneProxy* proxy;
//	std::vector<Shader*> shaders;
//
//	void ClearShaders();
//	void AddShader(Shader*);
//	void ReplaceShader(Shader*);
//	void BindAndDraw();
//};
//
//inline void SceneFormat::ClearShaders()
//{
//	shaders.clear();
//}
//
//inline void SceneFormat::AddShader(Shader* i_shader)
//{
//	shaders.push_back(i_shader);
//}
//
//inline void SceneFormat::ReplaceShader(Shader* i_shader)
//{
//	if (shaders.size() == 0)
//	{
//		shaders.push_back(i_shader);
//	}
//	else
//	{
//		shaders[shaders.size() - 1] = i_shader;
//	}
//}
//
//inline void SceneFormat::BindAndDraw()
//{
//	for (int i = 0; i < this->shaders.size(); i++)
//	{
//		shaders[i]->BindShader();
//		proxy->SetDrawType(shaders[i]->CheckDrawType());
//		proxy->Draw();
//	}
//}

struct CubeMapFormat
{
	CubeMapFormat()
	{
		skyboxproxy = nullptr;
		shader = nullptr;
	};

	CubeMapFormat(CubeMapProxy* i_proxy, Shader* i_shader)
	{
		skyboxproxy = i_proxy;
		shader = i_shader;
	}
	CubeMapProxy* skyboxproxy;
	Shader* shader;
};

class SceneEntity
{
public:
	static std::vector<OwningPointer<SceneProxy>> List;
	static CubeMapFormat SkyBoxScene;
	//static SceneFormat* Register(SceneProxy*);
	static void RegisterSkyBox(CubeMapProxy*, Shader*);
	//static SceneProxy* Query(const Object* i_obj);
	static void Init();
};

//inline SceneFormat* SceneEntity::Register(SceneProxy* i_proxy)
//{
//	SceneFormat format = SceneFormat(i_proxy);
//	List.push_back(format);
//	return &List[List.size() - 1];
//}

inline void SceneEntity::RegisterSkyBox(CubeMapProxy* i_cubemap, Shader* i_shader)
{
	CubeMapFormat format = CubeMapFormat(i_cubemap, i_shader);
	SkyBoxScene = format;
}

//inline SceneProxy* SceneEntity::Query(const Object* i_obj)
//{
//	for (int i = 0; i < List.size(); i++)
//	{
//		if (List[i]->mesh->owner == i_obj)
//		{
//			return List[i];
//		}
//	}
//	DEBUG_PRINT("Couldn't not find the object in the scene entity list");
//	return nullptr;
//}

inline void SceneEntity::Init()
{
	// Init sky-box cube map
	if (SkyBoxScene.skyboxproxy)
	{
		SkyBoxScene.skyboxproxy->Init();
		SkyBoxScene.shader->LoadShader();
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

	//for (auto it = List.begin(); it != List.end(); ++it)
	//{
	//	(*it).proxy->Init();
	//	for (auto it2 = (*it).shaders.begin(); it2 != (*it).shaders.end(); ++it2)
	//	{
	//		if (*it2)
	//		{
	//			(*it2)->LoadShader();
	//		}
	//	}
	//}
}