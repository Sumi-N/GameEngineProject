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

	if (i_type == FrameType::Image)
	{
		// Load shader
		shader.SetShader(PATH_SUFFIX SHADER_PATH MIRROR_VERT, PATH_SUFFIX SHADER_PATH MIRROR_FRAG);
		shader.LoadShader();

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
		shader.SetShader(PATH_SUFFIX SHADER_PATH SHADOWMAP_VERT, PATH_SUFFIX SHADER_PATH SHADOWMAP_FRAG);
		shader.LoadShader();

		// Create depth buffer
		glGenTextures(1, &textureid_depth);
		glBindTexture(GL_TEXTURE_2D, textureid_depth);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, i_width, i_height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		// attach depth texture as FBO's depth buffer
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, textureid_depth, 0);

		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
	}
	else if(i_type == FrameType::ShadowCubeMap)
	{
		glGenTextures(1, &textureid_depth);
		glBindTexture(GL_TEXTURE_CUBE_MAP, textureid_depth);
		glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		for (int i = 0; i < 6; i++)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT,
				width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, textureid_depth, 0);
		}

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
	if (frametype == FrameType::Image)
	{
		glBindTexture(GL_TEXTURE_2D, textureid_color);
	}
	else if (frametype == FrameType::Shadow)
	{
		glBindTexture(GL_TEXTURE_2D, textureid_depth);
	}
}

#endif // ENGINE_GRAPHIC_OPENGL
