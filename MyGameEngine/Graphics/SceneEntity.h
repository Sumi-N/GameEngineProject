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
	CubeMapProxy* skybox;
	Shader* shader;
};

class SceneEntity
{
public:
	static std::vector<SceneFormat> List;
	static CubeMapFormat SkyBox;
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
	for (auto it = List.begin(); it != List.end(); ++it)
	{
		(*it).proxy->Init();
		(*it).shader->LoadShader();
	}
}