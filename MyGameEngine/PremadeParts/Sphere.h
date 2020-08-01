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

	mesh->Load(PATH_SUFFIX MESH_PATH "sphere.obj");
}

inline void Sphere::Init()
{
	PremadeObjebct::Init();
}