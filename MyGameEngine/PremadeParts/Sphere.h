#pragma once

#include "Define.h"
#include "PremadeObject.h"

class Sphere : public PremadeObjebct
{
public:
	void Boot() override;
	void Init() override;
};

inline void Sphere::Boot()
{
	PremadeObjebct::Boot();

	SceneFormat* format = SceneEntity::Query(this);
	format->proxy->mesh->Load(PATH_SUFFIX MESH_PATH FILENAME_SPHERE);

	Shader* shader = new Shader(PATH_SUFFIX SHADER_PATH DISNEY_PBR_VERT, PATH_SUFFIX SHADER_PATH DISNEY_PBR_FRAG);
	format->AddShader(shader);
}

inline void Sphere::Init()
{
	PremadeObjebct::Init();
}