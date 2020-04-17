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
};

class FrameBuffer
{
public:

	FrameType frametype;
	Shader    shader;
	int unit_number;
	int width, height;

	static void RenderToQuad();
	static void RenderToCube();

#ifdef ENGINE_GRAPHIC_OPENGL

	void Init(FrameType i_type, int i_unitnum, int i_width, int i_height);
	void BindFrame();
	void BindTextureUnit();
	void RenderOnce();

	GLuint  bufferid = 0;
	GLuint  renderbufferid = 0;

	GLuint textureid_color;
	GLuint textureid_depth;

#endif // ENGINE_GRAPHIC_OPENGL

};