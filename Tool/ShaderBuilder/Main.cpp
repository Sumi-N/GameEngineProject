#include <Utility/File.h>
#include <ResourceManagement/ResourceData.h>
#include <shaderc/shaderc.h>
#include <External/SPIRV-Reflect/spirv_reflect.h>

#include <vulkan/vulkan.h>
// Returns the size in bytes of the provided VkFormat.
// As this is only intended for vertex attribute formats, not all VkFormats are supported.
static uint32_t FormatSize(VkFormat format)
{
	uint32_t result = 0;
	switch (format)
	{
	case VK_FORMAT_UNDEFINED: result = 0; break;
	case VK_FORMAT_R4G4_UNORM_PACK8: result = 1; break;
	case VK_FORMAT_R4G4B4A4_UNORM_PACK16: result = 2; break;
	case VK_FORMAT_B4G4R4A4_UNORM_PACK16: result = 2; break;
	case VK_FORMAT_R5G6B5_UNORM_PACK16: result = 2; break;
	case VK_FORMAT_B5G6R5_UNORM_PACK16: result = 2; break;
	case VK_FORMAT_R5G5B5A1_UNORM_PACK16: result = 2; break;
	case VK_FORMAT_B5G5R5A1_UNORM_PACK16: result = 2; break;
	case VK_FORMAT_A1R5G5B5_UNORM_PACK16: result = 2; break;
	case VK_FORMAT_R8_UNORM: result = 1; break;
	case VK_FORMAT_R8_SNORM: result = 1; break;
	case VK_FORMAT_R8_USCALED: result = 1; break;
	case VK_FORMAT_R8_SSCALED: result = 1; break;
	case VK_FORMAT_R8_UINT: result = 1; break;
	case VK_FORMAT_R8_SINT: result = 1; break;
	case VK_FORMAT_R8_SRGB: result = 1; break;
	case VK_FORMAT_R8G8_UNORM: result = 2; break;
	case VK_FORMAT_R8G8_SNORM: result = 2; break;
	case VK_FORMAT_R8G8_USCALED: result = 2; break;
	case VK_FORMAT_R8G8_SSCALED: result = 2; break;
	case VK_FORMAT_R8G8_UINT: result = 2; break;
	case VK_FORMAT_R8G8_SINT: result = 2; break;
	case VK_FORMAT_R8G8_SRGB: result = 2; break;
	case VK_FORMAT_R8G8B8_UNORM: result = 3; break;
	case VK_FORMAT_R8G8B8_SNORM: result = 3; break;
	case VK_FORMAT_R8G8B8_USCALED: result = 3; break;
	case VK_FORMAT_R8G8B8_SSCALED: result = 3; break;
	case VK_FORMAT_R8G8B8_UINT: result = 3; break;
	case VK_FORMAT_R8G8B8_SINT: result = 3; break;
	case VK_FORMAT_R8G8B8_SRGB: result = 3; break;
	case VK_FORMAT_B8G8R8_UNORM: result = 3; break;
	case VK_FORMAT_B8G8R8_SNORM: result = 3; break;
	case VK_FORMAT_B8G8R8_USCALED: result = 3; break;
	case VK_FORMAT_B8G8R8_SSCALED: result = 3; break;
	case VK_FORMAT_B8G8R8_UINT: result = 3; break;
	case VK_FORMAT_B8G8R8_SINT: result = 3; break;
	case VK_FORMAT_B8G8R8_SRGB: result = 3; break;
	case VK_FORMAT_R8G8B8A8_UNORM: result = 4; break;
	case VK_FORMAT_R8G8B8A8_SNORM: result = 4; break;
	case VK_FORMAT_R8G8B8A8_USCALED: result = 4; break;
	case VK_FORMAT_R8G8B8A8_SSCALED: result = 4; break;
	case VK_FORMAT_R8G8B8A8_UINT: result = 4; break;
	case VK_FORMAT_R8G8B8A8_SINT: result = 4; break;
	case VK_FORMAT_R8G8B8A8_SRGB: result = 4; break;
	case VK_FORMAT_B8G8R8A8_UNORM: result = 4; break;
	case VK_FORMAT_B8G8R8A8_SNORM: result = 4; break;
	case VK_FORMAT_B8G8R8A8_USCALED: result = 4; break;
	case VK_FORMAT_B8G8R8A8_SSCALED: result = 4; break;
	case VK_FORMAT_B8G8R8A8_UINT: result = 4; break;
	case VK_FORMAT_B8G8R8A8_SINT: result = 4; break;
	case VK_FORMAT_B8G8R8A8_SRGB: result = 4; break;
	case VK_FORMAT_A8B8G8R8_UNORM_PACK32: result = 4; break;
	case VK_FORMAT_A8B8G8R8_SNORM_PACK32: result = 4; break;
	case VK_FORMAT_A8B8G8R8_USCALED_PACK32: result = 4; break;
	case VK_FORMAT_A8B8G8R8_SSCALED_PACK32: result = 4; break;
	case VK_FORMAT_A8B8G8R8_UINT_PACK32: result = 4; break;
	case VK_FORMAT_A8B8G8R8_SINT_PACK32: result = 4; break;
	case VK_FORMAT_A8B8G8R8_SRGB_PACK32: result = 4; break;
	case VK_FORMAT_A2R10G10B10_UNORM_PACK32: result = 4; break;
	case VK_FORMAT_A2R10G10B10_SNORM_PACK32: result = 4; break;
	case VK_FORMAT_A2R10G10B10_USCALED_PACK32: result = 4; break;
	case VK_FORMAT_A2R10G10B10_SSCALED_PACK32: result = 4; break;
	case VK_FORMAT_A2R10G10B10_UINT_PACK32: result = 4; break;
	case VK_FORMAT_A2R10G10B10_SINT_PACK32: result = 4; break;
	case VK_FORMAT_A2B10G10R10_UNORM_PACK32: result = 4; break;
	case VK_FORMAT_A2B10G10R10_SNORM_PACK32: result = 4; break;
	case VK_FORMAT_A2B10G10R10_USCALED_PACK32: result = 4; break;
	case VK_FORMAT_A2B10G10R10_SSCALED_PACK32: result = 4; break;
	case VK_FORMAT_A2B10G10R10_UINT_PACK32: result = 4; break;
	case VK_FORMAT_A2B10G10R10_SINT_PACK32: result = 4; break;
	case VK_FORMAT_R16_UNORM: result = 2; break;
	case VK_FORMAT_R16_SNORM: result = 2; break;
	case VK_FORMAT_R16_USCALED: result = 2; break;
	case VK_FORMAT_R16_SSCALED: result = 2; break;
	case VK_FORMAT_R16_UINT: result = 2; break;
	case VK_FORMAT_R16_SINT: result = 2; break;
	case VK_FORMAT_R16_SFLOAT: result = 2; break;
	case VK_FORMAT_R16G16_UNORM: result = 4; break;
	case VK_FORMAT_R16G16_SNORM: result = 4; break;
	case VK_FORMAT_R16G16_USCALED: result = 4; break;
	case VK_FORMAT_R16G16_SSCALED: result = 4; break;
	case VK_FORMAT_R16G16_UINT: result = 4; break;
	case VK_FORMAT_R16G16_SINT: result = 4; break;
	case VK_FORMAT_R16G16_SFLOAT: result = 4; break;
	case VK_FORMAT_R16G16B16_UNORM: result = 6; break;
	case VK_FORMAT_R16G16B16_SNORM: result = 6; break;
	case VK_FORMAT_R16G16B16_USCALED: result = 6; break;
	case VK_FORMAT_R16G16B16_SSCALED: result = 6; break;
	case VK_FORMAT_R16G16B16_UINT: result = 6; break;
	case VK_FORMAT_R16G16B16_SINT: result = 6; break;
	case VK_FORMAT_R16G16B16_SFLOAT: result = 6; break;
	case VK_FORMAT_R16G16B16A16_UNORM: result = 8; break;
	case VK_FORMAT_R16G16B16A16_SNORM: result = 8; break;
	case VK_FORMAT_R16G16B16A16_USCALED: result = 8; break;
	case VK_FORMAT_R16G16B16A16_SSCALED: result = 8; break;
	case VK_FORMAT_R16G16B16A16_UINT: result = 8; break;
	case VK_FORMAT_R16G16B16A16_SINT: result = 8; break;
	case VK_FORMAT_R16G16B16A16_SFLOAT: result = 8; break;
	case VK_FORMAT_R32_UINT: result = 4; break;
	case VK_FORMAT_R32_SINT: result = 4; break;
	case VK_FORMAT_R32_SFLOAT: result = 4; break;
	case VK_FORMAT_R32G32_UINT: result = 8; break;
	case VK_FORMAT_R32G32_SINT: result = 8; break;
	case VK_FORMAT_R32G32_SFLOAT: result = 8; break;
	case VK_FORMAT_R32G32B32_UINT: result = 12; break;
	case VK_FORMAT_R32G32B32_SINT: result = 12; break;
	case VK_FORMAT_R32G32B32_SFLOAT: result = 12; break;
	case VK_FORMAT_R32G32B32A32_UINT: result = 16; break;
	case VK_FORMAT_R32G32B32A32_SINT: result = 16; break;
	case VK_FORMAT_R32G32B32A32_SFLOAT: result = 16; break;
	case VK_FORMAT_R64_UINT: result = 8; break;
	case VK_FORMAT_R64_SINT: result = 8; break;
	case VK_FORMAT_R64_SFLOAT: result = 8; break;
	case VK_FORMAT_R64G64_UINT: result = 16; break;
	case VK_FORMAT_R64G64_SINT: result = 16; break;
	case VK_FORMAT_R64G64_SFLOAT: result = 16; break;
	case VK_FORMAT_R64G64B64_UINT: result = 24; break;
	case VK_FORMAT_R64G64B64_SINT: result = 24; break;
	case VK_FORMAT_R64G64B64_SFLOAT: result = 24; break;
	case VK_FORMAT_R64G64B64A64_UINT: result = 32; break;
	case VK_FORMAT_R64G64B64A64_SINT: result = 32; break;
	case VK_FORMAT_R64G64B64A64_SFLOAT: result = 32; break;
	case VK_FORMAT_B10G11R11_UFLOAT_PACK32: result = 4; break;
	case VK_FORMAT_E5B9G9R9_UFLOAT_PACK32: result = 4; break;

	default:
		break;
	}
	return result;
}

using namespace Tempest;

Result ConvertShaders(String output_file_name, String* i_file_names)
{
	// Initialize compiler
	shaderc_compiler_t compiler = shaderc_compiler_initialize();

	// Open the destination file
	String output_name = output_file_name;
	String output_path = "..\\..\\" BIN_SHADER_PATH + output_name + ".ts";
	File out(output_path, File::Format::BinaryWrite);
	RETURN_IFNOT_SUCCESS(out.Open());

	// Shader info struct
	ShaderInfo shader_info{};
	RETURN_IFNOT_SUCCESS(out.Write(reinterpret_cast<void*>(&shader_info), sizeof(ShaderInfo)));
	size_t shader_info_current_offset = sizeof(ShaderInfo);

	// Iterate through shaders
	for (int idx_type = 0; idx_type < static_cast<int>(ShaderType::Size); idx_type++)
	{
		String output_name_with_shadertyp = File::RemoveExtension(File::GetFileName(i_file_names[idx_type]));

		// Skip the process if the shader type doesn't exist
		if (i_file_names[idx_type].empty())
			continue;

		// Open the source file
		File in(i_file_names[idx_type], File::Format::Read);
		RETURN_IFNOT_SUCCESS(in.Open());
		String shader_text = in.GetText();
		in.Close();

		auto GetCompilerShaderType = [](int i)
		{
			switch (i){
			case 0:
				return shaderc_vertex_shader;
			case 1:
				return shaderc_tess_control_shader;
			case 2:
				return shaderc_tess_evaluation_shader;
			case 3:
				return shaderc_geometry_shader;
			case 4:
				return shaderc_fragment_shader;
			case 5:
				return shaderc_compute_shader;
			default:
				DEBUG_ASSERT(false);}
			return shaderc_vertex_shader;
		};

		shaderc_compilation_result_t compile_result = shaderc_compile_into_spv(
			compiler, shader_text.c_str(), shader_text.size(),
			GetCompilerShaderType(idx_type), output_name_with_shadertyp.c_str(), "main", nullptr);

		size_t num_errors = shaderc_result_get_num_errors(compile_result);
		size_t num_warnings = shaderc_result_get_num_warnings(compile_result);
		if(num_errors != 0 || num_warnings != 0)
			DEBUG_PRINT("\n%s", shaderc_result_get_error_message(compile_result));
		DEBUG_ASSERT(num_errors == 0);
		DEBUG_ASSERT(num_warnings == 0);

		// Get reflection data
		{
			size_t shader_size = shaderc_result_get_length(compile_result);
			const char* shader_binary = shaderc_result_get_bytes(compile_result);

			SpvReflectShaderModule module = {};
			SpvReflectResult reflection_result = spvReflectCreateShaderModule(shader_size, shader_binary, &module);
			DEBUG_ASSERT(reflection_result == SPV_REFLECT_RESULT_SUCCESS);

			// Set vertex data
			if (idx_type == static_cast<int>(ShaderType::Vertex))
			{
				uint32_t vertex_count = 0;
				SpvReflectResult result = spvReflectEnumerateInputVariables(&module, &vertex_count, NULL);
				DEBUG_ASSERT(result == SPV_REFLECT_RESULT_SUCCESS);

				std::vector<VertexInfo> vertex_infos(vertex_count);
				std::vector<SpvReflectInterfaceVariable*> input_vars(vertex_count);
				result = spvReflectEnumerateInputVariables(&module, &vertex_count, input_vars.data());
				DEBUG_ASSERT(result == SPV_REFLECT_RESULT_SUCCESS);

				for (int i = 0; i < input_vars.size(); i++)
				{
					const SpvReflectInterfaceVariable& refl_var = *(input_vars[i]);
					if (refl_var.decoration_flags & SPV_REFLECT_DECORATION_BUILT_IN)
					{
						vertex_count--;
						continue;
					}

					vertex_infos[i].location = refl_var.location;
					vertex_infos[i].binding = 0;
					vertex_infos[i].format = static_cast<int>(refl_var.format);
					vertex_infos[i].offset = 0;
				}

				std::sort(std::begin(vertex_infos), std::end(vertex_infos),
							[](const VertexInfo& a, const VertexInfo& b)
							{
								return a.location < b.location;
							});
				int stride = 0;
				for (auto& vertex_info : vertex_infos)
				{
					uint32_t format_size = FormatSize(static_cast<VkFormat>(vertex_info.format));
					vertex_info.offset = stride;
					stride += format_size;
				}

				shader_info.vertex_count = vertex_count;
				shader_info.vertex_stride = stride;
				shader_info.vertex_info_offset = shader_info_current_offset;

				RETURN_IFNOT_SUCCESS(out.Write(vertex_infos.data(), vertex_count * sizeof(VertexInfo)));

				shader_info_current_offset += vertex_count * sizeof(VertexInfo);
			}

			// Set uniform data
			{
				uint32_t uniform_count = 0;
				SpvReflectResult result = spvReflectEnumerateDescriptorSets(&module, &uniform_count, NULL);
				DEBUG_ASSERT(result == SPV_REFLECT_RESULT_SUCCESS);

				Array<SpvReflectDescriptorSet*> sets(uniform_count);
				result = spvReflectEnumerateDescriptorSets(&module, &uniform_count, sets.Data());
				DEBUG_ASSERT(result == SPV_REFLECT_RESULT_SUCCESS);

				Array<UniformInfo> uniform_infos;
				for (size_t index = 0; index < sets.Size(); ++index)
				{
					DEBUG_ASSERT(index == 0);

					auto p_set = sets[index];
					uniform_infos.Resize(p_set->binding_count);
					for (uint32_t i = 0; i < p_set->binding_count; ++i)
					{
						const SpvReflectDescriptorBinding& binding_obj = *(p_set->bindings)[i];
						const SpvReflectBlockVariable& binding_obj_block = binding_obj.block;

						uniform_infos[i].binding = binding_obj.binding;
						//uniform_infos[i].name = binding_obj.name;
						uniform_infos[i].type = static_cast<ShaderDescriptorType>(binding_obj.descriptor_type);
						uniform_infos[i].stage = static_cast<int>(module.shader_stage);
						uniform_infos[i].size = binding_obj_block.size;

						DEBUG_ASSERT(binding_obj.array.dims_count == 0);
						DEBUG_ASSERT(binding_obj.uav_counter_binding == nullptr);
						//DEBUG_ASSERT((binding_obj.type_description->type_name != nullptr) && (strlen(binding_obj.type_description->type_name) > 0));
					}
				}

				shader_info.uniform_sizes[idx_type] = uniform_infos.Size();
				shader_info.uniform_offsets[idx_type] = shader_info_current_offset;

				RETURN_IFNOT_SUCCESS(out.Write(uniform_infos.Data(), uniform_infos.Size() * sizeof(UniformInfo)));

				shader_info_current_offset += uniform_infos.Size() * sizeof(UniformInfo);
			}

			// Set shader binary
			{
				size_t shader_size = shaderc_result_get_length(compile_result);
				const char* shader_binary = shaderc_result_get_bytes(compile_result);

				shader_info.shader_exist[idx_type] = true;
				shader_info.shader_sizes[idx_type] = shader_size;
				shader_info.shader_offsets[idx_type] = shader_info_current_offset;

				RETURN_IFNOT_SUCCESS(out.Write((void*)(shader_binary), shader_size));

				shader_info_current_offset += shader_size;
			}

			spvReflectDestroyShaderModule(&module);

			shaderc_result_release(compile_result);
		}
	}

	out.SetPosition(0);
	RETURN_IFNOT_SUCCESS(out.Write(reinterpret_cast<void*>(&shader_info), sizeof(ShaderInfo)));

	// Close the destination file
	out.Close();

	shaderc_compiler_release(compiler);

	return ResultValue::Success;
}

const String path_in = INT_SHADER_PATH;

int main()
{
    String directory = "..\\..\\" + path_in;

	String basic_paths[] = {
		directory + "debug_purpose\\basic.vert.glsl", "", "", "",
		directory + "debug_purpose\\basic.frag.glsl", ""
	};

	String outlinehighlight_paths[] = {
		directory + "debug_purpose\\outlinehighlight.vert.glsl", "", "", "",
		directory + "debug_purpose\\outlinehighlight.frag.glsl", ""
	};

	String albedomodel_paths[] = {
		directory + "debug_purpose\\albedomodel.vert.glsl", "", "", "",
		directory + "debug_purpose\\albedomodel.frag.glsl", ""
	};

	String specular_ibl[] = {
		directory + "image_base_rendering\\specular_ibl.vert.glsl", "", "", "",
		directory + "image_base_rendering\\specular_ibl.frag.glsl", ""
	};

	String equirectangular_to_cube_mapping[] = {
	directory + "image_base_rendering\\equirectangular_to_cube_mapping.vert.glsl", "", "",
	directory + "image_base_rendering\\equirectangular_to_cube_mapping.geo.glsl",
	directory + "image_base_rendering\\equirectangular_to_cube_mapping.frag.glsl", ""
	};

	String cubemap_diffuse_convolution[] = {
	directory + "image_base_rendering\\equirectangular_to_cube_mapping.vert.glsl", "", "",
	directory + "image_base_rendering\\equirectangular_to_cube_mapping.geo.glsl",
	directory + "image_base_rendering\\cubemap_diffuse_convolution.frag.glsl", ""
	};

	String cubemap_specular_convolution[] = {
	directory + "image_base_rendering\\equirectangular_to_cube_mapping.vert.glsl", "", "",
	directory + "image_base_rendering\\equirectangular_to_cube_mapping.geo.glsl",
	directory + "image_base_rendering\\cubemap_specular_convolution.frag.glsl", ""
	};

	String skybox[] = {
	directory + "skybox\\skybox.vert.glsl", "", "", "",
	directory + "skybox\\skybox.frag.glsl", ""
	};

	auto result = ConvertShaders("cubemap_diffuse_convolution", cubemap_diffuse_convolution);

	DEBUG_ASSERT(result == ResultValue::Success);

	return 0;
}