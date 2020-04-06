#pragma once

#include "Define.h"

class PremadeObjebct : public Object
{
public:
	void Boot() override;
	void Init() override;
};

inline void PremadeObjebct::Boot()
{
	Object::Boot();

	MeshComponent* mesh = new MeshComponent();
	MaterialAttribute* material = new MaterialAttribute();
	mesh->SetMaterial(material);
	mesh->owner = Entity::Query(this).p;
	Entity::RegisterMeshComponent(mesh);

	SceneProxy* proxy = new SceneProxy();
	proxy->mesh       = mesh;
	SceneFormat* format = SceneEntity::Register(proxy);

#if defined(_DEBUG) && !defined(NDEBUG)
	//SHOW_DEBUG_POLYGON
	//SHOW_DEBUG_NORMAL_COLOR
	//SHOW_DEBUG_NORMAL_VECTOR
	//SHOW_DEBUG_VIEWDIRECTION
	//SHOW_DEBUG_LIGHTDIRECTION
	//SHOW_DEBUG_BP_BASIC

#endif // DEBUG

	{
		Shader* debugshader = new Shader(PATH_SUFFIX SHADER_PATH DEBUG_POLYGON_VERT, PATH_SUFFIX SHADER_PATH DEBUG_POLYGON_GEO, PATH_SUFFIX SHADER_PATH DEBUG_POLYGON_FRAG);
		format->AddShader(debugshader);
	}
}

inline void PremadeObjebct::Init()
{
	Object::Init();
}