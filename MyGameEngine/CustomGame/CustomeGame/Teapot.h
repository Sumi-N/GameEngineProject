#pragma once
#include <Parts/Object.h>
#include <Core/Math/Vector.h>
#include <Parts/MeshComponent.h>
#include <Parts/MaterialAttribute.h>

#include <Graphics/SceneEntity.h>

class Teapot : public Object 
{
	void Boot() override;
	void Init() override;
	void Update(float i_dt) override;
};

inline void Teapot::Boot()
{
	Object::Boot();

	MeshComponent * teapotmesh = new MeshComponent();
	teapotmesh->Load("../../Assets/models/teapot.obj");
	teapotmesh->owner = Entity::ObjectList[0].p;
	MaterialAttribute* teapotmaterial = new MaterialAttribute();
	teapotmesh->SetMaterial(teapotmaterial);
	TextureAttribute * teapottexture = new TextureAttribute();
	teapottexture->Load("../../Assets/textures/brick.png");
	TextureAttribute * teapottexture2 = new TextureAttribute();
	teapottexture2->Load("../../Assets/textures/brick-specular.png");
	teapotmesh->SetTexture(teapottexture);
	teapotmesh->SetTexture(teapottexture2);

	Entity::RegisterMeshComponent(teapotmesh);


	// Register teapot information to render thread
	SceneProxy * teapotproxy = new SceneProxy();
	teapotproxy->mesh = teapotmesh;
	Shader * teapotshader = new Shader("../../Assets/shaders/blinn_phong.vert.glsl", "../../Assets/shaders/blinn_phong.frag.glsl");
	SceneEntity::Register(teapotproxy, teapotshader);
}

inline void Teapot::Init()
{
	Object::Init();
	this->pos = Vec3f(0, 0, -50);
	this->scale = Vec3f(1.0, 1.0, 1.0);
}

inline void Teapot::Update(float i_dt)
{
	Object::Update(i_dt);
}