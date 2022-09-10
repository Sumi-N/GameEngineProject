#include "Pipeline.h"

namespace Tempest
{
	void Pipeline::Initialize(const Device& i_device, const SwapChain& i_swapchain, const Array<Resource::Shader>& shaders)
	{
		Array<VkPipelineShaderStageCreateInfo> shader_stages;
		shader_stages.Resize(shaders.Size());
		{
			for (int i = 0; i < shaders.Size(); i++)
			{
				VkShaderModuleCreateInfo shader_create_info{};
				shader_create_info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
				shader_create_info.codeSize = shaders[i].shader_size;
				shader_create_info.pCode = reinterpret_cast<const uint32_t*>(shaders[i].shader_binary.Data());
				if (vkCreateShaderModule(i_device.logical_device, &shader_create_info, nullptr, &shader_module[i]) != VK_SUCCESS)
				{
					DEBUG_ASSERT(false);
				}

				VkPipelineShaderStageCreateInfo shader_stage_info{};
				{
					shader_stage_info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
					switch (shaders[i].type)
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

				shader_stages[i] = shader_stage_info;
			}
		}

		VkPipelineVertexInputStateCreateInfo vertex_input_create_info{};
		vertex_input_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
		vertex_input_create_info.vertexBindingDescriptionCount = 0;
		vertex_input_create_info.pVertexBindingDescriptions = nullptr;
		vertex_input_create_info.vertexAttributeDescriptionCount = 0;
		vertex_input_create_info.pVertexAttributeDescriptions = nullptr;

		VkPipelineInputAssemblyStateCreateInfo input_assembly_create_info{};
		input_assembly_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		input_assembly_create_info.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		input_assembly_create_info.primitiveRestartEnable = VK_FALSE;

		VkViewport viewport;
		viewport.x = 0.0f;
		viewport.y = 0.0f;
		viewport.width = static_cast<float>(i_swapchain.support_details.extent.width);
		viewport.height = static_cast<float>(i_swapchain.support_details.extent.height);
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;

		VkRect2D scissor;
		scissor.offset = { 0, 0 };
		scissor.extent = i_swapchain.support_details.extent;

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
		rasterizer_create_info.cullMode = VK_CULL_MODE_BACK_BIT;
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
			pipeline_layout_create_info.setLayoutCount = 0;
			pipeline_layout_create_info.pSetLayouts = nullptr;
			pipeline_layout_create_info.pushConstantRangeCount = 0;
			pipeline_layout_create_info.pPushConstantRanges = nullptr;

			if (vkCreatePipelineLayout(i_device.logical_device, &pipeline_layout_create_info, nullptr, &pipeline_layout) != VK_SUCCESS)
			{
				DEBUG_ASSERT(false);
			}
		}

		VkAttachmentDescription color_attachment{};
		color_attachment.format = i_swapchain.support_details.formats[i_swapchain.support_details.available_format_index].format;
		color_attachment.samples = VK_SAMPLE_COUNT_1_BIT;
		color_attachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
		color_attachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
		color_attachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		color_attachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		color_attachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		color_attachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

		VkAttachmentReference color_attachment_ref{};
		color_attachment_ref.attachment = 0;
		color_attachment_ref.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

		VkSubpassDescription subpass{};
		subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
		subpass.colorAttachmentCount = 1;
		subpass.pColorAttachments = &color_attachment_ref;

		VkSubpassDependency dependency{};
		dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
		dependency.dstSubpass = 0;
		dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		dependency.srcAccessMask = 0;
		dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

		VkRenderPassCreateInfo renderpass_info{};
		renderpass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		renderpass_info.attachmentCount = 1;
		renderpass_info.pAttachments = &color_attachment;
		renderpass_info.subpassCount = 1;
		renderpass_info.pSubpasses = &subpass;
		renderpass_info.dependencyCount = 1;
		renderpass_info.pDependencies = &dependency;

		if (vkCreateRenderPass(i_device.logical_device, &renderpass_info, nullptr, &render_pass) != VK_SUCCESS)
		{
			DEBUG_ASSERT(false);
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
		pipeline_create_info.pDepthStencilState = nullptr;
		pipeline_create_info.pColorBlendState = &color_blend_create_info;
		pipeline_create_info.pDynamicState = nullptr;
		pipeline_create_info.layout = pipeline_layout;
		pipeline_create_info.renderPass = render_pass;
		pipeline_create_info.basePipelineHandle = VK_NULL_HANDLE;
		pipeline_create_info.basePipelineIndex = -1;

		if (vkCreateGraphicsPipelines(i_device.logical_device, VK_NULL_HANDLE, 1, &pipeline_create_info, nullptr, &graphics_pipeline) != VK_SUCCESS)
		{
			DEBUG_ASSERT(false);
		}
	}
}