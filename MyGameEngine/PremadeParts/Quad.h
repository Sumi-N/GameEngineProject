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

	//SceneFormat* format = SceneEntity::Query(this);
	//format->proxy->mesh->Load(PATH_SUFFIX MESH_PATH FILENAME_QUAD);

	//format->proxy->mesh->material->Kd = Vec3f(.8f, .8f, .8f);
	//format->proxy->mesh->material->Ks = Vec3f(.8f, .8f, .8f);	
	//format->proxy->mesh->material->Ns = 1;

	const char* shaderpaths[] =
	{
		PATH_SUFFIX SHADER_PATH DEBUG_BP_BASIC_VERT,
		nullptr,
		nullptr,
		nullptr,
		PATH_SUFFIX SHADER_PATH DEBUG_BP_BASIC_FRAG,
	};

	EffectComponent* effect = new EffectComponent();
	effect->owner = Entity::Query(this).p;
	effect->RegisterShaderPath(shaderpaths);
	Entity::RegisterEffectComponent(effect);

	//Shader* quadshader = new Shader(PATH_SUFFIX SHADER_PATH QUAD_VERT, PATH_SUFFIX SHADER_PATH QUAD_FRAG);
	//Shader* quadshader = new Shader(PATH_SUFFIX SHADER_PATH DEBUG_BP_BASIC_VERT, PATH_SUFFIX SHADER_PATH DEBUG_BP_BASIC_FRAG);
	//format->ReplaceShader(quadshader);
}

inline void Quad::Init()
{
	PremadeObjebct::Init();
}

