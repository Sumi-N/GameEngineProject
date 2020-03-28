#pragma once
#include "Define.h"

class Shader 
{
#ifdef ENGINE_GRAPHIC_OPENGL
public:
	Shader() 
	{
		vertpath = nullptr;
		fragpath = nullptr;
		geopath  = nullptr;
		controlpath  = nullptr;
		evalpath     = nullptr;
	};

	Shader(const char* i_vert, const char* i_frag)
	{
		vertpath = i_vert;
		fragpath = i_frag;
		geopath = nullptr;
		controlpath = nullptr;
		evalpath    = nullptr;
	}

	Shader(const char* i_vert, const char* i_frag, const char* i_geo)
	{
		vertpath = i_vert;
		fragpath = i_frag;
		geopath  = i_geo;
		controlpath  = nullptr;
		evalpath     = nullptr;
	}

	Shader(const char* i_vert, const char* i_frag, const char* i_control, const char* i_eval)
	{
		vertpath = i_vert;
		fragpath = i_frag;
		geopath = nullptr;
		controlpath = i_control;
		evalpath = i_eval;
	}

	Shader(const char* i_vert, const char* i_frag, const char* i_geo, const char* i_control, const char * i_eval)
	{
		vertpath = i_vert;
		fragpath = i_frag;
		geopath  = i_geo;
		controlpath  = i_control;
		evalpath     = i_eval;
	}

	GLuint programid = 0;

	static void LoadShader(Shader& io_shader, const char* i_vert, const char* i_frag);
	static void LoadShader(Shader& io_shader, const char* i_vert, const char* i_frag, const char* i_geo);
	static void LoadShader(Shader& io_shader, const char* i_vert, const char* i_frag, const char* i_control, const char* i_eval);
	static void LoadShader(Shader& io_shader, const char* i_vert, const char* i_frag, const char* i_geo, const char* i_control, const char* i_eval);
	void BindShader();
	void LoadShader();

private:
	const char* vertpath;
	const char* fragpath;
	const char* geopath;
	const char* controlpath;
	const char* evalpath;

	static bool ReadShaderSource(const char* i_file, std::vector<GLchar> & io_buffer);
	static GLboolean PrintShaderInfoLog(GLuint i_shader, const char* str);
	static GLboolean PrintProgramInfoLog(GLuint i_program);

#endif // ENGINE_GRAPHIC_OPENGL
};