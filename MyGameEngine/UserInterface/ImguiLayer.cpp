#include "ImguiLayer.h"
#include <inttypes.h>

#include <iostream>
#include <string>

ImguiLayer::ImguiLayer()
	:Layer()
{

}

ImguiLayer::~ImguiLayer()
{

}

void ImguiLayer::OnAttach()
{
	FBXImporter fbx;
	fbx.Import(PATH_SUFFIX MESH_PATH "gunhand.fbx");
	this->g_scene = fbx.GetScene();

	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGuiIO& io = ImGui::GetIO();
	io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
	io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

	io.DisplaySize = ImVec2(SCREEN_WIDTH, SCREEN_HEIGHT);

	io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
	io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
	io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
	io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
	io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
	io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
	io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
	io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
	io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
	io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
	io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
	io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
	io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
	io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
	io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
	io.KeyMap[ImGuiKey_KeyPadEnter] = GLFW_KEY_KP_ENTER;
	io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
	io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
	io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
	io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
	io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
	io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

	ImGui_ImplOpenGL3_Init("#version 420");
}

void ImguiLayer::OnDetach()
{
	ImGui::DestroyContext();
}

void ImguiLayer::OnUpdate()
{
	ImGuiIO& io = ImGui::GetIO();

	ImGui_ImplOpenGL3_NewFrame();
	//ImGui::NewFrame();

	//static bool show = true;
	//ImGui::ShowDemoWindow(&show);

	//ImGui::Render();

	onGUI();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImguiLayer::OnEvent(Event& event)
{
	EventDispatcher dispatcher(event);
	dispatcher.Dispatch<MouseButtonPressedEvent>(std::bind(&ImguiLayer::OnMouseButtonPressedEvent, this, std::placeholders::_1));
	dispatcher.Dispatch<MouseButtonReleasedEvent>(std::bind(&ImguiLayer::OnMouseButtonReleasedEvent, this, std::placeholders::_1));
	dispatcher.Dispatch<MouseMovedEvent>(std::bind(&ImguiLayer::OnMouseMovedEvent, this, std::placeholders::_1));
	dispatcher.Dispatch<KeyPressedEvent>(std::bind(&ImguiLayer::OnKeyPressedEvent, this, std::placeholders::_1));
	dispatcher.Dispatch<KeyReleasedEvent>(std::bind(&ImguiLayer::OnKeyRelasedEvent, this, std::placeholders::_1));
	dispatcher.Dispatch<WindowResizeEvent>(std::bind(&ImguiLayer::OnWindowResizedEvent, this, std::placeholders::_1));
}

bool ImguiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
{
	ImGuiIO& io = ImGui::GetIO();
	io.MouseDown[static_cast<uint8_t>(e.GetMouseButton())] = true;
	return true;
}

bool ImguiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
{
	ImGuiIO& io = ImGui::GetIO();
	io.MouseDown[static_cast<uint8_t>(e.GetMouseButton())] = false;
	return true;
}

bool ImguiLayer::OnMouseMovedEvent(MouseMovedEvent& e)
{
	ImGuiIO& io = ImGui::GetIO();
	io.MousePos = ImVec2(e.GetX(), e.GetY());
	return true;
}

bool ImguiLayer::OnKeyPressedEvent(KeyPressedEvent& e)
{
	ImGuiIO& io = ImGui::GetIO();
	io.MouseDown[static_cast<uint8_t>(e.GetButton())] = true;
	io.AddInputCharacter(static_cast<unsigned short>(e.GetButton()));
	return true;
}

bool ImguiLayer::OnKeyRelasedEvent(KeyReleasedEvent& e)
{
	ImGuiIO& io = ImGui::GetIO();
	io.MouseDown[static_cast<uint8_t>(e.GetButton())] = false;
	return true;
}

bool ImguiLayer::OnWindowResizedEvent(WindowResizeEvent& e)
{
	ImGuiIO& io = ImGui::GetIO();
	io.DisplaySize = ImVec2(static_cast<float>(e.GetWidth()), static_cast<float>(e.GetHeight()));
	io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
	return true;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////

void ImguiLayer::onGUI()
{

	auto& io = ImGui::GetIO();
	io.KeyShift = (GetKeyState(VK_SHIFT) & 0x8000) != 0;
	io.KeyCtrl = (GetKeyState(VK_CONTROL) & 0x8000) != 0;
	io.KeyCtrl = (GetKeyState(VK_MENU) & 0x8000) != 0;

	ImGui::NewFrame();

	if (g_scene)
	{
		//		ImGui::RootDock(ImVec2(0, 0), ImGui::GetIO().DisplaySize);
		if (ImGui::Begin("Elements"))
		{
			const ofbx::IElement* root = g_scene->getRootElement();
			if (root && root->getFirstChild()) showGUI(*root);
		}
		ImGui::End();
		if (ImGui::Begin("Properties") && g_selected_element)
		{
			ofbx::IElementProperty* prop = g_selected_element->getFirstProperty();
			if (prop) showGUI(*prop);
		}
		ImGui::End();

		showObjectsGUI(*g_scene);
	}

	ImGui::Render();
}

template <int N>
void ImguiLayer::toString(ofbx::DataView view, char(&out)[N])
{
	int len = int(view.end - view.begin);
	if (len > sizeof(out) - 1) len = sizeof(out) - 1;
	strncpy(out, (const char*)view.begin, len);
	out[len] = 0;
}


int ImguiLayer::getPropertyCount(ofbx::IElementProperty* prop)
{
	return prop ? getPropertyCount(prop->getNext()) + 1 : 0;
}


template <int N>
void ImguiLayer::catProperty(char(&out)[N], const ofbx::IElementProperty& prop)
{
	char tmp[128];
	switch (prop.getType())
	{
	case ofbx::IElementProperty::DOUBLE: sprintf_s(tmp, "%f", prop.getValue().toDouble()); break;
	case ofbx::IElementProperty::LONG: sprintf_s(tmp, "%" PRId64, prop.getValue().toU64()); break;
	case ofbx::IElementProperty::INTEGER: sprintf_s(tmp, "%d", prop.getValue().toInt()); break;
	case ofbx::IElementProperty::STRING: prop.getValue().toString(tmp); break;
	default: sprintf_s(tmp, "Type: %c", (char)prop.getType()); break;
	}
	strcat_s(out, tmp);
}


void ImguiLayer::showGUI(const ofbx::IElement& parent)
{
	for (const ofbx::IElement* element = parent.getFirstChild(); element; element = element->getSibling())
	{
		auto id = element->getID();
		char label[128];
		id.toString(label);
		strcat_s(label, " (");
		ofbx::IElementProperty* prop = element->getFirstProperty();
		bool first = true;
		while (prop)
		{
			if (!first)
				strcat_s(label, ", ");
			first = false;
			catProperty(label, *prop);
			prop = prop->getNext();
		}
		strcat_s(label, ")");

		ImGui::PushID((const void*)id.begin);
		ImGuiTreeNodeFlags flags = g_selected_element == element ? ImGuiTreeNodeFlags_Selected : 0;
		if (!element->getFirstChild()) flags |= ImGuiTreeNodeFlags_Leaf;
		if (ImGui::TreeNodeEx(label, flags))
		{
			if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(0)) g_selected_element = element;
			if (element->getFirstChild()) showGUI(*element);
			ImGui::TreePop();
		}
		else
		{
			if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(0)) g_selected_element = element;
		}
		ImGui::PopID();
	}
}


template <typename T>
void ImguiLayer::showArray(const char* label, const char* format, ofbx::IElementProperty& prop)
{
	if (!ImGui::CollapsingHeader(label)) return;

	int count = prop.getCount();
	ImGui::Text("Count: %d", count);
	std::vector<T> tmp;
	tmp.resize(count);
	prop.getValues(&tmp[0], int(sizeof(tmp[0]) * tmp.size()));
	for (T v : tmp)
	{
		ImGui::Text(format, v);
	}
}


void ImguiLayer::showGUI(ofbx::IElementProperty& prop)
{
	ImGui::PushID((void*)&prop);
	char tmp[256];
	switch (prop.getType())
	{
	case ofbx::IElementProperty::LONG: ImGui::Text("Long: %" PRId64, prop.getValue().toU64()); break;
	case ofbx::IElementProperty::FLOAT: ImGui::Text("Float: %f", prop.getValue().toFloat()); break;
	case ofbx::IElementProperty::DOUBLE: ImGui::Text("Double: %f", prop.getValue().toDouble()); break;
	case ofbx::IElementProperty::INTEGER: ImGui::Text("Integer: %d", prop.getValue().toInt()); break;
	case ofbx::IElementProperty::ARRAY_FLOAT: showArray<float>("float array", "%f", prop); break;
	case ofbx::IElementProperty::ARRAY_DOUBLE: showArray<double>("double array", "%f", prop); break;
	case ofbx::IElementProperty::ARRAY_INT: showArray<int>("int array", "%d", prop); break;
	case ofbx::IElementProperty::ARRAY_LONG: showArray<ofbx::u64>("long array", "%" PRId64, prop); break;
	case ofbx::IElementProperty::STRING:
		toString(prop.getValue(), tmp);
		ImGui::Text("String: %s", tmp);
		break;
	default:
		ImGui::Text("Other: %c", (char)prop.getType());
		break;
	}

	ImGui::PopID();
	if (prop.getNext()) showGUI(*prop.getNext());
}


void ImguiLayer::showCurveGUI(const ofbx::Object& object)
{
	const ofbx::AnimationCurve& curve = static_cast<const ofbx::AnimationCurve&>(object);

	const int c = curve.getKeyCount();
	for (int i = 0; i < c; ++i)
	{
		const float t = (float)ofbx::fbxTimeToSeconds(curve.getKeyTime()[i]);
		const float v = curve.getKeyValue()[i];
		ImGui::Text("%fs: %f ", t, v);

	}
}


void ImguiLayer::showObjectGUI(const ofbx::Object& object)
{
	const char* label;
	switch (object.getType())
	{
	case ofbx::Object::Type::GEOMETRY: label = "geometry"; break;
	case ofbx::Object::Type::MESH: label = "mesh"; break;
	case ofbx::Object::Type::MATERIAL: label = "material"; break;
	case ofbx::Object::Type::ROOT: label = "root"; break;
	case ofbx::Object::Type::TEXTURE: label = "texture"; break;
	case ofbx::Object::Type::NULL_NODE: label = "null"; break;
	case ofbx::Object::Type::LIMB_NODE: label = "limb node"; break;
	case ofbx::Object::Type::NODE_ATTRIBUTE: label = "node attribute"; break;
	case ofbx::Object::Type::CLUSTER: label = "cluster"; break;
	case ofbx::Object::Type::SKIN: label = "skin"; break;
	case ofbx::Object::Type::ANIMATION_STACK: label = "animation stack"; break;
	case ofbx::Object::Type::ANIMATION_LAYER: label = "animation layer"; break;
	case ofbx::Object::Type::ANIMATION_CURVE: label = "animation curve"; break;
	case ofbx::Object::Type::ANIMATION_CURVE_NODE: label = "animation curve node"; break;
	default: assert(false); break;
	}

	ImGuiTreeNodeFlags flags = g_selected_object == &object ? ImGuiTreeNodeFlags_Selected : 0;
	char tmp[128];
	sprintf_s(tmp, "%" PRId64 " %s (%s)", object.id, object.name, label);
	if (ImGui::TreeNodeEx(tmp, flags))
	{
		if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(0)) g_selected_object = &object;
		int i = 0;
		while (ofbx::Object* child = object.resolveObjectLink(i))
		{
			showObjectGUI(*child);
			++i;
		}
		if (object.getType() == ofbx::Object::Type::ANIMATION_CURVE)
		{
			showCurveGUI(object);
		}

		ImGui::TreePop();
	}
	else
	{
		if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(0)) g_selected_object = &object;
	}
}


void ImguiLayer::showObjectsGUI(const ofbx::IScene& scene)
{
	if (!ImGui::Begin("Objects"))
	{
		ImGui::End();
		return;
	}
	const ofbx::Object* root = scene.getRoot();
	if (root) showObjectGUI(*root);

	int count = scene.getAnimationStackCount();
	for (int i = 0; i < count; ++i)
	{
		const ofbx::Object* stack = scene.getAnimationStack(i);
		showObjectGUI(*stack);
	}

	ImGui::End();
}
