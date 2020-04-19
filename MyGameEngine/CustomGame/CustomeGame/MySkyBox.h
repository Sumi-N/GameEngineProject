#pragma once
#include <Core/Parts/CubeMap.h>
#include <Thread/Define.h>

class MySkyBox : public CubeMap
{
	int currentstate = 0;

	void Update(float) override;

	void ChangeBackGround();
};

inline void MySkyBox::ChangeBackGround()
{
	if (currentstate == 0)
	{
		TextureAttribute* texture = new TextureAttribute();
		texture->Load(PATH_SUFFIX TEXTURE_PATH SKYBOX_HDR_BLACK, TextureType::SkyBox);
		effect->ReplaceTexture(texture);
	}
	else if (currentstate == 1)
	{
		TextureAttribute* texture = new TextureAttribute();
		texture->Load(PATH_SUFFIX TEXTURE_PATH SKYBOX_HDR_PINTREE, TextureType::SkyBox);
		effect->ReplaceTexture(texture);
	}
	else if (currentstate == 2)
	{
		TextureAttribute* texture = new TextureAttribute();
		texture->Load(PATH_SUFFIX TEXTURE_PATH SKYBOX_HDR_FROZEN_WATERFALL, TextureType::SkyBox);
		effect->ReplaceTexture(texture);
	}

	Entity::RegisterSkyBox(this);
	data_game_own->requireprecompute = true;
}

inline void MySkyBox::Update(float i_dt)
{
	if (UserInput.QueryKey((unsigned int)VirtualKey::KEY_SPACE) == InputState::Pressed)
	{
		if (currentstate == 0)
		{
			currentstate = 1;
		}
		else if (currentstate == 1)
		{
			currentstate = 2;
		}
		else if (currentstate == 2)
		{
			currentstate = 0;
		}

		DEBUG_PRINT("%d", (uint8_t)UserInput.QueryKey((unsigned int)VirtualKey::KEY_SPACE));
		//ChangeBackGround();
	}
}