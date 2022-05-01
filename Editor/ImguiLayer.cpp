#include "ImguiLayer.h"
#include "EntityInfo.h"
#include "Core/Math/Vector.h"

namespace Tempest
{
	namespace 
	{
		int IndexOfFocusedObject = -1;

		Vec3f SelectedObjectPosition;
		Vec3f SelectedObjectRotation;
		Vec3f SelectedObjectScale;
	}

	void ImguiLayer::OnAttach()
	{
		glfw_window = window->GetGLFWWindow();

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


		if (!glfw_window)
		{
			DEBUG_ASSERT(false);
		}

		// Setup Platform/Renderer backends
		ImGui_ImplGlfw_InitForOpenGL(glfw_window, true);
		ImGui_ImplOpenGL3_Init("#version 420");

		// Loading font
		io.Fonts->AddFontFromFileTTF(PATH_SUFFIX FONT_PATH "Karla-Regular.ttf", 25);
	}

	void ImguiLayer::OnDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImguiLayer::OnUpdate()
	{
		Begin();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		Docking();
		ViewportWindow();		
		AssetPanelWindow();
		LevelEditorPanelWindow();
		ControlPanelWindow();

		End();
	}

	void ImguiLayer::OnEvent(Event& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		//event.Handled |= event.GetCategory(EventCategory)
	}

	void ImguiLayer::Begin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImguiLayer::End()
	{
		ImGuiIO& io = ImGui::GetIO();		

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
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

	void ImguiLayer::ViewportWindow()
	{
		ImGui::Begin("Viewport");				
		ImVec2 imgui_viewport_panel_size = ImGui::GetContentRegionAvail();		
		ImGui::Image(reinterpret_cast<void*>(Graphic::FrameBufferImage.GetColorID()), imgui_viewport_panel_size, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

		if (ImGui::IsWindowFocused())
		{
			//DEBUG_PRINT("Hello");
		}

		ImGui::End();
	}

	void ImguiLayer::AssetPanelWindow()
	{
		ImGui::Begin("AssetPanel");
		ImGui::Text("This is setting panel");
		ImGui::End();
	}

	void ImguiLayer::ControlPanelWindow()
	{
		ImGui::Begin("ControlPanel");
		
		ImGuiTreeNodeFlags_ asset_panel_flags = ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_DefaultOpen;
		if (ImGui::CollapsingHeader("Basic Information", asset_panel_flags))
		{				
			float* position_data =reinterpret_cast<float*>(&SelectedObjectPosition);
			ImGui::Text("Position");
			ImGui::SameLine(100);
			ImGui::InputFloat3("", position_data);
			
			//float* rotation_data = reinterpret_cast<float*>(&SelectedObjectRotation);
			//ImGui::Text("Rotation");
			//ImGui::SameLine(100);
			//ImGui::InputFloat3("", rotation_data);
			//
			//float* scale_data = reinterpret_cast<float*>(&SelectedObjectScale);
			//ImGui::Text("Scale");
			//ImGui::SameLine(100);
			//ImGui::InputFloat3("", scale_data);
		}

		ImGui::End();
	}

	void ImguiLayer::LevelEditorPanelWindow()
	{
		ImGui::Begin("LevelEditorPanel");

		if (ImGui::TreeNode("Scene Hierarchy"))
		{
			static ImGuiTreeNodeFlags base_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;			
			static bool test_drag_and_drop = true;

			static int selection_mask = (1 << 0);

			int list_size = static_cast<int>(EntityInfo::GetTotalObjectSize());
			for (int i = 0; i < list_size; i++)
			{				
				ImGuiTreeNodeFlags node_flags = base_flags;
				const bool is_selected = (selection_mask & (1 << i)) != 0;
				if (is_selected)
					node_flags |= ImGuiTreeNodeFlags_Selected;
				
				String object_name = EntityInfo::GetObjectNameByIndex(i);
				bool node_open = ImGui::TreeNodeEx((void*)(intptr_t)i, node_flags, object_name.c_str(), i);
				if (ImGui::IsItemClicked()) 
				{
					IndexOfFocusedObject = i;
					SelectedObjectPosition = EntityInfo::GetObjectPositionByIndex(i);
					SelectedObjectRotation = EntityInfo::GetObjectRotationByIndex(i);
					SelectedObjectScale    = EntityInfo::GetObjectScaleByIndex(i);
				}
				if (test_drag_and_drop && ImGui::BeginDragDropSource())
				{
					ImGui::SetDragDropPayload("_TREENODE", NULL, 0);
					ImGui::Text("This is a drag and drop source");
					ImGui::EndDragDropSource();
				}
				if (node_open)
				{					
					ImGui::TreePop();
				}				
			}
			if (IndexOfFocusedObject != -1)
			{
				if (ImGui::GetIO().KeyCtrl)
					selection_mask ^= (1 << IndexOfFocusedObject);          // CTRL+click to toggle
				else 
					selection_mask = (1 << IndexOfFocusedObject);           // Click to single-select
			}
			ImGui::TreePop();
		}		

		ImGui::End();
	}

	void ImguiLayer::OnCriticalSection() 
	{

	}
}