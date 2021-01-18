#pragma once

#include "Define.h"

#ifdef ENGINE_PLATFORM_WINDOWS
__declspec(align(16))
#endif // ENGINE_PLATFORM_WINDOWS
struct MeshData
{
	Vec3f vertex;
	Vec3f normal;
	Vec2f uv;
	Vec2f padding; //For alignment purpose
	Vec3f tangent;
	Vec3f bitangent;
};

struct Joint
{

};

enum class TextureType : int8_t
{
	SkyBox = -1,
	Ohter = -1,

	//////////////////////

	Albedo = 0,
	Normal = 1,
	Roughness = 2,
	Metalic = 3,
	AmbientOcclusion = 4,

	//////////////////////

	PB_Diffuse = 0,
	PB_Specular = 1,
	PB_Normal = 2,
	PB_Displacement = 3,
};
