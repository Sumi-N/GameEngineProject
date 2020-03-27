#pragma once

#include "Define.h"

class Quad : public Object
{
public:
	void Boot() override;
	void Init() override;
};

inline void Quad::Boot()
{
	Object::Boot();

	MeshComponent* quadmesh = new MeshComponent();
	quadmesh->Load(PATH_SUFFIX MESH_PATH FILENAME_QUAD);
	quadmesh->owner = Entity::Query(this).p;

	MaterialAttribute* quadmaterial = new MaterialAttribute();
	quadmaterial->Kd = Vec3f(0, 1.0f, 0);
	quadmesh->SetMaterial(quadmaterial);

	Entity::RegisterMeshComponent(quadmesh);

	// Register quad information to render thread
	SceneProxy* quadproxy = new SceneProxy();
	quadproxy->mesh = quadmesh;
	Shader* quadshader = new Shader(PATH_SUFFIX SHADER_PATH QUAD_VERT, PATH_SUFFIX SHADER_PATH QUAD_FRAG);
	SceneEntity::Register(quadproxy, quadshader);
}

inline void Quad::Init()
{
	Object::Init();

	this->pos = Vec3f(0, -7, -50);
	this->rot = Vec3f(-90, 0, 0);
	this->scale = Vec3f(25.0, 25.0, 25.0);
}

