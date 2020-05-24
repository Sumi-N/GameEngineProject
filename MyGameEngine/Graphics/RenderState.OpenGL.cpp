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

void RenderState::InitTexture(ObservingPointer<TextureAttribute> i_textureattribute)
{
	for (int i = 0; i < unitlistsize; i++)
	{
		if (TextureUnitList[i].first == i_textureattribute->type)
		{
			if (i_textureattribute->type == TextureType::SkyBox)
			{
				textureunits.push_back(TextureUnitList[i].second);
				textureids.resize(textureunits.size());
				glGenTextures(1, &textureids[textureids.size() - 1]);
				glActiveTexture(GL_TEXTURE0 + TextureUnitList[i].second);
				glBindTexture(GL_TEXTURE_2D, textureids[textureids.size() - 1]);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, i_textureattribute->width, i_textureattribute->height, 0, GL_RGB, GL_FLOAT, i_textureattribute->hdrpixels);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			}
			else
			{
				textureunits.push_back(TextureUnitList[i].second);
				textureids.resize(textureunits.size());
				glGenTextures(1, &textureids[textureids.size() - 1]);
				glActiveTexture(GL_TEXTURE0 + TextureUnitList[i].second);
				glBindTexture(GL_TEXTURE_2D, textureids[textureids.size() - 1]);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, i_textureattribute->width, i_textureattribute->height, 0, GL_RGB, GL_UNSIGNED_BYTE, i_textureattribute->pixels.data());
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
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
	for (int i = 0; i < textureunits.size(); i++)
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
	for (int i = 0; i < textureunits.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + textureunits[i]);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

#endif //  ENGINE_GRAPHIC_OPENGL
