#pragma once
#include <PremadeParts/Quad.h>


class DepthMapDebugPlane : public Quad
{
	void Boot() override;
	void Init() override;
};

inline void DepthMapDebugPlane::Boot()
{
	Quad::Boot();

	SceneFormat* format = SceneEntity::Query(this);

	Shader* quadshader = new Shader(PATH_SUFFIX SHADER_PATH DEBUG_SHADOW_MAP_VERT, PATH_SUFFIX SHADER_PATH DEBUG_SHADOW_MAP_FRAG);
	format->ClearShaders();
	format->AddShader(quadshader);
}

inline void DepthMapDebugPlane::Init()
{
	Object::Init();

	pos = Vec3f(0, 10, -70);
	scale = Vec3f(15.0, 15.0, 15.0);
	rot = Vec3f(0, 0, 0);
}