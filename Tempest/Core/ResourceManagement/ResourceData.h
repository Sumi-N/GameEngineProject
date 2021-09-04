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

	struct MeshPoint
	{
		Vec3f vertex;
		Vec3f normal;
		Vec2f uv;		
		Vec3f tangent;
		Vec3f bitangent;		
	};

	struct SkeletonMeshPoint : MeshPoint
	{
		SkeletonMeshPoint(): 
			padding(Vec2f(0, 0)),
			index(Vec4i(NUM_MAX_BONES - 1, NUM_MAX_BONES - 1, NUM_MAX_BONES - 1, NUM_MAX_BONES - 1)),
			weight(Vec4f(0, 0, 0, 0))
		{};

		Vec2f padding;
		Vec4i index;
		Vec4f weight;
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
		String      name;
		int          parent_index;
	};

	struct Skeleton
	{
		Array<Joint>   joints;
	};

	struct JointPose
	{
		Quaternionf rot;
		Vec4f       trans;
		Vec3f       scale;
		Mat4f       global_inversed_matrix;
		int         parent_index;
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
		Array<AnimationSample>       samples;
		bool                         do_looping;

		static Result Load(const char* i_filepath, AnimationClip& o_clip)
		{
			File in(i_filepath, File::Format::BinaryRead);

			RETURN_IFNOT_SUCCESS(in.Open())

			size_t num_samples;
			size_t num_joints;
			RETURN_IFNOT_SUCCESS(in.Read(static_cast<void*>(&num_samples), sizeof(size_t)));
			RETURN_IFNOT_SUCCESS(in.Read(static_cast<void*>(&num_joints), sizeof(size_t)));

			o_clip.samples.Resize(num_samples);

			for (int i = 0; i < num_samples; i++)
			{
				o_clip.samples[i].jointposes.Resize(num_joints);
				RETURN_IFNOT_SUCCESS(in.Read(static_cast<void*>(o_clip.samples[i].jointposes.Data()), num_joints * sizeof(size_t)));
			}

			in.Close();

			return ResultValue::Success;
		}
	};

	struct Mesh
	{
		Array<MeshPoint> data;
		Array<uint32_t> index;

		static Result Load(const char* i_filepath, Array<MeshPoint>& o_data, Array<uint32_t>& o_index)
		{				
			File in(i_filepath, File::Format::BinaryRead);

			RETURN_IFNOT_SUCCESS(in.Open())

			size_t data_size;
			size_t index_size;

			RETURN_IFNOT_SUCCESS(in.Read(&data_size, sizeof(size_t)))
			RETURN_IFNOT_SUCCESS(in.Read(&index_size, sizeof(size_t)))

			o_data.Resize(data_size);
			o_index.Resize(index_size);

			RETURN_IFNOT_SUCCESS(in.Read(o_data.Data(), data_size * sizeof(MeshPoint)))
			RETURN_IFNOT_SUCCESS(in.Read(o_index.Data(), index_size * sizeof(MeshPoint)))

			in.Close();

			return ResultValue::Success;
		}
	};

	struct SkeletonMesh
	{
		Array<SkeletonMeshPoint> data;
		Array<uint32_t> index;

		static Result Load(const char* i_filepath, Array<SkeletonMeshPoint>& o_data, Array<uint32_t>& o_index)
		{
			File in(i_filepath, File::Format::BinaryRead);

			RETURN_IFNOT_SUCCESS(in.Open())

			size_t data_size;
			size_t index_size;

			RETURN_IFNOT_SUCCESS(in.Read(&data_size, sizeof(size_t)))
			RETURN_IFNOT_SUCCESS(in.Read(&index_size, sizeof(size_t)))

			o_data.Resize(data_size);
			o_index.Resize(index_size);

			RETURN_IFNOT_SUCCESS(in.Read(o_data.Data(), data_size * sizeof(SkeletonMeshPoint)))
			RETURN_IFNOT_SUCCESS(in.Read(o_index.Data(), index_size * sizeof(MeshPoint)))

			in.Close();

			return ResultValue::Success;
		}
	};

	struct  Texture
	{
		Texture() = default;
		~Texture() = default;

		int width, height;
		Array<Vec3u8t> pixels;

		static Result Load(const char* i_filepath, size_t& o_width, size_t& o_height, Array<Vec3u8t>& o_pixels)
		{
			TextureType type;
			o_pixels.Clear();

			File in(i_filepath, File::Format::BinaryRead);

			RETURN_IFNOT_SUCCESS(in.Open());

			RETURN_IFNOT_SUCCESS(in.Read(&type, sizeof(uint8_t)));
			RETURN_IFNOT_SUCCESS(in.Read(&o_width, sizeof(int)));
			RETURN_IFNOT_SUCCESS(in.Read(&o_height, sizeof(int)));

			if (type == TextureType::SkyBox)
			{
				size_t fixed_size = sizeof(float) * 3 / sizeof(Vec3u8t);
				o_pixels.Resize(o_width * o_height * fixed_size);
				RETURN_IFNOT_SUCCESS(in.Read(o_pixels.Data(), sizeof(float) * o_width * o_height * static_cast<size_t>(3)));
			}
			else
			{
				o_pixels.Resize(o_width * o_height);
				RETURN_IFNOT_SUCCESS(in.Read(o_pixels.Data(), o_width * o_height * sizeof(Vec3u8t)));				
			}

			in.Close();
			DEBUG_PRINT("Succeed loading texture %s", i_filepath);

			return ResultValue::Success;
		}
	};
}