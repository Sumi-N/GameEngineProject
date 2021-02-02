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

struct MaterialData
{
	Vec3f ambient;
	Vec3f diffuse;
	Vec3f emissive;
	Vec3f specular;
	float shininess;
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

struct Joint
{
	Mat4f       inversed; // inversed bind pose translation matrix
	const char* name;
	uint8_t     parent_index;
};

struct BlendingWeight
{
	int index;
	float weight;
};

struct Skeleton
{
	std::vector<Joint>   joints;
};

struct JointPose
{
	Quaternionf rot;
	Vec4f       trans;
	Vec4f       scale;
};

struct SkeletonPose
{
	Skeleton*  skeletons;
	JointPose* local_pose;
	Mat4f      global_pose;
};
