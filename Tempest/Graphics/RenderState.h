#pragma once
#include "Define.h"
#include "Shader.h"

using namespace Tempest;

constexpr std::pair<Resource::TextureType, int> TextureUnitList[] =
{
	{Resource::TextureType::SkyBox, 2},

	// For PBR
	{Resource::TextureType::Albedo, 10},
	{Resource::TextureType::Normal, 11},
	{Resource::TextureType::Roughness, 12},
	{Resource::TextureType::Metalic, 13},
	{Resource::TextureType::AmbientOcclusion, 14},
};

class RenderState
{
public:
	RenderState()
	{
		unitlistsize = sizeof(TextureUnitList) / sizeof(TextureUnitList[0]);
	}
	~RenderState() = default;

	Shader shader;

	void InitShader(const char**);
	void InitShader(String*);
	void InitTexture(const Resource::TextureType&, Owner<Resource::Texture>&);
	void BindTextureUnit();
	void BindShaderState();
	void UnBindShaderState();

private:

	int unitlistsize;

#ifdef  ENGINE_GRAPHIC_OPENGL
	// Texture data
	Array<GLuint> textureids;
	Array<GLuint> textureunits;
#endif //  ENGINE_GRAPHIC_OPENGL
};