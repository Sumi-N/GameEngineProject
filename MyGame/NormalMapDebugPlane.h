#pragma once
#include <PremadeParts/Quad.h>

namespace Tempest
{

	class NormalMapDebugPlane : public Quad
	{
		void Boot() override;
		void Init() override;
	};

	inline void NormalMapDebugPlane::Boot()
	{
		Quad::Boot();

		OwningPointer<TextureAttribute> quadtexture = OwningPointer<TextureAttribute>::Create(quadtexture);
		OwningPointer<TextureAttribute> quadtexture2 = OwningPointer<TextureAttribute>::Create(quadtexture2);
		OwningPointer<TextureAttribute> quadtexture3 = OwningPointer<TextureAttribute>::Create(quadtexture3);
		OwningPointer<TextureAttribute> quadtexture4 = OwningPointer<TextureAttribute>::Create(quadtexture4);

		quadtexture->Load(PATH_SUFFIX BIN_TEXTURE_PATH "albedo/gray.ttd", TextureType::PB_Diffuse);
		quadtexture2->Load(PATH_SUFFIX BIN_TEXTURE_PATH "albedo/gray.ttd", TextureType::PB_Specular);
		quadtexture3->Load(PATH_SUFFIX BIN_TEXTURE_PATH "normal/teapot_normal.ttd", TextureType::PB_Normal);
		quadtexture4->Load(PATH_SUFFIX BIN_TEXTURE_PATH "displacement/teapot_disp.ttd", TextureType::PB_Displacement);

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

}