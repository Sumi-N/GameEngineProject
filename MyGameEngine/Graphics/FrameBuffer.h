#pragma once
#include "Define.h"
#include "Shader.h"

// The number of enum also represents the texture unit number
enum class FrameType : uint8_t
{
	Shadow = SHADOWMAPBINDINGUNIT,
	Mirror = 4,
};

class FrameBuffer
{
public:

	FrameType frametype;
	Shader    shader;
	int width, height;

#ifdef ENGINE_GRAPHIC_OPENGL

	void Init(FrameType i_type, int i_width, int i_height);
	void BindFrame();
	void BindTextureUnit();

	GLuint  bufferid;

	GLuint textureid_color;
	GLuint textureid_depth;

#endif // ENGINE_GRAPHIC_OPENGL

};