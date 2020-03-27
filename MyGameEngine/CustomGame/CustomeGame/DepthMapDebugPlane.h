#pragma once
#include <PremadeParts/Quad.h>


class DepthMapDebugPlane : public Object
{
	void Boot() override;
	void Init() override;
};

inline void DepthMapDebugPlane::Boot()
{
	Object::Boot();

	MeshComponent* quadmesh = new MeshComponent();
	quadmesh->Load(PATH_SUFFIX MESH_PATH FILENAME_QUAD);
	quadmesh->owner = Entity::Query(this).p;

	MaterialAttribute* quadmaterial = new MaterialAttribute();
	quadmaterial->Kd = Vec3f(1.0, 1.0f, 1.0);
	quadmesh->SetMaterial(quadmaterial);

	Entity::RegisterMeshComponent(quadmesh);

	// Register quad information to render thread
	SceneProxy* quadproxy = new SceneProxy();
	quadproxy->mesh = quadmesh;
	Shader* quadshader = new Shader(PATH_SUFFIX SHADER_PATH DEBUG_SHADOW_MAP_VERT, PATH_SUFFIX SHADER_PATH DEBUG_SHADOW_MAP_FRAG);
	SceneEntity::Register(quadproxy, quadshader);
}

inline void DepthMapDebugPlane::Init()
{
	Object::Init();

	pos = Vec3f(0, 10, -70);
	scale = Vec3f(15.0, 15.0, 15.0);
	rot = Vec3f(0, 0, 0);
}