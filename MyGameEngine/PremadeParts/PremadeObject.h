#pragma once

#include "Define.h"

class PremadeObjebct : public Object
{
public:
	void Boot() override;
	void Init() override;

protected:
	MeshComponent* mesh;
};

inline void PremadeObjebct::Boot()
{
	Object::Boot();

	MeshComponent* thismesh = new MeshComponent();
	MaterialAttribute* material = new MaterialAttribute();
	thismesh->SetMaterial(material);
	thismesh->owner = Entity::Query(this).p;
	Entity::RegisterMeshComponent(thismesh);
	mesh = thismesh;

	//const char* shaderpaths[] =
	//{
	//	PATH_SUFFIX SHADER_PATH DEBUG_POLYGON_VERT,
	//	nullptr,
	//	nullptr,
	//	PATH_SUFFIX SHADER_PATH DEBUG_POLYGON_GEO,
	//	PATH_SUFFIX SHADER_PATH DEBUG_POLYGON_FRAG,
	//};

	//EffectComponent* effect = new EffectComponent();
	//effect->owner = Entity::Query(this).p;
	//effect->RegisterShaderPath(shaderpaths);
	//Entity::RegisterEffectComponent(effect);

#if defined(_DEBUG) && !defined(NDEBUG)
	//SHOW_DEBUG_POLYGON
	//SHOW_DEBUG_NORMAL_COLOR
	//SHOW_DEBUG_NORMAL_VECTOR
	//SHOW_DEBUG_VIEWDIRECTION
	//SHOW_DEBUG_LIGHTDIRECTION
	//SHOW_DEBUG_BP_BASIC

#endif // DEBUG

	{
	}
}

inline void PremadeObjebct::Init()
{
	Object::Init();
}