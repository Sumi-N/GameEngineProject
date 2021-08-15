#pragma once
#include "Define.h"
#include "Shader.h"

using namespace Tempest;

constexpr std::pair<TextureType, int> TextureUnitList[] =
{
	{TextureType::SkyBox, 2},

	// For PBR 
	{TextureType::Albedo, 10},
	{TextureType::Normal, 11},
	{TextureType::Roughness, 12},
	{TextureType::Metalic, 13},
	{TextureType::AmbientOcclusion, 14},
};

class RenderState
{
public: 
	RenderState();
	~RenderState() = default;

	Shader shader;

	void InitShader(const char**);
	void InitTexture(ObservingPointer<TextureAttribute>);
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

inline RenderState::RenderState()
{
	unitlistsize = sizeof(TextureUnitList) / sizeof(TextureUnitList[0]);
}