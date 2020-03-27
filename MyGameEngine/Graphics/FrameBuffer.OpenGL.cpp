#pragma  once
#include "FrameBuffer.h"

#ifdef ENGINE_GRAPHIC_OPENGL

void FrameBuffer::Init(FrameType i_type, int i_width, int i_height)
{
	frametype = i_type;
	width  = i_width;
	height = i_height;

	// Create frame buffer
	glGenFramebuffers(1, &bufferid);
	glBindFramebuffer(GL_FRAMEBUFFER, bufferid);

	if (i_type == FrameType::Mirror)
	{
		// Load shader
		Shader::LoadShader(shader, PATH_SUFFIX SHADER_PATH MIRROR_VERT, PATH_SUFFIX SHADER_PATH MIRROR_FRAG);

		// Create color buffer
		glGenTextures(1, &textureid_color);
		glBindTexture(GL_TEXTURE_2D, textureid_color);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, i_width, i_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		// Create depth buffer
		glGenTextures(1, &textureid_depth);
		glBindTexture(GL_TEXTURE_2D, textureid_depth);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, i_width, i_height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		// bind textures to framebuffer
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, textureid_color, 0);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, textureid_depth, 0);

		glDrawBuffer(GL_COLOR_ATTACHMENT0);
	}
	else if (i_type == FrameType::Shadow)
	{
		// Load shader
		Shader::LoadShader(shader, PATH_SUFFIX SHADER_PATH SHADOWMAP_VERT, PATH_SUFFIX SHADER_PATH SHADOWMAP_FRAG);

		// Create depth buffer
		glGenTextures(1, &textureid_depth);
		glBindTexture(GL_TEXTURE_2D, textureid_depth);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, i_width, i_height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		// attach depth texture as FBO's depth buffer
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, textureid_depth, 0);

		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
	}

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{  
		//Check for FBO completeness
		DEBUG_PRINT("Error! FrameBuffer is not complete");
	}

	// Set back to original back buffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::BindFrame()
{
	glViewport(0, 0, width, height);
	glBindFramebuffer(GL_FRAMEBUFFER, bufferid);
	shader.BindShader();
}

void FrameBuffer::BindTextureUnit()
{
	glActiveTexture(GL_TEXTURE0 + static_cast<int>(frametype));
	if (frametype == FrameType::Mirror)
	{
		glBindTexture(GL_TEXTURE_2D, textureid_color);
	}
	else if (frametype == FrameType::Shadow)
	{
		glBindTexture(GL_TEXTURE_2D, textureid_depth);
	}
}

#endif // ENGINE_GRAPHIC_OPENGL
