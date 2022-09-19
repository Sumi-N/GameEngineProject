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
		Uninitialized = 0,
		Vertex     = 1,
		Control    = 2,
		Evaluation = 3,
		Geometry   = 4,
		Fragment   = 5,
		Compute    = 6,
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

namespace Tempest { namespace Resource
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

	struct  Descriptor
	{
		int binding;
		size_t size;
		String name;
		ShaderDescriptorType type;
	};

	struct Shader
	{
		Shader() = default;
		~Shader() = default;

		ShaderType type;
		size_t shader_size;
		Array<char> shader_binary;
		Array<Descriptor> descriptor_info;

		static Result Load(const char* i_filepath, Shader& o_shader)
		{
			File in(i_filepath, File::Format::BinaryRead);

			RETURN_IFNOT_SUCCESS(in.Open());

			o_shader.shader_size = in.GetFileSize();
			o_shader.shader_binary.Resize(o_shader.shader_size);
			RETURN_IFNOT_SUCCESS(in.Read(static_cast<void*>(o_shader.shader_binary.Data()), o_shader.shader_size));

			in.Close();

			{
				SpvReflectShaderModule module = {};
				SpvReflectResult result = spvReflectCreateShaderModule(o_shader.shader_size, o_shader.shader_binary.Data(), &module);
				DEBUG_ASSERT(result == SPV_REFLECT_RESULT_SUCCESS);

				switch (module.shader_stage)
				{
				default: break;
				case SPV_REFLECT_SHADER_STAGE_VERTEX_BIT: o_shader.type = ShaderType::Vertex; break;
				case SPV_REFLECT_SHADER_STAGE_TESSELLATION_CONTROL_BIT: o_shader.type = ShaderType::Control; break;
				case SPV_REFLECT_SHADER_STAGE_TESSELLATION_EVALUATION_BIT: o_shader.type = ShaderType::Evaluation; break;
				case SPV_REFLECT_SHADER_STAGE_GEOMETRY_BIT: o_shader.type = ShaderType::Geometry; break;
				case SPV_REFLECT_SHADER_STAGE_FRAGMENT_BIT: o_shader.type = ShaderType::Fragment; break;
				case SPV_REFLECT_SHADER_STAGE_COMPUTE_BIT: o_shader.type = ShaderType::Compute; break;
				}

				{
					uint32_t count = 0;
					result = spvReflectEnumerateInputVariables(&module, &count, NULL);
					assert(result == SPV_REFLECT_RESULT_SUCCESS);

					Array<SpvReflectInterfaceVariable*> input_vars(count);
					result = spvReflectEnumerateInputVariables(&module, &count, input_vars.Data());
					assert(result == SPV_REFLECT_RESULT_SUCCESS);
				}

				{
					uint32_t count = 0;
					result = spvReflectEnumerateDescriptorSets(&module, &count, NULL);
					DEBUG_ASSERT(result == SPV_REFLECT_RESULT_SUCCESS);

					Array<SpvReflectDescriptorSet*> sets(count);
					result = spvReflectEnumerateDescriptorSets(&module, &count, sets.Data());
					DEBUG_ASSERT(result == SPV_REFLECT_RESULT_SUCCESS);

					for (size_t index = 0; index < sets.Size(); ++index)
					{
						auto p_set = sets[index];

						DEBUG_ASSERT(result == SPV_REFLECT_RESULT_SUCCESS);

						o_shader.descriptor_info.Resize(p_set->binding_count);

						for (uint32_t i = 0; i < p_set->binding_count; ++i)
						{
							const SpvReflectDescriptorBinding& binding_obj = *(p_set->bindings)[i];
							const SpvReflectBlockVariable& binding_obj_block = binding_obj.block;

							o_shader.descriptor_info[i].binding = binding_obj.binding;
							o_shader.descriptor_info[i].name = binding_obj.name;
							o_shader.descriptor_info[i].type = static_cast<ShaderDescriptorType>(binding_obj.descriptor_type);
							o_shader.descriptor_info[i].size = binding_obj_block.size;

							DEBUG_ASSERT(binding_obj.array.dims_count == 0);
							DEBUG_ASSERT(binding_obj.uav_counter_binding == nullptr);
							DEBUG_ASSERT((binding_obj.type_description->type_name != nullptr) && (strlen(binding_obj.type_description->type_name) > 0));
						}
					}
				}

				spvReflectDestroyShaderModule(&module);
			}

			return ResultValue::Success;
		}
	};
}}