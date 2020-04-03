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
	//SHOW_DEBUG_NORMAL
	//SHOW_DEBUG_VIEWDIRECTION
	//SHOW_DEBUG_LIGHTDIRECTION
	//SHOW_DEBUG_BP_BASIC
#endif // DEBUG

}

inline void PremadeObjebct::Init()
{
	Object::Init();
}