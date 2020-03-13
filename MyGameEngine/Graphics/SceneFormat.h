#pragma once

#include "Define.h"
#include "SceneProxy.h"
#include "Shader.h"

struct SceneFormat
{
	SceneFormat(SceneProxy * i_proxy, Shader * i_shader)
	{
		proxy = i_proxy;
		shader = i_shader;
	}

	SceneProxy* proxy;
	Shader* shader;

	static std::vector<SceneFormat> List;
	static void Register(SceneProxy*, Shader*);
	static void Init();
	static void Draw();
};

inline void SceneFormat::Register(SceneProxy* i_proxy, Shader* i_shader)
{
	SceneFormat scene = SceneFormat(i_proxy, i_shader);
	List.push_back(scene);
}

inline void SceneFormat::Init()
{
	for (auto it = List.begin(); it != List.end(); ++it)
	{
		(*it).proxy->Init();
	}
}

inline void SceneFormat::Draw()
{
	for (auto it = List.begin(); it != List.end(); ++it)
	{
		(*it).shader->BindShader();
		(*it).proxy->Draw();
	}
}