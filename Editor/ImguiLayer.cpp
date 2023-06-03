#include "ImguiLayer.h"
#include "Serializer.h"

namespace Tempest
{
	Window* EditorWindow{};
	VkDescriptorPool DescriptorPool{};
	Device* g_pDevice;

	bool isEntityModifies{false};
	bool isObjectModified{false};
	int SelectedObjectIndex = -1;
	EntityInfo::ComponentFlags SelectingComponent = EntityInfo::ComponentFlags::None;
	EntityInfo::ComponentFlags SelectedObjectInfo = EntityInfo::ComponentFlags::None;
	Object SelectedObject{};
	CameraComponent SelectedCamera{};
	LightComponent SelectedLight{};
	MeshComponent SelectedMesh{};
	EffectComponent SelecctedEffect{};
	Observer<EffectComponent> SelectingDebugEffect{};

	extern EntityInfo::ComponentFlags SelectingComponent;
	extern Object SelectedObject;
	extern CameraComponent SelectedCamera;
	extern LightComponent SelectedLight;
	extern MeshComponent SelectedMesh;
	extern EffectComponent SelecctedEffect;
	extern Observer<EffectComponent> SelectingDebugEffect;

	Serializer SceneSerializer;

	static void check_vk_result(VkResult err)
	{
		if (err == 0)
			return;
		fprintf(stderr, "[Editor] [vulkan] Error: VkResult = %d\n", err);
		if (err < 0)
			abort();
	}

	void ImguiLayer::OnAttach()
	{
		EditorWindow = new Window();
		WindowProperty property;
		{
			property.title = "Editor Window";
			property.graphics_type = WindowProperty::GraphicsApiType::Vulkan;
		}
		EditorWindow->Init( property );

		//g_pDevice = const_cast<Device *>(&Framework::GetDevice());
		g_pDevice = &graphics_device;
		g_pDevice->Init(EditorWindow);

		ImGui_ImplVulkanH_Window* wd = &imgui_windows_data;
		SetupVulkanWindow(wd, g_pDevice->surface, EditorWindow->data.width, EditorWindow->data.height);

		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsClassic();

		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		// Setup Platform/Renderer backends
		glfw_window = EditorWindow->GetGLFWWindow();
		ImGui_ImplGlfw_InitForVulkan(glfw_window, true);
		ImGui_ImplVulkan_InitInfo init_info = {};
		{
			init_info.Instance = g_pDevice->instance;
			init_info.PhysicalDevice = g_pDevice->physical_device;
			init_info.Device = g_pDevice->logical_device;
			init_info.QueueFamily = g_pDevice->queue_family_index;
			init_info.Queue = g_pDevice->queue;
			init_info.PipelineCache = nullptr;
			// Create Descriptor Pool
			{
				VkDescriptorPoolSize pool_sizes[] =
				{
					{ VK_DESCRIPTOR_TYPE_SAMPLER, 1000 },
					{ VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1000 },
					{ VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, 1000 },
					{ VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 1000 },
					{ VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER, 1000 },
					{ VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER, 1000 },
					{ VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1000 },
					{ VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 1000 },
					{ VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 1000 },
					{ VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC, 1000 },
					{ VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT, 1000 }
				};
				VkDescriptorPoolCreateInfo pool_info = {};
				pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
				pool_info.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
				pool_info.maxSets = 1000 * IM_ARRAYSIZE(pool_sizes);
				pool_info.poolSizeCount = (uint32_t)IM_ARRAYSIZE(pool_sizes);
				pool_info.pPoolSizes = pool_sizes;
				auto result = vkCreateDescriptorPool(g_pDevice->logical_device, &pool_info, nullptr, &DescriptorPool);
				check_vk_result(result);
			}
			init_info.DescriptorPool = DescriptorPool;
			init_info.Allocator = nullptr;
			init_info.MinImageCount = wd->ImageCount;
			init_info.ImageCount = wd->ImageCount;
			init_info.CheckVkResultFn = check_vk_result;
		}
		ImGui_ImplVulkan_Init(&init_info, wd->RenderPass);

		// Loading font
		{
			//io.Fonts->AddFontFromFileTTF(PATH_SUFFIX FONT_PATH "Karla-Regular.ttf", 25);
			// Use any command queue
			VkCommandPool command_pool = wd->Frames[wd->FrameIndex].CommandPool;
			VkCommandBuffer command_buffer = wd->Frames[wd->FrameIndex].CommandBuffer;

			auto err = vkResetCommandPool(g_pDevice->logical_device, command_pool, 0);
			check_vk_result(err);
			VkCommandBufferBeginInfo begin_info = {};
			begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
			begin_info.flags |= VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
			err = vkBeginCommandBuffer(command_buffer, &begin_info);
			check_vk_result(err);

			ImGui_ImplVulkan_CreateFontsTexture(command_buffer);

			VkSubmitInfo end_info = {};
			end_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
			end_info.commandBufferCount = 1;
			end_info.pCommandBuffers = &command_buffer;
			err = vkEndCommandBuffer(command_buffer);
			check_vk_result(err);
			err = vkQueueSubmit(g_pDevice->queue, 1, &end_info, VK_NULL_HANDLE);
			check_vk_result(err);

			err = vkDeviceWaitIdle(g_pDevice->logical_device);
			check_vk_result(err);
			ImGui_ImplVulkan_DestroyFontUploadObjects();
		}

		OnAttach_ViewportPanel();
	}

	void ImguiLayer::OnDetach()
	{
		ImGui_ImplVulkan_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		delete EditorWindow;
	}

	void ImguiLayer::OnUpdate()
	{
		Begin();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		Docking();
		ViewportPanel();
		AssetPanel();
		SceneEditorPanel();
		ControlPanel();

		End();
	}

	void ImguiLayer::OnEvent(Event& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		//event.Handled |= event.GetCategory(EventCategory)
	}

	void ImguiLayer::Begin()
	{
		EditorWindow->SetContext();

		ImGui_ImplVulkan_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImguiLayer::End()
	{
		ImGuiIO& io = ImGui::GetIO();

		ImGui::Render();
		ImGui_ImplVulkanH_Window* wd = &imgui_windows_data;
		ImDrawData* main_draw_data = ImGui::GetDrawData();
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
		wd->ClearValue.color.float32[0] = clear_color.x * clear_color.w;
		wd->ClearValue.color.float32[1] = clear_color.y * clear_color.w;
		wd->ClearValue.color.float32[2] = clear_color.z * clear_color.w;
		wd->ClearValue.color.float32[3] = clear_color.w;
		FrameRender(wd, main_draw_data);

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}

		FramePresent(wd);
	}

	void ImguiLayer::Docking()
	{
		static bool opt_fullscreen = true;
		static bool opt_padding = false;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			const ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->WorkPos);
			ImGui::SetNextWindowSize(viewport->WorkSize);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}
		else
		{
			dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
		// and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		if (!opt_padding)
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		static bool show = true;
		ImGui::Begin("DockSpace Demo", &show, window_flags);
		if (!opt_padding)
			ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// Submit the DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}
		else
		{
			//ShowDockingDisabledMessage();
		}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Edit"))
			{
				if (ImGui::MenuItem("Save Scene", NULL))
				{
					SceneSerializer.Serialize("../Assets/Scene/test.tyml");
				}

				if (ImGui::MenuItem("Load Scene", NULL))
				{
					isEntityModifies = true;
				}

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Options"))
			{
				// Disabling fullscreen would allow the window to be moved to the front of other windows,
				// which we can't undo at the moment without finer window depth/z control.
				ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen);
				ImGui::MenuItem("Padding", NULL, &opt_padding);
				ImGui::Separator();

				if (ImGui::MenuItem("Flag: NoSplit", "", (dockspace_flags & ImGuiDockNodeFlags_NoSplit) != 0))
				{
					dockspace_flags ^= ImGuiDockNodeFlags_NoSplit;
				}
				if (ImGui::MenuItem("Flag: NoResize", "", (dockspace_flags & ImGuiDockNodeFlags_NoResize) != 0))
				{
					dockspace_flags ^= ImGuiDockNodeFlags_NoResize;
				}
				if (ImGui::MenuItem("Flag: NoDockingInCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_NoDockingInCentralNode) != 0))
				{
					dockspace_flags ^= ImGuiDockNodeFlags_NoDockingInCentralNode;
				}
				if (ImGui::MenuItem("Flag: AutoHideTabBar", "", (dockspace_flags & ImGuiDockNodeFlags_AutoHideTabBar) != 0))
				{
					dockspace_flags ^= ImGuiDockNodeFlags_AutoHideTabBar;
				}
				if (ImGui::MenuItem("Flag: PassthruCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) != 0, opt_fullscreen))
				{
					dockspace_flags ^= ImGuiDockNodeFlags_PassthruCentralNode;
				}
				ImGui::Separator();

				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		ImGui::End();
	}

	void ImguiLayer::OnCriticalSection()
	{
		OnCriticalSection_ViewportPanel();

		if (!isObjectModified && !isEntityModifies)
		{
			return;
		}

		if (isEntityModifies)
		{
			Entity::Reset();
			SceneSerializer.Deserialize("../Assets/int/scene/PBR_9Balls.tyml");
			//SceneSerializer.Deserialize("../Assets/int/scene/SkeletonAnimation.tyml");
			//SceneSerializer.Deserialize("../Assets/int/scene/Hexagon.tyml");
			GameThreadOnReset.ExecuteIfBound();
			RenderThreadOnReset.ExecuteIfBound();
			isEntityModifies = false;
		}

		switch (SelectingComponent)
		{
		case EntityInfo::ComponentFlags::ObjectFlag:
			*Entity::ObjectList[SelectedObjectIndex] = SelectedObject;
			break;
		case EntityInfo::ComponentFlags::CameraFlag:
			*Entity::CameraComponentList[SelectedObjectIndex] = SelectedCamera;
			break;
		case EntityInfo::ComponentFlags::LightFlag:
			*Entity::LightComponentList[SelectedObjectIndex] = SelectedLight;
			break;
		case EntityInfo::ComponentFlags::MeshFlag:
			*Entity::MeshComponentList[SelectedObjectIndex] = SelectedMesh;
			break;
		case EntityInfo::ComponentFlags::EffectFlag:
			*Entity::EffectComponentList[0] = SelecctedEffect;
			break;
		default:
			break;
		}

		if (SelectedObjectIndex != -1)
		{
			SelectingDebugEffect->is_enable = true;
		}

		isObjectModified = false;
	}

	void ImguiLayer::FrameRender(ImGui_ImplVulkanH_Window* wd, ImDrawData* draw_data)
	{
		VkResult err;

		VkSemaphore image_acquired_semaphore = wd->FrameSemaphores[wd->SemaphoreIndex].ImageAcquiredSemaphore;
		VkSemaphore render_complete_semaphore = wd->FrameSemaphores[wd->SemaphoreIndex].RenderCompleteSemaphore;
		err = vkAcquireNextImageKHR(g_pDevice->logical_device, wd->Swapchain, UINT64_MAX, image_acquired_semaphore, VK_NULL_HANDLE, &wd->FrameIndex);
		if (err == VK_ERROR_OUT_OF_DATE_KHR || err == VK_SUBOPTIMAL_KHR)
		{
			DEBUG_ASSERT(false);
			return;
		}
		check_vk_result(err);

		ImGui_ImplVulkanH_Frame* fd = &wd->Frames[wd->FrameIndex];
		{
			err = vkWaitForFences(g_pDevice->logical_device, 1, &fd->Fence, VK_TRUE, UINT64_MAX);    // wait indefinitely instead of periodically checking
			check_vk_result(err);

			err = vkResetFences(g_pDevice->logical_device, 1, &fd->Fence);
			check_vk_result(err);
		}
		{
			err = vkResetCommandPool(g_pDevice->logical_device, fd->CommandPool, 0);
			check_vk_result(err);
			VkCommandBufferBeginInfo info = {};
			info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
			info.flags |= VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
			err = vkBeginCommandBuffer(fd->CommandBuffer, &info);
			check_vk_result(err);
		}
		{
			VkRenderPassBeginInfo info = {};
			info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
			info.renderPass = wd->RenderPass;
			info.framebuffer = fd->Framebuffer;
			info.renderArea.extent.width = wd->Width;
			info.renderArea.extent.height = wd->Height;
			info.clearValueCount = 1;
			info.pClearValues = &wd->ClearValue;
			vkCmdBeginRenderPass(fd->CommandBuffer, &info, VK_SUBPASS_CONTENTS_INLINE);
		}

		// Record dear imgui primitives into command buffer
		ImGui_ImplVulkan_RenderDrawData(draw_data, fd->CommandBuffer);

		// Submit command buffer
		vkCmdEndRenderPass(fd->CommandBuffer);
		{
			VkPipelineStageFlags wait_stage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
			VkSubmitInfo info = {};
			info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
			info.waitSemaphoreCount = 1;
			info.pWaitSemaphores = &image_acquired_semaphore;
			info.pWaitDstStageMask = &wait_stage;
			info.commandBufferCount = 1;
			info.pCommandBuffers = &fd->CommandBuffer;
			info.signalSemaphoreCount = 1;
			info.pSignalSemaphores = &render_complete_semaphore;

			err = vkEndCommandBuffer(fd->CommandBuffer);
			check_vk_result(err);
			err = vkQueueSubmit(g_pDevice->queue, 1, &info, fd->Fence);
			check_vk_result(err);
		}
	}

	void ImguiLayer::FramePresent(ImGui_ImplVulkanH_Window* wd)
	{
		VkSemaphore render_complete_semaphore = wd->FrameSemaphores[wd->SemaphoreIndex].RenderCompleteSemaphore;
		VkPresentInfoKHR info = {};
		info.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
		info.waitSemaphoreCount = 1;
		info.pWaitSemaphores = &render_complete_semaphore;
		info.swapchainCount = 1;
		info.pSwapchains = &wd->Swapchain;
		info.pImageIndices = &wd->FrameIndex;
		VkResult err = vkQueuePresentKHR(g_pDevice->queue, &info);
		if (err == VK_ERROR_OUT_OF_DATE_KHR || err == VK_SUBOPTIMAL_KHR)
		{
			//g_SwapChainRebuild = true;
			return;
		}
		check_vk_result(err);
		wd->SemaphoreIndex = (wd->SemaphoreIndex + 1) % wd->ImageCount; // Now we can use the next set of semaphores
	}

	void ImguiLayer::SetupVulkanWindow(ImGui_ImplVulkanH_Window* wd, VkSurfaceKHR surface, int width, int height)
	{
		wd->Surface = surface;

		// Check for WSI support
		VkBool32 res;
		vkGetPhysicalDeviceSurfaceSupportKHR(g_pDevice->physical_device, g_pDevice->queue_family_index, wd->Surface, &res);
		if (res != VK_TRUE)
		{
			fprintf(stderr, "Error no WSI support on physical device 0\n");
			exit(-1);
		}

		// Select Surface Format
		const VkFormat requestSurfaceImageFormat[] = { VK_FORMAT_B8G8R8A8_UNORM, VK_FORMAT_R8G8B8A8_UNORM, VK_FORMAT_B8G8R8_UNORM, VK_FORMAT_R8G8B8_UNORM };
		const VkColorSpaceKHR requestSurfaceColorSpace = VK_COLORSPACE_SRGB_NONLINEAR_KHR;
		wd->SurfaceFormat = ImGui_ImplVulkanH_SelectSurfaceFormat(g_pDevice->physical_device, wd->Surface, requestSurfaceImageFormat, (size_t)IM_ARRAYSIZE(requestSurfaceImageFormat), requestSurfaceColorSpace);

		VkPresentModeKHR present_modes[] = { VK_PRESENT_MODE_FIFO_KHR };

		wd->PresentMode = ImGui_ImplVulkanH_SelectPresentMode(g_pDevice->physical_device, wd->Surface, &present_modes[0], IM_ARRAYSIZE(present_modes));
		//printf("[vulkan] Selected PresentMode = %d\n", wd->PresentMode);

		// Create SwapChain, RenderPass, Framebuffer, etc.
		ImGui_ImplVulkanH_CreateOrResizeWindow(g_pDevice->instance, g_pDevice->physical_device, g_pDevice->logical_device, wd, g_pDevice->queue_family_index, nullptr, width, height, 2);
	}
}