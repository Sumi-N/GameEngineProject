#pragma once

#include "Define.h"

class PremadeObjebct : public Object
{
public:
	PremadeObjebct() : mesh(nullptr){}

	void Boot() override;
	void Init() override;

protected:
	OwningPointer<MeshComponent> mesh;
};

inline void PremadeObjebct::Boot()
{
	Object::Boot();

	mesh = ObjectFactory<MeshComponent>::Create();
	OwningPointer<MaterialAttribute> material;
	material = ObjectFactory<MaterialAttribute>::Create();
	mesh->SetMaterial(material);
	mesh->owner = Entity::Query(this).p;
	Entity::RegisterMeshComponent(mesh);

	//const char* shaderpaths[] =
	//{
	//	PATH_SUFFIX SHADER_PATH DEBUG_POLYGON_VERT,
	//	nullptr,
	//	nullptr,
	//	PATH_SUFFIX SHADER_PATH DEBUG_POLYGON_GEO,
	//	PATH_SUFFIX SHADER_PATH DEBUG_POLYGON_FRAG,
	//};

	//OwningPointer<EffectComponent> effect;
	//effect = ObjectFactory<EffectComponent>::Create();
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