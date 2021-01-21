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
	
	FBXImporter fbx;
	fbx.LoadMesh(PATH_SUFFIX MESH_PATH "cube.fbx", mesh->data, mesh->index);

	const char* shaderpaths[] =
	{
		PATH_SUFFIX SHADER_PATH DEBUG_PBR_BASIC_VERT,
		nullptr,
		nullptr,
		nullptr,
		PATH_SUFFIX SHADER_PATH DEBUG_PBR_BASIC_FRAG,
	};

	OwningPointer<EffectComponent> effect = OwningPointer<EffectComponent>::Create(effect);
	effect->owner = Entity::Query(this).p;
	effect->RegisterShaderPath(shaderpaths);
	Entity::RegisterEffectComponent(effect);

	SHOW_DEBUG_NORMAL_VECTOR
}

inline void Cube::Init()
{
	PremadeObjebct::Init();
}