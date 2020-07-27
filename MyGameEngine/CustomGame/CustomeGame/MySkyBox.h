#pragma once
#include <PremadeParts/Skybox.h>
#include <Thread/Define.h>

class MySkyBox : public SkyBox
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
	if (UserInput.QueryKey(VirtualKey::KEY_1) == InputState::Pressed)
	{
		currentstate = 1;
		ChangeBackGround();
	}
	if (UserInput.QueryKey(VirtualKey::KEY_2) == InputState::Pressed)
	{
		currentstate = 2;
		ChangeBackGround();
	}

	if (UserInput.QueryKey(VirtualKey::KEY_3) == InputState::Pressed)
	{
		currentstate = 0;
		ChangeBackGround();
	}
}