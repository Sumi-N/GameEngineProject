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

	OwningPointer<TextureAttribute> quadtexture = ObjectFactory<TextureAttribute>::Create();
	OwningPointer<TextureAttribute> quadtexture2 = ObjectFactory<TextureAttribute>::Create();
	OwningPointer<TextureAttribute> quadtexture3 = ObjectFactory<TextureAttribute>::Create();
	OwningPointer<TextureAttribute> quadtexture4 = ObjectFactory<TextureAttribute>::Create();

	quadtexture->Load("../../Assets/textures/albedo/gray.png", TextureType::PB_Diffuse);
	quadtexture2->Load("../../Assets/textures/albedo/gray.png", TextureType::PB_Specular);
	quadtexture3->Load("../../Assets/textures/normal/teapot_normal.png", TextureType::PB_Normal);
	quadtexture4->Load("../../Assets/textures/displacement/teapot_disp.png", TextureType::PB_Displacement);

	//Shader* quadshader  = new Shader(PATH_SUFFIX SHADER_PATH "test_purpose/test_tessellation.vert.glsl", PATH_SUFFIX SHADER_PATH "debug_purpose/debug_polygon.geo.glsl", PATH_SUFFIX SHADER_PATH "debug_purpose/debug_polygon.frag.glsl");
	//Shader* debugshader = new Shader(PATH_SUFFIX SHADER_PATH "test_purpose/test_tessellation.vert.glsl", PATH_SUFFIX SHADER_PATH "test_purpose/test_tessellation.control.glsl", PATH_SUFFIX SHADER_PATH "test_purpose/test_tessellation.eval.glsl", PATH_SUFFIX SHADER_PATH "test_purpose/normal_mapping.frag.glsl");

	//scneformat->proxy->mesh->material->Kd = Vec3f(0.5, 0.5f, 0.5);
	//scneformat->proxy->mesh->material->Ns = 100;
}

inline void NormalMapDebugPlane::Init()
{
	Object::Init();

	pos = Vec3f(-30, 10, -60);
	scale = Vec3f(15.0, 15.0, 15.0);
	rot = Vec3f(0, 0, 0);
}