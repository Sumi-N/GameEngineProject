#include "ImguiLayer.h"

namespace Tempest
{
	extern GraphicRequiredData GraphicsData;

	static struct EditorCamera
	{
		Vec3f pos;
		Vec3f vel;
		Vec3f angvel;
		Mat4f view;
		Mat4f perspective;
		Mat4f view_perspective;
		Vec3f forward;
		Vec3f up;
		Vec3f right;
	} SceneCamera;

	void MoveCamera(const float amount, const Vec3f& dir)
	{
		SceneCamera.vel = amount * dir;
	}

	void RotateAround(const float amount, const Vec3f& axis)
	{

		SceneCamera.forward = SceneCamera.forward.Rotate(axis, amount);
		SceneCamera.up = SceneCamera.up.Rotate(axis, amount);

		SceneCamera.right = Vec3f::Normalize(SceneCamera.forward.Cross(SceneCamera.up));
	}

	void CameraControl()
	{
		if (UserInput.QueryKey(VirtualKey::KEY_W) == InputState::Pressing)
		{
			MoveCamera(0.01f, SceneCamera.forward);
		}

		if (UserInput.QueryKey(VirtualKey::KEY_S) == InputState::Pressing)
		{
			MoveCamera(-0.01f, SceneCamera.forward);
		}

		if (UserInput.QueryKey(VirtualKey::KEY_A) == InputState::Pressing)
		{
			MoveCamera(-0.01f, SceneCamera.right);
		}

		if (UserInput.QueryKey(VirtualKey::KEY_D) == InputState::Pressing)
		{
			MoveCamera(0.01f, SceneCamera.right);
		}

		if (UserInput.QueryKey(VirtualKey::KEY_Q) == InputState::Pressing)
		{
			MoveCamera(0.01f, SceneCamera.up);
		}

		if (UserInput.QueryKey(VirtualKey::KEY_E) == InputState::Pressing)
		{
			MoveCamera(-0.01f, SceneCamera.up);
		}

		if (UserInput.QueryKey(VirtualKey::KEY_RIGHTBUTTON) == InputState::Pressing)
		{
			Vec2f mousevelocity = Vec2f(UserInput.MouseVelocityX(16.666f), UserInput.MouseVelocityY(16.666f));

			Vec3f up = Vec3f(0, 1, 0);
			RotateAround(mousevelocity.x, up);
			Vec3f right = SceneCamera.right;
			RotateAround(mousevelocity.y, right);
		}

		SceneCamera.pos += 16.666f * SceneCamera.vel;
		SceneCamera.vel = Vec3f(0, 0, 0);

		SceneCamera.view = Mat4f::LookAt(SceneCamera.pos, SceneCamera.pos + SceneCamera.forward, SceneCamera.up);
	}

	void ImguiLayer::OnAttach_ViewportPanel()
	{
		SceneCamera.forward = Vec3f(0, 0, -1);
		SceneCamera.up = Vec3f(0, 1, 0);
		SceneCamera.right = Vec3f::Normalize(SceneCamera.forward.Cross(SceneCamera.up));

		SceneCamera.view = Mat4f::LookAt(SceneCamera.pos, SceneCamera.pos + SceneCamera.forward, SceneCamera.up);

		SceneCamera.perspective = Mat4f::Perspective(FieldOfView, (float)ScreenWidth / ScreenHeight, NearClip, FarClip);
	}

	void ImguiLayer::ViewportPanel()
	{
		ImGui::Begin("Viewport");
		ImVec2 imgui_viewport_panel_size = ImGui::GetContentRegionAvail();
		ImGui::Image(reinterpret_cast<void*>(Graphic::FrameBufferImage.GetColorID()), imgui_viewport_panel_size, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

		if (ImGui::IsWindowFocused())
		{
			CameraControl();
		}

		ImGui::End();
	}

	void ImguiLayer::OnCriticalSection_ViewportPanel()
	{
		GraphicsData.editor_camera.camera_position_vector = SceneCamera.pos;
		GraphicsData.editor_camera.perspective_matrix = SceneCamera.perspective;
		GraphicsData.editor_camera.view_matrix = SceneCamera.view;
	}

	void ImguiLayer::AssetPanel()
	{
		ImGui::Begin("AssetPanel");
		ImGui::Text("This is setting panel");
		ImGui::End();
	}
}