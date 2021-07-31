#pragma once

#include "Define.h"

using namespace Tempest;

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
	struct MeshPoint
	{
		Vec3f vertex;
		Vec3f normal;
		Vec2f uv;
		//Vec2f padding; //For alignment purpose
		Vec3f tangent;
		Vec3f bitangent;
	};

	struct SkeletonMeshPoint : public MeshPoint
	{
		Vec4u8t index;
		Vec4f   weight;
	};

	struct Material
	{
		Vec4f albedo;
		float roughness;
		float metalic;		
	};

	struct Joint
	{
		Mat4f       inversed; // inversed bind pose translation matrix
		Vec3f       coord;
		String name;
		uint8_t     parent_index;
	};

	struct Skeleton
	{
		Array<Joint>   joints;
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
		Array<JointPose> jointposes;
	};

	struct AnimationClip
	{
		Skeleton*                    skeleton;
		float                        frame_per_second;
		int                          frame_count;
		Array<AnimationSample> samples;
		bool                         is_looping;
	};

	struct Mesh
	{
		Array<MeshPoint> data;
		Array<uint32_t> index;

		static Tempest::Result Load(const char* i_filepath, Array<Resource::MeshPoint>& o_data, Array<uint32_t>& o_index)
		{				
			Tempest::File in(i_filepath, Tempest::File::Format::BinaryRead);

			RETURN_IFNOT_SUCCESS(in.Open())

			size_t data_size;
			size_t index_size;

			RETURN_IFNOT_SUCCESS(in.Read(&data_size, sizeof(size_t)))
			RETURN_IFNOT_SUCCESS(in.Read(&index_size, sizeof(size_t)))

			o_data.resize(data_size);
			o_index.resize(index_size);

			RETURN_IFNOT_SUCCESS(in.Read(o_data.data(), data_size * sizeof(Resource::MeshPoint)))
			RETURN_IFNOT_SUCCESS(in.Read(o_index.data(), index_size * sizeof(Resource::MeshPoint)))

			in.Close();

			return Tempest::ResultValue::Success;
		}
	};

	struct SkeletonMesh
	{
		Array<SkeletonMeshPoint> data;
		Array<uint32_t> index;
	};

	struct  Texture
	{
		int width, height;
		Array<Vec3u8t> pixels;

		static Tempest::Result Load(const char* i_filepath, int& o_width, int& o_height, Array<Vec3u8t>& o_pixels)
		{
			o_pixels.clear();

			Tempest::File in(i_filepath, Tempest::File::Format::BinaryRead);

			RETURN_IFNOT_SUCCESS(in.Open());

			RETURN_IFNOT_SUCCESS(in.Read(&o_width, sizeof(int)))
			RETURN_IFNOT_SUCCESS(in.Read(&o_height, sizeof(int)))

			o_pixels.resize((size_t)o_width * o_height);


			RETURN_IFNOT_SUCCESS(in.Read(o_pixels.data(), (size_t)o_width * o_height * sizeof(Vec3u8t)))

			in.Close();

			DEBUG_PRINT("Succeed loading texture %s", i_filepath);

			return Tempest::ResultValue::Success;
		}
	};
}