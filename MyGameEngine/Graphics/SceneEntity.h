#pragma once

#include "Define.h"
#include "SceneProxy.h"
#include "CubeMapProxy.h"
#include "Shader.h"

// Forward declaration
struct  GraphicRequiredData;

struct SceneFormat
{
	SceneFormat(SceneProxy* i_proxy, Shader* i_shader)
	{
		proxy = i_proxy;
		shaders.push_back(i_shader);
	}

	SceneProxy* proxy;
	std::vector<Shader*> shaders;

	void ClearShaders();
	void AddShader(Shader*);
	void BindAndDraw();
};

inline void SceneFormat::ClearShaders()
{
	shaders.clear();
}

inline void SceneFormat::AddShader(Shader* i_shader)
{
	shaders.push_back(i_shader);
}

inline void SceneFormat::BindAndDraw()
{
	for (int i = 0; i < this->shaders.size(); i++)
	{
		shaders[i]->BindShader();
		proxy->SetDrawType(shaders[i]->CheckDrawType());
		proxy->Draw();
	}
}

struct CubeMapFormat
{
	CubeMapFormat(){};
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
	static std::vector<SceneFormat> List;
	static CubeMapFormat SkyBoxScene;
	static void Register(SceneProxy*, Shader*);
	static SceneFormat* Query(const Object* i_obj);
	static void Init();
};

inline void SceneEntity::Register(SceneProxy* i_proxy, Shader* i_shader)
{
	SceneFormat scene = SceneFormat(i_proxy, i_shader);
	List.push_back(scene);
}

inline SceneFormat* SceneEntity::Query(const Object* i_obj)
{
	for (int i = 0; i < List.size(); i++)
	{
		if (List[i].proxy->mesh->owner == i_obj)
		{
			return &List[i];
		}
	}
	DEBUG_PRINT("Coulnd't not find the object in SceneEntity list");
	return nullptr;
}

inline void SceneEntity::Init()
{
	if (Entity::SkyBox)
	{
		CubeMapProxy* skyboxproxy = new CubeMapProxy();
		SkyBoxScene.skyboxproxy = skyboxproxy;
		SkyBoxScene.skyboxproxy->mesh = static_cast<OwningPointer<MeshComponent>>(Entity::SkyBox);
		SkyBoxScene.skyboxproxy->Init();
		Shader* skyboxshader = new Shader(PATH_SUFFIX SHADER_PATH SKYBOX_VERT, PATH_SUFFIX SHADER_PATH SKYBOX_FRAG);
		SkyBoxScene.shader = skyboxshader;
		SkyBoxScene.shader->LoadShader();
	}

	for (auto it = List.begin(); it != List.end(); ++it)
	{
		(*it).proxy->Init();
		for (auto it2 = (*it).shaders.begin(); it2 != (*it).shaders.end(); ++it2)
		{
			(*it2)->LoadShader();
		}
	}
}