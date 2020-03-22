#pragma once

#include "Define.h"
#include "MeshComponent.h"

class CubeMapMeshComponent : public MeshComponent
{
	void Init() override;
};

inline void CubeMapMeshComponent::Init()
{
	Load(MESH_PATH FILENAME_CUBEMAP);

	// This part can be optimize

	TextureAttribute posx;
	posx.Load(SKYBOX_PATH  SKYBOX_POSX);

	TextureAttribute negx;
	negx.Load(SKYBOX_PATH  SKYBOX_POSX);

	TextureAttribute posy;
	posy.Load(SKYBOX_PATH  SKYBOX_POSX);

	TextureAttribute negy;
	negy.Load(SKYBOX_PATH  SKYBOX_POSX);

	TextureAttribute posz;
	posz.Load(SKYBOX_PATH  SKYBOX_POSX);

	TextureAttribute negz;
	negz.Load(SKYBOX_PATH  SKYBOX_POSX);

	OwningPointer<TextureAttribute> posxhandler(&posx);
	OwningPointer<TextureAttribute> negxhandler(&negx);
	OwningPointer<TextureAttribute> posyhandler(&posy);
	OwningPointer<TextureAttribute> negyhandler(&negy);
	OwningPointer<TextureAttribute> poszhandler(&posz);
	OwningPointer<TextureAttribute> negzhandler(&negz);

	textures.push_back(posxhandler);
	textures.push_back(negxhandler);
	textures.push_back(posyhandler);
	textures.push_back(negyhandler);
	textures.push_back(poszhandler);
	textures.push_back(negzhandler);
}