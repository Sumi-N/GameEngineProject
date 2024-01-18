#pragma once

#include "Define.h"
#include "Format.h"

namespace Tempest
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
		Vec4f albedo{ 1.0f, 0.0f, 1.0, 1.0f };
		float roughness{ 1.0f };
		float metalic{ 0.0f };
	};

	struct Joint
	{
		Mat4f inversed{}; // inversed bind pose translation matrix
		Vec3f coord{};
		int   parent_index;
	};

	struct Skeleton
	{
		Array<Joint>   joints{};

		static Result Load(const char* i_filepath, Skeleton& o_skeleton)
		{
			File in(i_filepath, File::Format::BinaryRead);

			auto result = in.Open();
			if (result != ResultValue::Success)
			{
				in.SetFileName(PATH_SUFFIX_FROM_EXE + String(i_filepath));
				LOG::ConsolePrint("Failed to load skeleton: %s", i_filepath);
				RETURN_IFNOT_SUCCESS(in.Open());
			}

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

			auto result = in.Open();
			if (result != ResultValue::Success)
			{
				in.SetFileName(PATH_SUFFIX_FROM_EXE + String(i_filepath));
				LOG::ConsolePrint("Failed to load animation clip: %s", i_filepath);
				RETURN_IFNOT_SUCCESS(in.Open());
			}

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

			auto result = in.Open();
			if (result != ResultValue::Success)
			{
				in.SetFileName(PATH_SUFFIX_FROM_EXE + String(i_filepath));
				LOG::ConsolePrint("Failed to load mesh: %s", i_filepath);
				RETURN_IFNOT_SUCCESS(in.Open());
			}

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

			auto result = in.Open();
			if (result != ResultValue::Success)
			{
				in.SetFileName(PATH_SUFFIX_FROM_EXE + String(i_filepath));
				LOG::ConsolePrint("Failed to load skeleton mesh: %s", i_filepath);
				RETURN_IFNOT_SUCCESS(in.Open());
			}

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

	typedef uint32_t TextureInfoFlags;

	struct  TextureInfo
	{
		TextureInfo() = default;
		~TextureInfo() = default;

		uint32_t         width;
		uint32_t         height;
		uint32_t         count;
		uint32_t         mip_count;
		Array<char>      pixels;
		TextureFormat    format;
		TextureInfoFlags aspect_flag{};
		TextureInfoFlags usage_flag{};
		uint32_t         additional_flag{};
		bool             need_samper{false};
		bool             has_data{false};


		static Result Load(const char* i_filepath, TextureInfo& o_texture)
		{
			TextureType type;
			o_texture.pixels.Clear();

			File in(i_filepath, File::Format::BinaryRead);

			auto result = in.Open();
			if (result != ResultValue::Success)
			{
				in.SetFileName(PATH_SUFFIX_FROM_EXE + String(i_filepath));
				LOG::ConsolePrint("Failed to load texture: %s", i_filepath);
				RETURN_IFNOT_SUCCESS(in.Open());
			}

			RETURN_IFNOT_SUCCESS(in.Read(&type, sizeof(uint8_t)));
			RETURN_IFNOT_SUCCESS(in.Read(&o_texture.width, sizeof(uint32_t)));
			RETURN_IFNOT_SUCCESS(in.Read(&o_texture.height, sizeof(uint32_t)));

			if (type == TextureType::SkyBox)
			{
				o_texture.format = TextureFormat::R32G32B32_SFLOAT;
				o_texture.usage_flag |= TextureUsage::USAGE_TRANSFER_DST_BIT;
				o_texture.usage_flag |= TextureUsage::USAGE_SAMPLED_BIT;
			}
			else if(type < TextureType::Size)
			{
				o_texture.format = TextureFormat::R8G8B8A8_UNORM;
				o_texture.usage_flag |= TextureUsage::USAGE_TRANSFER_DST_BIT;
				o_texture.usage_flag |= TextureUsage::USAGE_SAMPLED_BIT;
			}
			else
			{
				DEBUG_ASSERT(false);
			}

			o_texture.has_data = true;
			o_texture.need_samper = true;
			o_texture.count = 1;
			o_texture.mip_count = 1;
			o_texture.aspect_flag |= TextureAspect::COLOR_BIT_ASPECT;
			size_t texture_size = o_texture.width * o_texture.height * GetTextureFormatSize(o_texture.format);
			o_texture.pixels.Resize(texture_size);
			RETURN_IFNOT_SUCCESS(in.Read(static_cast<void*>(o_texture.pixels.Data()), texture_size));

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
		char name[MAX_NAME_LENGTH];
	};

	struct  UniformInfo
	{
		int binding;
		size_t size;
		ShaderDescriptorType type;
		int stage;
		char name[MAX_NAME_LENGTH];
	};

	struct ShaderFile
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

	struct ShaderInfo
	{
		bool               shader_exist[static_cast<int>(ShaderType::Size)];
		size_t             shader_sizes[static_cast<int>(ShaderType::Size)];
		Array<char>        shader_binaries[static_cast<int>(ShaderType::Size)];
		Array<VertexInfo>  vertex_info;
		size_t             vertex_stride;
		Array<UniformInfo> uniform_infos[static_cast<int>(ShaderType::Size)];

		static Result Load(const char* i_filepath, ShaderInfo& o_shader)
		{
			File in(i_filepath, File::Format::BinaryRead);

			auto result = in.Open();
			if (result != ResultValue::Success)
			{
				in.SetFileName(PATH_SUFFIX_FROM_EXE + String(i_filepath));
				LOG::ConsolePrint("Failed to load shader: %s", i_filepath);
				RETURN_IFNOT_SUCCESS(in.Open());
			}

			ShaderFile shader_file;
			RETURN_IFNOT_SUCCESS(in.Read(static_cast<void*>(&shader_file), sizeof(ShaderFile)));

			for (int i = 0; i < static_cast<int>(ShaderType::Size); i++)
			{
				o_shader.shader_exist[i] = shader_file.shader_exist[i];
				o_shader.shader_sizes[i] = shader_file.shader_sizes[i];

				if(shader_file.shader_exist[i] == false)
					DEBUG_ASSERT(shader_file.shader_sizes[i] == 0);

				if (shader_file.shader_sizes[i] != 0)
				{
					o_shader.shader_binaries[i].Resize(shader_file.shader_sizes[i]);
					in.SetPosition(shader_file.shader_offsets[i]);
					RETURN_IFNOT_SUCCESS(in.Read(o_shader.shader_binaries[i].Data(), shader_file.shader_sizes[i]));
				}

				if (shader_file.uniform_sizes[i] != 0)
				{
					o_shader.uniform_infos[i].Resize(shader_file.uniform_sizes[i]);
					in.SetPosition(shader_file.uniform_offsets[i]);
					RETURN_IFNOT_SUCCESS(in.Read(o_shader.uniform_infos[i].Data(), shader_file.uniform_sizes[i] * sizeof(UniformInfo)));
				}

				if (i == static_cast<int>(ShaderType::Vertex) && shader_file.vertex_count != 0)
				{
					o_shader.vertex_stride = shader_file.vertex_stride;
					o_shader.vertex_info.Resize(shader_file.vertex_count);
					in.SetPosition(shader_file.vertex_info_offset);
					RETURN_IFNOT_SUCCESS(in.Read(o_shader.vertex_info.Data(), shader_file.vertex_count * sizeof(VertexInfo)));
				}
			}

			in.Close();

			return ResultValue::Success;
		}
	};
}