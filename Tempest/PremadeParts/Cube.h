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

	//mesh->Load(PATH_SUFFIX MESH_PATH FILENAME_SPHERE);
	
	//FBXImporter fbx;
	//fbx.Import(PATH_SUFFIX MESH_PATH "NotFree/Iris_Costume.fbx");
	//fbx.LoadMesh(PATH_SUFFIX MESH_PATH "NotFree/Iris_Nude.fbx", mesh->data, mesh->index);

	//OwningPointer<TextureAttribute> diffuse = OwningPointer<TextureAttribute>::Create(diffuse);
	//OwningPointer<TextureAttribute> speclar = OwningPointer<TextureAttribute>::Create(speclar);

	//diffuse->Load(PATH_SUFFIX TEXTURE_PATH "NotFree/tex_fuku2_Anon.png", TextureType::PB_Diffuse);
	//speclar->Load(PATH_SUFFIX TEXTURE_PATH "NotFree/tex_fuku2_Anon.png", TextureType::PB_Specular);

	//const char* shaderpaths[] =
	//{
	//	PATH_SUFFIX SHADER_PATH BLINN_PHONG_VERT,
	//	nullptr,
	//	nullptr,
	//	nullptr,
	//	PATH_SUFFIX SHADER_PATH BLINN_PHONG_FRAG,
	//};

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

	//effect->SetTexture(diffuse);
	//effect->SetTexture(speclar);

	effect->RegisterShaderPath(shaderpaths);
	Entity::RegisterEffectComponent(effect);

	this->Translate(Vec3f(0, 0, -80));
	this->scale = Vec3f(1.0f, 1.0f, 1.0f);
	//this->rot.x = -90;

	//SHOW_DEBUG_POLYGON
	//SHOW_DEBUG_NORMAL_VECTOR
}

inline void Cube::Init()
{
	PremadeObjebct::Init();

	mesh->material->metalic = 0.9f;
	mesh->material->roughness = 0.9f;
}