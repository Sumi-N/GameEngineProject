#pragma once

#include "Define.h"

namespace Tempest
{
	enum class LightType : uint8_t
	{
		Uninitialized = 0,
		AmbientLight = 1,
		PointLight = 2,
		DirectionalLight = 3,
		Size,
	};

	enum class TextureType : uint8_t
	{
		Default = 0,
		SkyBox = 1,
		Albedo = 2,
		Normal = 3,
		Roughness = 4,
		Metalic = 5,
		AmbientOcclusion = 6,
		Size,
	};

	enum class MeshType : uint8_t
	{
		Mesh = 0,
		SkeletonMesh = 1,
		Size,
	};

	enum class ShaderType : uint8_t
	{
		Vertex     = 0,
		Control    = 1,
		Evaluation = 2,
		Geometry   = 3,
		Fragment   = 4,
		Compute    = 5,
		Size,
	};

	enum class ShaderDescriptorType : uint8_t
	{
		Sampler,
		CombinedImageSampler,
		SapmledImage,
		StorageImage,
		UniformTexelBuffer,
		StorageTexelBuffer,
		UniformBuffer,
		StorageBuffer,
		Size,
	};
}

namespace Tempest
{
	using namespace Tempest;

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
		Vec4f albedo{ 1.0f, 0.0f, 1.0, 1.0f };
		float roughness{ 1.0f };
		float metalic{ 0.0f };
	};

	struct Joint
	{
		Mat4f       inversed{}; // inversed bind pose translation matrix
		Vec3f       coord{};
		int         parent_index;
	};

	struct Skeleton
	{
		Array<Joint>   joints{};

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
		Array<JointPose> jointposes{};
	};

	struct AnimationClip
	{
		int frame_count;
		Array<AnimationSample> samples{};

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
		Array<MeshPoint> data{};
		Array<uint32_t> index{};

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
		Array<SkeletonMeshPoint> data{};
		Array<uint32_t> index{};

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
			else if(type < TextureType::Size)
			{
				o_texture.pixels.Resize(o_texture.width * o_texture.height);
				RETURN_IFNOT_SUCCESS(in.Read(static_cast<void*>(o_texture.pixels.Data()), o_texture.width * o_texture.height * sizeof(Vec3u8t)));
			}
			else
			{
				DEBUG_ASSERT(false);
			}

			in.Close();

			return ResultValue::Success;
		}
	};

	struct VertexInfo
	{
		int location;
		int binding;
		int format;
		int offset;
	};

	struct  UniformInfo
	{
		int binding;
		size_t size;
		String name;
		ShaderDescriptorType type;
		int stage;
	};

	struct ShaderInfo
	{
		bool   shader_exist   [static_cast<int>(ShaderType::Size)];
		size_t shader_sizes   [static_cast<int>(ShaderType::Size)];
		size_t shader_offsets [static_cast<int>(ShaderType::Size)];
		size_t vertex_count;
		size_t vertex_info_offset;
		size_t vertex_stride;
		size_t uniform_sizes  [static_cast<int>(ShaderType::Size)];
		size_t uniform_offsets[static_cast<int>(ShaderType::Size)];
	};

	struct Shader
	{
		bool   shader_exist[static_cast<int>(ShaderType::Size)];
		size_t shader_sizes[static_cast<int>(ShaderType::Size)];
		Array<char> shader_binaries[static_cast<int>(ShaderType::Size)];
		Array<VertexInfo> vertex_info;
		size_t vertex_stride;
		Array<UniformInfo> uniform_infos[static_cast<int>(ShaderType::Size)];

		static Result Load(const char* i_filepath, Shader& o_shader)
		{
			File in(i_filepath, File::Format::BinaryRead);

			RETURN_IFNOT_SUCCESS(in.Open());

			ShaderInfo shader_info;
			RETURN_IFNOT_SUCCESS(in.Read(static_cast<void*>(&shader_info), sizeof(ShaderInfo)));

			for (int i = 0; i < static_cast<int>(ShaderType::Size); i++)
			{
				o_shader.shader_exist[i] = shader_info.shader_exist[i];
				o_shader.shader_sizes[i] = shader_info.shader_sizes[i];

				if(shader_info.shader_exist[i] == false)
					DEBUG_ASSERT(shader_info.shader_sizes[i] == 0);

				if (shader_info.shader_sizes[i] != 0)
				{
					o_shader.shader_binaries[i].Resize(shader_info.shader_sizes[i]);
					in.SetPosition(shader_info.shader_offsets[i]);
					RETURN_IFNOT_SUCCESS(in.Read(o_shader.shader_binaries[i].Data(), shader_info.shader_sizes[i]));
				}

				if (shader_info.uniform_sizes[i] != 0)
				{
					o_shader.uniform_infos[i].Resize(shader_info.uniform_sizes[i]);
					in.SetPosition(shader_info.uniform_offsets[i]);
					RETURN_IFNOT_SUCCESS(in.Read(o_shader.uniform_infos[i].Data(), shader_info.uniform_sizes[i] * sizeof(UniformInfo)));
				}

				if (i == static_cast<int>(ShaderType::Vertex) && shader_info.vertex_count != 0)
				{
					o_shader.vertex_stride = shader_info.vertex_stride;
					o_shader.vertex_info.Resize(shader_info.vertex_count);
					in.SetPosition(shader_info.vertex_info_offset);
					RETURN_IFNOT_SUCCESS(in.Read(o_shader.vertex_info.Data(), shader_info.vertex_count * sizeof(VertexInfo)));
				}
			}

			in.Close();

			return ResultValue::Success;
		}
	};
}