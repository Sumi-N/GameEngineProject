#include "Shader.h"

#ifdef ENGINE_GRAPHIC_OPENGL

void Shader::LoadShader(Shader & io_shader, const char* i_vert, const char* i_frag)
{
	std::vector<GLchar> vertsrc;
	std::vector<GLchar> fragsrc;

	ReadShaderSource(i_vert, vertsrc);
	ReadShaderSource(i_frag, fragsrc);

	// Create program;
	if (io_shader.programid != 0)
	{
		glDeleteProgram(io_shader.programid);
	}

	io_shader.programid = glCreateProgram();

	// Attach the shaders to the program

	// Vertex Shader
	if (vertsrc.data() != nullptr)
	{
		const GLuint vshader = glCreateShader(GL_VERTEX_SHADER);
		const char* vertsrcponter = vertsrc.data();
		glShaderSource(vshader, 1, &vertsrcponter, NULL);
		glCompileShader(vshader);

		if (PrintShaderInfoLog(vshader, "vertex shader"))
		{
			glAttachShader(io_shader.programid, vshader);
		}
		glDeleteShader(vshader);
	}

	// Fragment Shader
	if (fragsrc.data() != nullptr)
	{
		const GLuint fshader = glCreateShader(GL_FRAGMENT_SHADER);
		const char* fragsrcpointer = fragsrc.data();
		glShaderSource(fshader, 1, &fragsrcpointer, NULL);
		glCompileShader(fshader);

		if (PrintShaderInfoLog(fshader, "fragment shader"))
		{
			glAttachShader(io_shader.programid, fshader);
		}
		glDeleteShader(fshader);
	}

	// Link the program
	glBindAttribLocation(io_shader.programid, 0, "model_position");
	glBindAttribLocation(io_shader.programid, 1, "model_normal");
	glBindAttribLocation(io_shader.programid, 2, "model_texcoord");
	glBindFragDataLocation(io_shader.programid, 0, "color");
	glLinkProgram(io_shader.programid);

	if (PrintProgramInfoLog(io_shader.programid))
	{
		DEBUG_PRINT("Succeed compiling the shader %s and %s \n", i_vert, i_frag);
	}
	else
	{
		DEBUG_PRINT("Faild compiling the shader %s and %s \n", i_vert, i_frag);
	}
}

void Shader::LoadShader(Shader& io_shader, const char* i_vert, const char* i_frag, const char* i_geo)
{
	std::vector<GLchar> vertsrc;
	std::vector<GLchar> fragsrc;
	std::vector<GLchar> geosrc;

	ReadShaderSource(i_vert, vertsrc);
	ReadShaderSource(i_frag, fragsrc);
	ReadShaderSource(i_geo, geosrc);

	// Create program;
	if (io_shader.programid != 0)
	{
		glDeleteProgram(io_shader.programid);
	}

	io_shader.programid = glCreateProgram();

	// Attach the shaders to the program

	// Vertex Shader
	if (vertsrc.data() != nullptr)
	{
		const GLuint vshader = glCreateShader(GL_VERTEX_SHADER);
		const char* vertsrcponter = vertsrc.data();
		glShaderSource(vshader, 1, &vertsrcponter, NULL);
		glCompileShader(vshader);

		if (PrintShaderInfoLog(vshader, "vertex shader"))
		{
			glAttachShader(io_shader.programid, vshader);
		}
		glDeleteShader(vshader);
	}

	// Fragment Shader
	if (fragsrc.data() != nullptr)
	{
		const GLuint fshader = glCreateShader(GL_FRAGMENT_SHADER);
		const char* fragsrcpointer = fragsrc.data();
		glShaderSource(fshader, 1, &fragsrcpointer, NULL);
		glCompileShader(fshader);

		if (PrintShaderInfoLog(fshader, "fragment shader"))
		{
			glAttachShader(io_shader.programid, fshader);
		}
		glDeleteShader(fshader);
	}

	// Fragment Shader
	if (geosrc.data() != nullptr)
	{
		const GLuint gshader = glCreateShader(GL_GEOMETRY_SHADER);
		const char* geosrcpointer = geosrc.data();
		glShaderSource(gshader, 1, &geosrcpointer, NULL);
		glCompileShader(gshader);

		if (PrintShaderInfoLog(gshader, "geometry shader"))
		{
			glAttachShader(io_shader.programid, gshader);
		}
		glDeleteShader(gshader);
	}

	// Link the program
	glBindAttribLocation(io_shader.programid, 0, "model_position");
	glBindAttribLocation(io_shader.programid, 1, "model_normal");
	glBindAttribLocation(io_shader.programid, 2, "model_texcoord");
	glBindFragDataLocation(io_shader.programid, 0, "color");
	glLinkProgram(io_shader.programid);

	if (PrintProgramInfoLog(io_shader.programid))
	{
		DEBUG_PRINT("Succeed compiling the shader %s, %s and %s \n", i_vert, i_frag, i_geo);
	}
	else
	{
		DEBUG_PRINT("Faild compiling the shader %s, %s and %s \n", i_vert, i_frag, i_geo);
	}
}

void Shader::BindShader()
{
	glUseProgram(programid);
}

void Shader::LoadShader()
{
	if (geopath)
	{
		Shader::LoadShader(*this, vertpath, fragpath, geopath);
	}
	else
	{
		Shader::LoadShader(*this, vertpath, fragpath);
	}
}

bool Shader::ReadShaderSource(const char* i_file, std::vector<GLchar>& io_buffer)
{
	if (i_file == nullptr)
	{
		return false;
	}

	std::ifstream file(i_file, std::ios::binary);
	if (file.fail())
	{
		DEBUG_PRINT("Error: Can't open source file: %s \n", i_file);
		return false;
	}

	file.seekg(0L, std::ios::end);
	GLsizei size = static_cast<GLsizei>(file.tellg());

	io_buffer.resize(size + 1);
	file.seekg(0L, std::ios::beg);
	file.read(io_buffer.data(), size);
	io_buffer[size] = '\0';

	if (file.fail())
	{
		DEBUG_PRINT("Error: Could not read source file: %s \n", i_file);
		file.close();
		return false;
	}

	file.close();
	return true;
}

GLboolean Shader::PrintShaderInfoLog(GLuint shader, const char* str)
{
	// Get compile status
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
		DEBUG_PRINT("Compile Error in: %s \n", str);

	// Get the length of the compile log
	GLsizei bufSize;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &bufSize);
	if (bufSize > 1)
	{
		// Get the contents of the compile log
		std::vector<GLchar> infoLog(bufSize);
		GLsizei length;
		glGetShaderInfoLog(shader, bufSize, &length, &infoLog[0]);
		DEBUG_PRINT("%s \n", &infoLog[0]);
	}
	return static_cast<GLboolean>(status);
}

GLboolean Shader::PrintProgramInfoLog(GLuint i_program)
{
	// Get a link result
	GLint status;
	glGetProgramiv(i_program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE) 
		DEBUG_PRINT("Link Error.");
	// Get the log of the link result
	GLsizei bufSize;
	glGetProgramiv(i_program, GL_INFO_LOG_LENGTH, &bufSize);
	if (bufSize > 1)
	{
		// Get the contents of the link result
		std::vector<GLchar> infoLog(bufSize);
		GLsizei length;
		glGetProgramInfoLog(i_program, bufSize, &length, &infoLog[0]);
		DEBUG_PRINT("%s \n", &infoLog[0]);
	}
	return static_cast<GLboolean>(status);
}

#endif // ENGINE_GRAPHIC_OPENGL