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

	format->proxy->mesh->material->Kd = Vec3f(.8f, .8f, .8f);
	format->proxy->mesh->material->Ks = Vec3f(.8f, .8f, .8f);	
	format->proxy->mesh->material->Ns = 1;

	//Shader* quadshader = new Shader(PATH_SUFFIX SHADER_PATH QUAD_VERT, PATH_SUFFIX SHADER_PATH QUAD_FRAG);
	Shader* quadshader = new Shader(PATH_SUFFIX SHADER_PATH DEBUG_BP_BASIC_VERT, PATH_SUFFIX SHADER_PATH DEBUG_BP_BASIC_FRAG);
	format->ReplaceShader(quadshader);
}

inline void Quad::Init()
{
	PremadeObjebct::Init();
}

