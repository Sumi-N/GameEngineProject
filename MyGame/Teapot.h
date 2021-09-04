#pragma once

#include <Core/Math/Vector.h>
#include <PremadeParts/PremadeObject.h>

#include <Graphics/SceneEntity.h>

namespace Tempest
{

	class Teapot : public PremadeObjebct
	{
		void Boot() override;
		void Init() override;
		void Update(float i_dt) override;
	};

	inline void Teapot::Boot()
	{
		PremadeObjebct::Boot();

		mesh_component->Load(PATH_SUFFIX BIN_MESH_PATH "teapot.tmd");

		OwningPointer<TextureAttribute> teapottexture = OwningPointer<TextureAttribute>::Create(teapottexture);
		OwningPointer<TextureAttribute> teapottexture2 = OwningPointer<TextureAttribute>::Create(teapottexture2);
		OwningPointer<TextureAttribute> teapottexture3 = OwningPointer<TextureAttribute>::Create(teapottexture3);

		teapottexture->Load(PATH_SUFFIX BIN_TEXTURE_PATH "albedo\\brickwall.ttd", TextureType::PB_Diffuse);
		teapottexture2->Load(PATH_SUFFIX BIN_TEXTURE_PATH "albedo\\brickwall.ttd", TextureType::PB_Specular);
		teapottexture3->Load(PATH_SUFFIX BIN_TEXTURE_PATH "normal\\brickwall_normal.ttd", TextureType::PB_Normal);

		const char* shaderpaths[] =
		{
			PATH_SUFFIX SHADER_PATH BLINN_PHONG_VERT,
			nullptr,
			nullptr,
			nullptr,
			PATH_SUFFIX SHADER_PATH BLINN_PHONG_FRAG,
		};

		effect_component->RegisterShaderPath(shaderpaths);
		effect_component->SetTexture(teapottexture);
		effect_component->SetTexture(teapottexture2);
		effect_component->SetTexture(teapottexture3);
	}

	inline void Teapot::Init()
	{
		PremadeObjebct::Init();
	}

	inline void Teapot::Update(float i_dt)
	{
		PremadeObjebct::Update(i_dt);
	}

}