#pragma once

#include "Define.h"

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

namespace Resource
{

	//__declspec(align(16))
	struct Mesh
	{
		Vec3f vertex;
		Vec3f normal;
		Vec2f uv;
		//Vec2f padding; //For alignment purpose
		Vec3f tangent;
		Vec3f bitangent;
	};

	struct SkeletonMesh : public Mesh
	{
		Vec4u8t index;
		Vec4f   weight;
	};

	struct Material
	{
		Vec3f ambient;
		Vec3f diffuse;
		Vec3f emissive;
		Vec3f specular;
		float shininess;
	};

	struct Joint
	{
		Mat4f       inversed; // inversed bind pose translation matrix
		Vec3f       coord;
		std::string name;
		uint8_t     parent_index;
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
		Mat4f       global_inversed_matrix;
		uint8_t     parent_index;
	};

	struct AnimationSample
	{
		std::vector<JointPose> jointposes;
	};

	struct AnimationClip
	{
		Skeleton*                    skeleton;
		float                        frame_per_second;
		int                          frame_count;
		std::vector<AnimationSample> samples;
		bool                         is_looping;
	};

}