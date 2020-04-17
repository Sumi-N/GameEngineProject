#pragma once
#include "Define.h"
#include "Shader.h"

constexpr std::pair<TextureType, int> TextureUnitList[] =
{
	{TextureType::SkyBox, 0},
	// For Bllin Shading


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

	Shader shader;
	void InitShader(const char**);
	void InitTexture(ObservingPointer<TextureAttribute>);
	void BindShaderState();
	void UnBindShaderState();

private:

	int unitlistsize;

#ifdef  ENGINE_GRAPHIC_OPENGL
	// Texture data
	std::vector<GLuint> textureids;
	std::vector<GLuint> textureunits;
#endif //  ENGINE_GRAPHIC_OPENGL
};

inline RenderState::RenderState()
{
	unitlistsize = sizeof(TextureUnitList) / sizeof(TextureUnitList[0]);
}