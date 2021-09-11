#pragma once

#include "Define.h"

using namespace Tempest;

enum class TextureType : int8_t
{
	Default          = 0,
	SkyBox           = 1,
	Albedo           = 2,
	Normal           = 3,
	Roughness        = 4,
	Metalic          = 5,
	AmbientOcclusion = 6,
	//-------------------------
	PB_Diffuse       = Albedo,
	PB_Specular      = Normal,
	PB_Normal        = Roughness,
	PB_Displacement  = Metalic,
	//--------------------------
	End,
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
		int         parent_index;
	};

	struct Skeleton
	{
		Array<Joint>   joints;

		static Result Load(const char* i_filepath, Skeleton& o_skeleton)
		{
			File in(i_filepath, File::Format::BinaryRead);

			RETURN_IFNOT_SUCCESS(in.Open())

			size_t num_joint;			
			RETURN_IFNOT_SUCCESS(in.Read(static_cast<void*>(&num_joint), sizeof(size_t)));

			o_skeleton.joints.Resize(num_joint);
			
			RETURN_IFNOT_SUCCESS(in.Read(static_cast<void*>(o_skeleton.joints.Data()), num_joint * sizeof(Joint)));			

			in.Close();

			return ResultValue::Success;
		}
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
		int frame_count;
		Array<AnimationSample> samples;

		static Result Load(const char* i_filepath, AnimationClip& o_clip)
		{
			File in(i_filepath, File::Format::BinaryRead);

			RETURN_IFNOT_SUCCESS(in.Open())

			size_t num_sample;
			size_t num_joint;
			RETURN_IFNOT_SUCCESS(in.Read(static_cast<void*>(&num_sample), sizeof(size_t)));
			RETURN_IFNOT_SUCCESS(in.Read(static_cast<void*>(&num_joint), sizeof(size_t)));

			o_clip.samples.Resize(num_sample);

			for (int i = 0; i < num_sample; i++)
			{
				o_clip.samples[i].jointposes.Resize(num_joint);
				RETURN_IFNOT_SUCCESS(in.Read(static_cast<void*>(o_clip.samples[i].jointposes.Data()), num_joint * sizeof(JointPose)));
			}

			in.Close();

			o_clip.frame_count = static_cast<int>(num_sample);

			return ResultValue::Success;
		}
	};

	struct Mesh
	{
		Array<MeshPoint> data;
		Array<uint32_t> index;

		static Result Load(const char* i_filepath, Mesh& o_mesh)
		{				
			File in(i_filepath, File::Format::BinaryRead);

			RETURN_IFNOT_SUCCESS(in.Open())

			size_t data_size;
			size_t index_size;

			RETURN_IFNOT_SUCCESS(in.Read(&data_size, sizeof(size_t)))
			RETURN_IFNOT_SUCCESS(in.Read(&index_size, sizeof(size_t)))

			o_mesh.data.Resize(data_size);
			o_mesh.index.Resize(index_size);

			RETURN_IFNOT_SUCCESS(in.Read(static_cast<void*>(o_mesh.data.Data()), data_size * sizeof(MeshPoint)))
			RETURN_IFNOT_SUCCESS(in.Read(static_cast<void*>(o_mesh.index.Data()), index_size * sizeof(MeshPoint)))

			in.Close();

			return ResultValue::Success;
		}
	};

	struct SkeletonMesh
	{
		Array<SkeletonMeshPoint> data;
		Array<uint32_t> index;

		static Result Load(const char* i_filepath, SkeletonMesh& o_smesh)
		{
			File in(i_filepath, File::Format::BinaryRead);

			RETURN_IFNOT_SUCCESS(in.Open())

			size_t data_size;
			size_t index_size;

			RETURN_IFNOT_SUCCESS(in.Read(&data_size, sizeof(size_t)))
			RETURN_IFNOT_SUCCESS(in.Read(&index_size, sizeof(size_t)))

			o_smesh.data.Resize(data_size);
			o_smesh.index.Resize(index_size);

			RETURN_IFNOT_SUCCESS(in.Read(static_cast<void*>(o_smesh.data.Data()), data_size * sizeof(SkeletonMeshPoint)))
			RETURN_IFNOT_SUCCESS(in.Read(static_cast<void*>(o_smesh.index.Data()), index_size * sizeof(MeshPoint)))

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

		static Result Load(const char* i_filepath, Texture& o_texture)
		{
			TextureType type;
			o_texture.pixels.Clear();

			File in(i_filepath, File::Format::BinaryRead);

			RETURN_IFNOT_SUCCESS(in.Open());

			RETURN_IFNOT_SUCCESS(in.Read(&type, sizeof(uint8_t)));
			RETURN_IFNOT_SUCCESS(in.Read(&o_texture.width, sizeof(int)));
			RETURN_IFNOT_SUCCESS(in.Read(&o_texture.height, sizeof(int)));

			if (type == TextureType::SkyBox)
			{
				size_t fixed_size = sizeof(float) * 3 / sizeof(Vec3u8t);
				o_texture.pixels.Resize(o_texture.width * o_texture.height * fixed_size);
				RETURN_IFNOT_SUCCESS(in.Read(static_cast<void*>(o_texture.pixels.Data()), sizeof(float) * o_texture.width * o_texture.height * static_cast<size_t>(3)));
			}
			else if(type < TextureType::End)
			{
				o_texture.pixels.Resize(o_texture.width * o_texture.height);
				RETURN_IFNOT_SUCCESS(in.Read(static_cast<void*>(o_texture.pixels.Data()), o_texture.width * o_texture.height * sizeof(Vec3u8t)));
			}
			else
			{
				DEBUG_ASSERT(false);
			}

			in.Close();
			DEBUG_PRINT("Succeed loading texture %s", i_filepath);

			return ResultValue::Success;
		}
	};
}