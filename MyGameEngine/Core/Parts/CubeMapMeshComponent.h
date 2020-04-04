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
}

inline void CubeMapMeshComponent::Init()
{

}