#pragma once

#include "Define.h"
#include "MeshComponent.h"

class CubeMapMeshComponent : public MeshComponent
{
public:
	void Boot() override;
	void Init() override;
};

inline void CubeMapMeshComponent::Boot()
{
	Load(PATH_SUFFIX MESH_PATH FILENAME_CUBEMAP);

	// This part can be optimize

	TextureAttribute* posx = new TextureAttribute();
	posx->Load(PATH_SUFFIX SKYBOX_PATH SKYBOX_POSX);

	TextureAttribute* negx = new TextureAttribute();
	negx->Load(PATH_SUFFIX SKYBOX_PATH SKYBOX_NEGX);

	TextureAttribute* posy = new TextureAttribute();
	posy->Load(PATH_SUFFIX SKYBOX_PATH SKYBOX_POSY);

	TextureAttribute* negy = new TextureAttribute();
	negy->Load(PATH_SUFFIX SKYBOX_PATH SKYBOX_NEGY);

	TextureAttribute* posz = new TextureAttribute();
	posz->Load(PATH_SUFFIX SKYBOX_PATH SKYBOX_POSZ);

	TextureAttribute* negz = new TextureAttribute();	negz->Load(PATH_SUFFIX SKYBOX_PATH SKYBOX_NEGZ);

	OwningPointer<TextureAttribute> posxhandler(posx);
	OwningPointer<TextureAttribute> negxhandler(negx);
	OwningPointer<TextureAttribute> posyhandler(posy);
	OwningPointer<TextureAttribute> negyhandler(negy);
	OwningPointer<TextureAttribute> poszhandler(posz);
	OwningPointer<TextureAttribute> negzhandler(negz);

	textures.push_back(posxhandler);
	textures.push_back(negxhandler);
	textures.push_back(posyhandler);
	textures.push_back(negyhandler);
	textures.push_back(poszhandler);
	textures.push_back(negzhandler);
}

inline void CubeMapMeshComponent::Init()
{

}