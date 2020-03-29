#pragma once
#include <PremadeParts/Quad.h>

class NormalMapDebugPlane : public Quad
{
	void Boot() override;
	void Init() override;
};

inline void NormalMapDebugPlane::Boot()
{
	Quad::Boot();

	SceneFormat* scneformat = SceneEntity::Query(this);

	TextureAttribute* quadtexture = new TextureAttribute();
	quadtexture->Load("../../Assets/textures/gray.png");

	TextureAttribute* quadtexture2 = new TextureAttribute();
	quadtexture2->Load("../../Assets/textures/gray.png");

	// normal map texture
	TextureAttribute* quadtexture3 = new TextureAttribute();
	quadtexture3->Load("../../Assets/textures/teapot_normal.png");

	TextureAttribute* quadtexture4 = new TextureAttribute();
	quadtexture4->Load("../../Assets/textures/teapot_disp.png");

	Shader* quadshader  = new Shader(PATH_SUFFIX SHADER_PATH "test_tessellation.vert.glsl", PATH_SUFFIX SHADER_PATH "debug_polygon.geo.glsl", PATH_SUFFIX SHADER_PATH "debug_polygon.frag.glsl");
	Shader* debugshader = new Shader(PATH_SUFFIX SHADER_PATH "test_tessellation.vert.glsl", PATH_SUFFIX SHADER_PATH "test_tessellation.control.glsl", PATH_SUFFIX SHADER_PATH "test_tessellation.eval.glsl", PATH_SUFFIX SHADER_PATH "normal_mapping.frag.glsl");

	scneformat->proxy->mesh->material->Kd = Vec3f(0.5, 0.5f, 0.5);
	scneformat->proxy->mesh->material->Ns = 100;

	scneformat->proxy->mesh->SetTexture(quadtexture);
	scneformat->proxy->mesh->SetTexture(quadtexture2);
	scneformat->proxy->mesh->SetTexture(quadtexture3);
	scneformat->proxy->mesh->SetTexture(quadtexture4);

	scneformat->ClearShaders();
	scneformat->AddShader(quadshader);
	scneformat->AddShader(debugshader);
}

inline void NormalMapDebugPlane::Init()
{
	Object::Init();

	pos = Vec3f(-30, 10, -60);
	scale = Vec3f(15.0, 15.0, 15.0);
	rot = Vec3f(0, 0, 0);
}