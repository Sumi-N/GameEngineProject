#pragma  once
#include "FrameBuffer.h"

#ifdef ENGINE_GRAPHIC_OPENGL

void FrameBuffer::Init(FrameType i_type, int i_unitnum, int i_width, int i_height)
{
	frametype   = i_type;
	width       = i_width;
	height      = i_height;
	unit_number = i_unitnum;

	if (i_type == FrameType::ShadowCubeMap)
	{
	// Load shader
	shader.SetShader(PATH_SUFFIX SHADER_PATH SHADOW_CUBE_MAPPING_VERT, PATH_SUFFIX SHADER_PATH SHADOW_CUBE_MAPPING_GEO, PATH_SUFFIX SHADER_PATH SHADOW_CUBE_MAPPING_FRAG);
	shader.LoadShader();

	// Create frame buffer
	glGenFramebuffers(1, &bufferid);
	glBindFramebuffer(GL_FRAMEBUFFER, bufferid);

	glGenTextures(1, &textureid_depth);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureid_depth);

	for (int i = 0; i < 6; i++)
	{
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	}

	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, textureid_depth, 0);

	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	}
	else if (i_type == FrameType::EquirectangularMap)
	{
		// Load shader
		shader.SetShader(PATH_SUFFIX SHADER_PATH EQUIRECTANGULAR_MAP_VERT, PATH_SUFFIX SHADER_PATH EQUIRECTANGULAR_MAP_GEO, PATH_SUFFIX SHADER_PATH EQUIRECTANGULAR_MAP_FRAG);
		shader.LoadShader();

		glGenFramebuffers(1, &bufferid);
		glBindFramebuffer(GL_FRAMEBUFFER, bufferid);

		glGenTextures(1, &textureid_color);
		glBindTexture(GL_TEXTURE_CUBE_MAP, textureid_color);

		for (int i = 0; i < 6; i++)
		{
			// note that we store each face with 16 bit floating point values
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, nullptr);
		}

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, textureid_color, 0);

		glDrawBuffer(GL_COLOR_ATTACHMENT0);
		glReadBuffer(GL_NONE);
	}
	else if (i_type == FrameType::IrradianceMap)
	{
		// Load shader
		shader.SetShader(PATH_SUFFIX SHADER_PATH EQUIRECTANGULAR_MAP_VERT, PATH_SUFFIX SHADER_PATH EQUIRECTANGULAR_MAP_GEO, PATH_SUFFIX SHADER_PATH CUBEMAP_CONVOLUTION_DIFFUSE_FRAG);
		shader.LoadShader();

		glGenFramebuffers(1, &bufferid);
		glBindFramebuffer(GL_FRAMEBUFFER, bufferid);

		glGenTextures(1, &textureid_color);
		glBindTexture(GL_TEXTURE_CUBE_MAP, textureid_color);

		for (int i = 0; i < 6; i++)
		{
			// note that we store each face with 16 bit floating point values
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, nullptr);
		}

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, textureid_color, 0);

		glDrawBuffer(GL_COLOR_ATTACHMENT0);
		glReadBuffer(GL_NONE);
	}
	else if (i_type == FrameType::Specular)
	{
		// Load shader
		shader.SetShader(PATH_SUFFIX SHADER_PATH EQUIRECTANGULAR_MAP_VERT, PATH_SUFFIX SHADER_PATH EQUIRECTANGULAR_MAP_GEO, PATH_SUFFIX SHADER_PATH CUBEMAP_CONVOLUTION_SPECULAR_FRAG);
		shader.LoadShader();

		glGenFramebuffers(1, &bufferid);
		glBindFramebuffer(GL_FRAMEBUFFER, bufferid);

		glGenTextures(1, &textureid_color);
		glBindTexture(GL_TEXTURE_CUBE_MAP, textureid_color);

		for (int i = 0; i < 6; i++)
		{
			// note that we store each face with 16 bit floating point values
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, nullptr);
		}

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
		//glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, textureid_color, 0);

		glDrawBuffer(GL_COLOR_ATTACHMENT0);
		glReadBuffer(GL_NONE);
	}
	else if (i_type == FrameType::BRDF)
	{
		// Load shader
		shader.SetShader(PATH_SUFFIX SHADER_PATH IBL_BRDF_VERT, PATH_SUFFIX SHADER_PATH IBL_BRDF_FRAG);
		shader.LoadShader();

		// Create frame buffer
		glGenFramebuffers(1, &bufferid);
		glBindFramebuffer(GL_FRAMEBUFFER, bufferid);

		// Create color buffer
		glGenTextures(1, &textureid_color);
		glBindTexture(GL_TEXTURE_2D, textureid_color);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RG16F, i_width, i_height, 0, GL_RG, GL_FLOAT, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// bind textures to framebuffer
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, textureid_color, 0);

		glDrawBuffer(GL_COLOR_ATTACHMENT0);
	}
	else if (i_type == FrameType::Image)
	{
		// Load shader
		shader.SetShader(PATH_SUFFIX SHADER_PATH MIRROR_VERT, PATH_SUFFIX SHADER_PATH MIRROR_FRAG);
		shader.LoadShader();

		// Create frame buffer
		glGenFramebuffers(1, &bufferid);
		glBindFramebuffer(GL_FRAMEBUFFER, bufferid);

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
	else if (i_type == FrameType::ShadowMap)
	{
		// Load shader
		shader.SetShader(PATH_SUFFIX SHADER_PATH SHADOWMAP_VERT, PATH_SUFFIX SHADER_PATH SHADOWMAP_FRAG);
		shader.LoadShader();

		// Create frame buffer
		glGenFramebuffers(1, &bufferid);
		glBindFramebuffer(GL_FRAMEBUFFER, bufferid);

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
		//Specular framebuffer is the exception
		if (frametype != FrameType::Specular)
		{
			DEBUG_PRINT("Error! FrameBuffer is not complete");
		}
	}

	// Set back to original back buffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::BindFrame()
{
	glBindFramebuffer(GL_FRAMEBUFFER, bufferid);
	glViewport(0, 0, width, height);
	shader.BindShader();
}

void FrameBuffer::BindTextureUnit()
{
	glActiveTexture(GL_TEXTURE0 + static_cast<int>(unit_number));

	if (frametype == FrameType::ShadowCubeMap)
	{
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureid_depth);
	}
	else if (frametype == FrameType::EquirectangularMap)
	{
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureid_color);
	}
	else if (frametype == FrameType::IrradianceMap)
	{
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureid_color);
	}
	else if (frametype == FrameType::BRDF)
	{
	glBindTexture(GL_TEXTURE_2D, textureid_color);
	}
	else if (frametype == FrameType::Specular)
	{
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureid_color);
	}
	else if (frametype == FrameType::Image)
	{
		glBindTexture(GL_TEXTURE_2D, textureid_color);
	}
	else if (frametype == FrameType::ShadowMap)
	{
		glBindTexture(GL_TEXTURE_2D, textureid_depth);
	}
}

void FrameBuffer::RenderOnce()
{
	if (frametype == FrameType::EquirectangularMap)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		FrameBuffer::RenderToCube();
	}
	else if (frametype == FrameType::IrradianceMap)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		FrameBuffer::RenderToCube();
	}
	else if (frametype == FrameType::Specular)
	{
		unsigned int maxmiplevels = 5;
		for (unsigned int mip = 0; mip < maxmiplevels; ++mip)
		{
			unsigned int mipwidth = 128 * std::pow(0.5, mip);
			unsigned int mipheight = 128 * std::pow(0.5, mip);

			glViewport(0, 0, mipwidth, mipheight);
			float roughness = (float)mip / (float)(maxmiplevels - 1);

			glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, textureid_color, mip);

			GLuint roughness_value = glGetUniformLocation(shader.programid, "roughness");
			glUniform1f(roughness_value, roughness);


			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			FrameBuffer::RenderToCube();
		}
	}
	else if (frametype == FrameType::BRDF)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		FrameBuffer::RenderToQuad();
	}
	else
	{
		DEBUG_ASSERT(false);
	}

}
#endif // ENGINE_GRAPHIC_OPENGL
