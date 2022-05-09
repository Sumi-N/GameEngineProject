#include "RenderState.h"

#ifdef  ENGINE_GRAPHIC_OPENGL

void RenderState::InitShader(const char** i_paths)
{
	// vertex and fragment shader
	if (i_paths[0] && !i_paths[1] && !i_paths[2] && !i_paths[3] && i_paths[4])
	{
		shader.SetShader(i_paths[0], i_paths[4]);
	}
	// vertex, geometry and fragment shader 
	else if (i_paths[0] && !i_paths[1] && !i_paths[2] && i_paths[3] && i_paths[4])
	{
		shader.SetShader(i_paths[0], i_paths[3], i_paths[4]);
	}
	// vertex, tessellation and fragment shader
	else if (i_paths[0] && i_paths[1] && i_paths[2] && !i_paths[3] && i_paths[4])
	{
		shader.SetShader(i_paths[0], i_paths[1], i_paths[2], i_paths[4]);
	}
	// vertex, tessellation, geometry and fragment shader
	else if (i_paths[0] && i_paths[1] && i_paths[2] && i_paths[3] && i_paths[4])
	{
		shader.SetShader(i_paths[0], i_paths[1], i_paths[2], i_paths[3], i_paths[4]);
	}
	else
	{
		DEBUG_ASSERT(false);
	}

	shader.LoadShader();
}

void RenderState::InitTexture(const Resource::TextureType& i_type, Owner<Resource::Texture>& i_resource)
{
	for (int i = 0; i < unitlistsize; i++)
	{
		if (TextureUnitList[i].first == i_type)
		{			
			int width = i_resource->width;
			int height = i_resource->height;
			void* data = i_resource->pixels.Data();

			if (i_type == TextureType::SkyBox)
			{
				textureunits.PushBack(TextureUnitList[i].second);
				textureids.Resize(textureunits.Size());
				glGenTextures(1, &textureids[textureids.Size() - 1]);
				glActiveTexture(GL_TEXTURE0 + TextureUnitList[i].second);
				glBindTexture(GL_TEXTURE_2D, textureids[textureids.Size() - 1]);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, static_cast<GLsizei>(width), static_cast<GLsizei>(height), 0, GL_RGB, GL_FLOAT, data);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			}
			else
			{
				textureunits.PushBack(TextureUnitList[i].second);
				textureids.Resize(textureunits.Size());
				glGenTextures(1, &textureids[textureids.Size() - 1]);
				glActiveTexture(GL_TEXTURE0 + TextureUnitList[i].second);
				glBindTexture(GL_TEXTURE_2D, textureids[textureids.Size() - 1]);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, static_cast<GLsizei>(width), static_cast<GLsizei>(height), 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glGenerateMipmap(GL_TEXTURE_2D);
			}

			return;
		}
	}
	DEBUG_ASSERT(false);
}

void RenderState::BindTextureUnit()
{
	for (int i = 0; i < textureunits.Size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + textureunits[i]);
		glBindTexture(GL_TEXTURE_2D, textureids[i]);
	}
}

void RenderState::BindShaderState()
{
	shader.BindShader();
	BindTextureUnit();
}

void RenderState::UnBindShaderState()
{
	for (int i = 0; i < textureunits.Size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + textureunits[i]);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

#endif //  ENGINE_GRAPHIC_OPENGL
