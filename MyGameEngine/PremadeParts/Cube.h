#pragma once

#include "Define.h"
#include "PremadeObject.h"
#include <ResourceManagement/FBXImporter.h>
#include <PremadeParts/Define.h>

class Cube : public PremadeObjebct
{
public:
	void Boot() override;
	void Init() override;
};

inline void Cube::Boot()
{
	PremadeObjebct::Boot();

	//mesh->Load(PATH_SUFFIX MESH_PATH FILENAME_CUBEMAP);
	//mesh->Load(PATH_SUFFIX MESH_PATH FILENAME_SPHERE);
	
	FBXImporter fbx;
	fbx.LoadMesh(PATH_SUFFIX MESH_PATH "twocubes.fbx", mesh->data, mesh->index);

	//const char* shaderpaths[] =
	//{
	//	PATH_SUFFIX SHADER_PATH DEBUG_PBR_BASIC_VERT,
	//	nullptr,
	//	nullptr,
	//	nullptr,
	//	PATH_SUFFIX SHADER_PATH DEBUG_PBR_BASIC_FRAG,
	//};

	//const char* shaderpaths[] =
	//{
	//	PATH_SUFFIX SHADER_PATH BLINN_PHONG_VERT,
	//	nullptr,
	//	nullptr,
	//	nullptr,
	//	PATH_SUFFIX SHADER_PATH BLINN_PHONG_FRAG,
	//};

	//OwningPointer<EffectComponent> effect = OwningPointer<EffectComponent>::Create(effect);
	//effect->owner = Entity::Query(this).p;
	//effect->RegisterShaderPath(shaderpaths);
	//Entity::RegisterEffectComponent(effect);

	this->Translate(Vec3f(0, 0, -80));
	this->scale = Vec3f(0.05f, 0.05f, 0.05f);

	SHOW_DEBUG_POLYGON
	SHOW_DEBUG_NORMAL_VECTOR
}

inline void Cube::Init()
{
	PremadeObjebct::Init();

	mesh->material->metalic = 0.9f;
	mesh->material->roughness = 0.0f;
}