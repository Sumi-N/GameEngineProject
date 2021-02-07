#pragma once
#include "Define.h"

class Shader 
{
public:
	Shader() :
		vertpath    (nullptr),
		controlpath (nullptr),
		evalpath    (nullptr),
		geopath     (nullptr),
		fragpath    (nullptr)
	{}

	Shader(const char* i_vert, const char* i_frag) :
		vertpath    (i_vert),
		controlpath (nullptr),
		evalpath    (nullptr),
		geopath     (nullptr),
		fragpath    (i_frag)
	{}

	Shader(const char* i_vert, const char* i_geo, const char* i_frag) :
		vertpath    (i_vert),
		controlpath (nullptr),
		evalpath    (nullptr),
		geopath     (i_geo),
		fragpath    (i_frag)
	{}

	Shader(const char* i_vert, const char* i_control, const char* i_eval, const char* i_frag) :
		vertpath    (i_vert),
		controlpath (i_control),
		evalpath    (i_eval),
		geopath     (nullptr),
		fragpath    (i_frag)
	{}

	Shader(const char* i_vert, const char* i_control, const char * i_eval, const char* i_geo, const char* i_frag) :
		vertpath    (i_vert),
		controlpath (i_control),
		evalpath    (i_eval),
		geopath     (i_geo),
		fragpath    (i_frag)
	{}

	void SetShader(const char* i_vert, const char* i_frag);
	void SetShader(const char* i_vert, const char* i_geo, const char* i_frag);
	void SetShader(const char* i_vert, const char* i_control, const char * i_eval, const char* i_frag);
	void SetShader(const char* i_vert, const char* i_control, const char* i_eval, const char* i_geo, const char* i_frag);
	void LoadShader();
	void BindShader();
	bool HasTessellationShader();

private:
	const char* vertpath;
	const char* fragpath;
	const char* geopath;
	const char* controlpath;
	const char* evalpath;

#ifdef ENGINE_GRAPHIC_OPENGL
public:
	GLuint programid = 0;

private:

	static void LoadShader(Shader& io_shader, const char* i_vert, const char* i_frag);
	static void LoadShader(Shader& io_shader, const char* i_vert, const char* i_geo, const char* i_frag);
	static void LoadShader(Shader& io_shader, const char* i_vert, const char* i_control, const char* i_eval, const char* i_frag);
	static void LoadShader(Shader& io_shader, const char* i_vert, const char* i_control, const char* i_eval, const char* i_geo, const char* i_frag);

	static bool ReadShaderSource(const char* i_file, std::vector<GLchar> & io_buffer);
	static GLboolean PrintShaderInfoLog(GLuint i_shader, const char* str);
	static GLboolean PrintProgramInfoLog(GLuint i_program);
	static void AttachShaderProgram(Shader& io_shader, std::vector<GLchar> i_src, GLint i_shadertype);

#endif // ENGINE_GRAPHIC_OPENGL
};