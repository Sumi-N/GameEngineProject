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
		shader = i_shader;
	}

	SceneProxy* proxy;
	Shader* shader;
};

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
	static void Init();
};

inline void SceneEntity::Register(SceneProxy* i_proxy, Shader* i_shader)
{
	SceneFormat scene = SceneFormat(i_proxy, i_shader);
	List.push_back(scene);
}

inline void SceneEntity::Init()
{
	if (Entity::SkyBox)
	{
		CubeMapProxy* skyboxproxy = new CubeMapProxy();
		SkyBoxScene.skyboxproxy = skyboxproxy;
		SkyBoxScene.skyboxproxy->mesh = static_cast<OwningPointer<MeshComponent>>(Entity::SkyBox);
		SkyBoxScene.skyboxproxy->Init();
		Shader* skyboxshader = new Shader("../../" SKYBOX_VERT_PATH, "../../" SKYBOX_FRAG_PATH);
		SkyBoxScene.shader = skyboxshader;
		SkyBoxScene.shader->LoadShader();
	}

	for (auto it = List.begin(); it != List.end(); ++it)
	{
		(*it).proxy->Init();
		(*it).shader->LoadShader();
	}
}