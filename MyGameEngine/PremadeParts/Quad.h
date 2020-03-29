#pragma once

#include "Define.h"
#include "PremadeObject.h"

class Quad : public PremadeObjebct
{
public:
	void Boot() override;
	void Init() override;
};

inline void Quad::Boot()
{
	PremadeObjebct::Boot();

	SceneFormat* format = SceneEntity::Query(this);
	format->proxy->mesh->Load(PATH_SUFFIX MESH_PATH FILENAME_QUAD);

	format->proxy->mesh->material->Kd = Vec3f(1.0f, 0.0f, 1.0f);

	Shader* quadshader = new Shader(PATH_SUFFIX SHADER_PATH QUAD_VERT, PATH_SUFFIX SHADER_PATH QUAD_FRAG);
	format->AddShader(quadshader);
}

inline void Quad::Init()
{
	PremadeObjebct::Init();

	this->pos = Vec3f(0, -7, -50);
	this->rot = Vec3f(-90, 0, 0);
	this->scale = Vec3f(25.0, 25.0, 25.0);
}

