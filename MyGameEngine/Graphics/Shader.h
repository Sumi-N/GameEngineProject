#pragma once
#include "Define.h"

class Shader 
{
#ifdef ENGINE_GRAPHIC_OPENGL
public:
	Shader() {};

	Shader(const char* i_vert, const char* i_frag)
	{
		vertpath = i_vert;
		fragpath = i_frag;
	}

	Shader(const char* i_vert, const char* i_frag, const char* i_geo)
	{
		vertpath = i_vert;
		fragpath = i_frag;
		geopath  = i_geo;
	}

	GLuint programid = 0;

	static void LoadShader(Shader& io_shader, const char* i_vert, const char* i_frag);
	static void LoadShader(Shader& io_shader, const char* i_vert, const char* i_frag, const char* i_geo);
	void BindShader();
	void LoadShader();

private:
	const char* vertpath;
	const char* fragpath;
	const char* geopath;

	static bool ReadShaderSource(const char* i_file, std::vector<GLchar> & io_buffer);
	static GLboolean PrintShaderInfoLog(GLuint i_shader, const char* str);
	static GLboolean PrintProgramInfoLog(GLuint i_program);

#endif // ENGINE_GRAPHIC_OPENGL
};