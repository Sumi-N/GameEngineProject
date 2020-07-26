#pragma once
#include "Define.h"
#include "Shader.h"

// The number of enum also represents the texture unit number
enum class FrameType : uint8_t
{
	ShadowCubeMap        = 0,
	EquirectangularMap   = 1,
	IrradianceMap        = 2,
	Specular             = 3,
	BRDF                 = 4,
	Image                = 5,
	ShadowMap            = 6,

	UnInitialized       = 255,
};

class FrameBuffer
{
public:

	FrameType frametype = FrameType::UnInitialized;
	Shader    shader;
	int       unit_number = -1;
	int       width = 0, height = 0;

	static void RenderToQuad();
	static void RenderToCube();

#ifdef ENGINE_GRAPHIC_OPENGL

	void Init(FrameType i_type, int i_unitnum, int i_width, int i_height);
	void BindFrame();
	void BindTextureUnit();
	void RenderOnce();

	GLuint  bufferid = 0;
	GLuint  renderbufferid = 0;

	GLuint  textureid_color = 0;
	GLuint  textureid_depth = 0;

#endif // ENGINE_GRAPHIC_OPENGL

};