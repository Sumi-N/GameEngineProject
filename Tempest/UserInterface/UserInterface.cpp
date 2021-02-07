//#include "Define.h"
//#include "UserInterface.h"
//
//UserInterface::UserInterface()
//{
//}
//
//UserInterface::~UserInterface()
//{
//}
//
//void UserInterface::Init()
//{
//	ImGui::CreateContext();
//	ImGui::StyleColorsDark();
//
//	ImGuiIO& io = ImGui::GetIO();
//	io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
//	io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
//
//	io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
//	io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
//	io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
//	io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
//	io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
//	io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
//	io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
//	io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
//	io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
//	io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
//	io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
//	io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
//	io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
//	io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
//	io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
//	io.KeyMap[ImGuiKey_KeyPadEnter] = GLFW_KEY_KP_ENTER;
//	io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
//	io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
//	io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
//	io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
//	io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
//	io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;
//
//	ImGui_ImplOpenGL3_Init("#version 420");
//}
//
//void UserInterface::OnUpdate()
//{
//	ImGuiIO& io = ImGui::GetIO();
//	io.DisplaySize = ImVec2(SCREEN_WIDTH, SCREEN_HEIGHT);
//
//	ImGui_ImplOpenGL3_NewFrame();
//	ImGui::NewFrame();
//
//	static bool show = true;
//	ImGui::ShowDemoWindow(&show);
//
//	ImGui::Render();
//	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
//}
//
//void UserInterface::CleanUp()
//{
//	ImGui::DestroyContext();
//}
//
//void UserInterface::OnEvent(Event& e)
//{
//	EventDispatcher dispatcher(e);
//	dispatcher.Dispatch<MouseButtonPressedEvent>(std::bind(&UserInterface::OnMouseButtonPressedEvent, this, std::placeholders::_1));
//	dispatcher.Dispatch<MouseButtonReleasedEvent>(std::bind(&UserInterface::OnMouseButtonReleasedEvent, this, std::placeholders::_1));
//	dispatcher.Dispatch<MouseMovedEvent>(std::bind(&UserInterface::OnMouseMovedEvent, this, std::placeholders::_1));
//	dispatcher.Dispatch<KeyPressedEvent>(std::bind(&UserInterface::OnKeyPressedEvent, this, std::placeholders::_1));
//	dispatcher.Dispatch<KeyReleasedEvent>(std::bind(&UserInterface::OnKeyRelasedEvent, this, std::placeholders::_1));
//	dispatcher.Dispatch<WindowResizeEvent>(std::bind(&UserInterface::OnWindowResizedEvent, this, std::placeholders::_1));
//}
//
//bool UserInterface::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
//{
//	DEBUG_PRINT("I'm gui pressed");
//	ImGuiIO& io = ImGui::GetIO();
//	io.MouseDown[0] = true;
//	return false;
//}
//
//bool UserInterface::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
//{
//	return false;
//}
//
//bool UserInterface::OnMouseMovedEvent(MouseMovedEvent& e)
//{
//	ImGuiIO& io = ImGui::GetIO();
//	io.MousePos = ImVec2(0, 0);
//	return false;
//}
//
//bool UserInterface::OnKeyPressedEvent(KeyPressedEvent& e)
//{
//	return false;
//}
//
//bool UserInterface::OnKeyRelasedEvent(KeyReleasedEvent& e)
//{
//	return false;
//}
//
//bool UserInterface::OnWindowResizedEvent(WindowResizeEvent& e)
//{
//	return false;
//}
