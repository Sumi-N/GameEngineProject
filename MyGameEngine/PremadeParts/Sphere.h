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
}

inline void Sphere::Init()
{
	PremadeObjebct::Init();
}