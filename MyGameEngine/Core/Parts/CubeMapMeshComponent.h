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

	TextureAttribute* texture[6];
	const char* filename[6] = 
	{
		PATH_SUFFIX SKYBOX_PATH SKYBOX_POSX,
		PATH_SUFFIX SKYBOX_PATH SKYBOX_NEGX,
		PATH_SUFFIX SKYBOX_PATH SKYBOX_POSY,
		PATH_SUFFIX SKYBOX_PATH SKYBOX_NEGY,
		PATH_SUFFIX SKYBOX_PATH SKYBOX_POSZ,
		PATH_SUFFIX SKYBOX_PATH SKYBOX_NEGZ,
	};

#pragma omp parallel for
	for (int i = 0; i < 6; i++)
	{
		texture[i] = new TextureAttribute();
		texture[i]->Load(filename[i]);
		OwningPointer<TextureAttribute> handler(texture[i]);
		textures.push_back(handler);
	}
}

inline void CubeMapMeshComponent::Init()
{

}