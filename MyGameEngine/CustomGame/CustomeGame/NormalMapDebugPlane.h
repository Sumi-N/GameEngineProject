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
	quadmaterial->Ns = 100;
	quadmesh->SetMaterial(quadmaterial);

	TextureAttribute* quadtexture = new TextureAttribute();
	quadtexture->Load("../../Assets/textures/gray.png");
	quadmesh->SetTexture(quadtexture);

	TextureAttribute* quadtexture2 = new TextureAttribute();
	quadtexture2->Load("../../Assets/textures/gray.png");
	quadmesh->SetTexture(quadtexture2);

	// normal map texture
	TextureAttribute* quadtexture3 = new TextureAttribute();
	quadtexture3->Load("../../Assets/textures/teapot_normal.png");
	quadmesh->SetTexture(quadtexture3);

	TextureAttribute* quadtexture4 = new TextureAttribute();
	quadtexture4->Load("../../Assets/textures/teapot_disp.png");
	quadmesh->SetTexture(quadtexture4);

	Entity::RegisterMeshComponent(quadmesh);

	// Register quad information to render thread
	SceneProxy* quadproxy = new SceneProxy();
	quadproxy->mesh = quadmesh;
	Shader* quadshader = new Shader(PATH_SUFFIX SHADER_PATH "normal_mapping.vert.glsl", PATH_SUFFIX SHADER_PATH "normal_mapping.frag.glsl");

	SceneFormat quadscene(quadproxy, quadshader);
	Shader* debugshader = new Shader(PATH_SUFFIX SHADER_PATH "test_tessellation.vert.glsl", PATH_SUFFIX SHADER_PATH "debug_polygon.frag.glsl", PATH_SUFFIX SHADER_PATH "debug_polygon.geo.glsl", PATH_SUFFIX SHADER_PATH "test_tessellation.control.glsl", PATH_SUFFIX SHADER_PATH "test_tessellation.eval.glsl");
	quadscene.AddShader(debugshader);

	SceneEntity::List.push_back(quadscene);
}

inline void NormalMapDebugPlane::Init()
{
	Object::Init();

	pos = Vec3f(-30, 10, -60);
	scale = Vec3f(15.0, 15.0, 15.0);
	rot = Vec3f(0, 0, 0);
}