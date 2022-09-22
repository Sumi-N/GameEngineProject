#include "Pipeline.h"

namespace Tempest
{
	void Pipeline::Init(const Device& i_device, const SwapChain& i_swapchain, const Shader& i_shader, const VertexBuffer& i_vertexbuffer, const UniformBuffer& i_uniforbuffer, const RenderPass& i_renderpass)
	{
		device = &i_device;

		Array<VkPipelineShaderStageCreateInfo> shader_stages;

		VkShaderModule shader_module[static_cast<int>(ShaderType::Size)];
		for (int i = 0; i < static_cast<int>(ShaderType::Size); i++)
		{
			if (!i_shader.shader_exist[i])
				continue;

			VkShaderModuleCreateInfo shader_create_info{};
			shader_create_info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
			shader_create_info.codeSize = i_shader.shader_sizes[i];
			shader_create_info.pCode = reinterpret_cast<const uint32_t*>(i_shader.shader_binaries[i].Data());
			if (vkCreateShaderModule(device->logical_device, &shader_create_info, nullptr, &shader_module[i]) != VK_SUCCESS)
			{
				DEBUG_ASSERT(false);
			}

			VkPipelineShaderStageCreateInfo shader_stage_info{};
			{
				shader_stage_info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
				switch (static_cast<ShaderType>(i))
				{
				case ShaderType::Vertex:
					shader_stage_info.stage = VK_SHADER_STAGE_VERTEX_BIT;
					break;
				case ShaderType::Control:
					shader_stage_info.stage = VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT;
					break;
				case ShaderType::Evaluation:
					shader_stage_info.stage = VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT;
					break;
				case ShaderType::Geometry:
					shader_stage_info.stage = VK_SHADER_STAGE_GEOMETRY_BIT;
					break;
				case ShaderType::Fragment:
					shader_stage_info.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
					break;
				case ShaderType::Compute:
					shader_stage_info.stage = VK_SHADER_STAGE_COMPUTE_BIT;
					break;
				default:
					DEBUG_ASSERT(false);
				}
				shader_stage_info.module = shader_module[i];
				shader_stage_info.pName = "main";
			}

			shader_stages.PushBack(shader_stage_info);
		}

		VkPipelineVertexInputStateCreateInfo vertex_input_create_info{};
		vertex_input_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
		vertex_input_create_info.vertexBindingDescriptionCount = 1;
		vertex_input_create_info.pVertexBindingDescriptions = &i_vertexbuffer.binding_description;
		vertex_input_create_info.vertexAttributeDescriptionCount = static_cast<uint32_t>(i_vertexbuffer.attribute_descriptions.Size());
		vertex_input_create_info.pVertexAttributeDescriptions = i_vertexbuffer.attribute_descriptions.Data();

		VkPipelineInputAssemblyStateCreateInfo input_assembly_create_info{};
		input_assembly_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		input_assembly_create_info.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		input_assembly_create_info.primitiveRestartEnable = VK_FALSE;

		VkViewport viewport;
		viewport.x = 0.0f;
		viewport.y = static_cast<float>(i_swapchain.height);
		viewport.width = static_cast<float>(i_swapchain.width);
		viewport.height = -1 * static_cast<float>(i_swapchain.height);
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;

		VkRect2D scissor;
		scissor.offset = { 0, 0 };
		scissor.extent = VkExtent2D{ i_swapchain.width, i_swapchain.height };

		VkPipelineViewportStateCreateInfo viewport_create_info{};
		viewport_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
		viewport_create_info.viewportCount = 1;
		viewport_create_info.pViewports = &viewport;
		viewport_create_info.scissorCount = 1;
		viewport_create_info.pScissors = &scissor;

		VkPipelineRasterizationStateCreateInfo rasterizer_create_info{};
		rasterizer_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		rasterizer_create_info.depthClampEnable = VK_FALSE;
		rasterizer_create_info.rasterizerDiscardEnable = VK_FALSE;
		rasterizer_create_info.polygonMode = VK_POLYGON_MODE_FILL;
		rasterizer_create_info.lineWidth = 1.0f;
		rasterizer_create_info.cullMode = VK_CULL_MODE_NONE;
		rasterizer_create_info.frontFace = VK_FRONT_FACE_CLOCKWISE;
		rasterizer_create_info.depthBiasEnable = VK_FALSE;
		rasterizer_create_info.depthBiasConstantFactor = 0.0f;
		rasterizer_create_info.depthBiasClamp = 0.0f;
		rasterizer_create_info.depthBiasSlopeFactor = 0.0f;

		VkPipelineMultisampleStateCreateInfo multisampling_create_info{};
		multisampling_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
		multisampling_create_info.sampleShadingEnable = VK_FALSE;
		multisampling_create_info.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
		multisampling_create_info.minSampleShading = 1.0f;
		multisampling_create_info.pSampleMask = nullptr;
		multisampling_create_info.alphaToCoverageEnable = VK_FALSE;
		multisampling_create_info.alphaToOneEnable = VK_FALSE;

		VkPipelineDepthStencilStateCreateInfo depth_stencil{};
		depth_stencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
		depth_stencil.depthTestEnable = VK_TRUE;
		depth_stencil.depthWriteEnable = VK_TRUE;
		depth_stencil.depthCompareOp = VK_COMPARE_OP_LESS;
		depth_stencil.depthBoundsTestEnable = VK_FALSE;
		depth_stencil.stencilTestEnable = VK_FALSE;
		depth_stencil.minDepthBounds = 0.0f;
		depth_stencil.maxDepthBounds = 1.0f;

		VkPipelineColorBlendAttachmentState color_blend_attachment{};
		color_blend_attachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
		color_blend_attachment.blendEnable = VK_FALSE;
		color_blend_attachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;
		color_blend_attachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
		color_blend_attachment.colorBlendOp = VK_BLEND_OP_ADD;
		color_blend_attachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
		color_blend_attachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
		color_blend_attachment.alphaBlendOp = VK_BLEND_OP_ADD;

		VkPipelineColorBlendStateCreateInfo color_blend_create_info{};
		color_blend_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
		color_blend_create_info.logicOpEnable = VK_FALSE;
		color_blend_create_info.logicOp = VK_LOGIC_OP_COPY;
		color_blend_create_info.attachmentCount = 1;
		color_blend_create_info.pAttachments = &color_blend_attachment;
		color_blend_create_info.blendConstants[0] = 0.0f;
		color_blend_create_info.blendConstants[1] = 0.0f;
		color_blend_create_info.blendConstants[2] = 0.0f;
		color_blend_create_info.blendConstants[3] = 0.0f;

		{
			VkPipelineLayoutCreateInfo pipeline_layout_create_info{};
			pipeline_layout_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
			pipeline_layout_create_info.setLayoutCount = 1;
			pipeline_layout_create_info.pSetLayouts = &i_uniforbuffer.GetDescriptorLayout();
			pipeline_layout_create_info.pushConstantRangeCount = 0;
			pipeline_layout_create_info.pPushConstantRanges = nullptr;

			auto create_pipeline_layout_result = vkCreatePipelineLayout(device->logical_device, &pipeline_layout_create_info, nullptr, &pipeline_layout);
			DEBUG_ASSERT(create_pipeline_layout_result == VK_SUCCESS);
		}

		VkGraphicsPipelineCreateInfo pipeline_create_info{};
		pipeline_create_info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
		pipeline_create_info.stageCount = static_cast<uint32_t>(shader_stages.Size());
		pipeline_create_info.pStages = shader_stages.Data();
		pipeline_create_info.pVertexInputState = &vertex_input_create_info;
		pipeline_create_info.pInputAssemblyState = &input_assembly_create_info;
		pipeline_create_info.pViewportState = &viewport_create_info;
		pipeline_create_info.pRasterizationState = &rasterizer_create_info;
		pipeline_create_info.pMultisampleState = &multisampling_create_info;
		pipeline_create_info.pDepthStencilState = &depth_stencil;
		pipeline_create_info.pColorBlendState = &color_blend_create_info;
		pipeline_create_info.pDynamicState = nullptr;
		pipeline_create_info.layout = pipeline_layout;
		pipeline_create_info.renderPass = i_renderpass.GetRenderPass();
		pipeline_create_info.subpass = 0;
		pipeline_create_info.basePipelineHandle = VK_NULL_HANDLE;
		pipeline_create_info.basePipelineIndex = -1;

		auto create_graphics_pipelines_result = vkCreateGraphicsPipelines(device->logical_device, VK_NULL_HANDLE, 1, &pipeline_create_info, nullptr, &graphics_pipeline);
		DEBUG_ASSERT(create_graphics_pipelines_result == VK_SUCCESS);
	}

	void Pipeline::CleanUp()
	{
		vkDestroyPipeline(device->logical_device, graphics_pipeline, nullptr);
		vkDestroyPipelineLayout(device->logical_device, pipeline_layout, nullptr);
	}
}