#pragma once
#include <PremadeParts/Quad.h>

class NormalMapDebugPlane : public Object
{
	void Boot() override;
	void Init() override;
};

inline void NormalMapDebugPlane::Boot()
{
	Object::Boot();

	MeshComponent* quadmesh = new MeshComponent();
	quadmesh->Load(PATH_SUFFIX MESH_PATH FILENAME_QUAD);
	quadmesh->owner = Entity::Query(this).p;

	MaterialAttribute* quadmaterial = new MaterialAttribute();
	quadmaterial->Kd = Vec3f(0.5, 0.5f, 0.5);
	quadmesh->SetMaterial(quadmaterial);
	TextureAttribute* quadtexture = new TextureAttribute();
	quadtexture->Load("../../Assets/textures/teapot_normal.png");
	quadmesh->SetTexture(quadtexture);

	Entity::RegisterMeshComponent(quadmesh);

	// Register quad information to render thread
	SceneProxy* quadproxy = new SceneProxy();
	quadproxy->mesh = quadmesh;
	Shader* quadshader = new Shader(PATH_SUFFIX SHADER_PATH "blinn_phong.vert.glsl", PATH_SUFFIX SHADER_PATH "blinn_phong.frag.glsl");
	SceneEntity::Register(quadproxy, quadshader);
}

inline void NormalMapDebugPlane::Init()
{
	Object::Init();

	pos = Vec3f(-20, 10, -40);
	scale = Vec3f(15.0, 15.0, 15.0);
	rot = Vec3f(0, 90, 0);
}