#include "ImguiLayer.h"

namespace Tempest
{
	void ImguiLayer::ControlPanel()
	{
		ImGui::Begin("ControlPanel");
		ImGuiTreeNodeFlags_ collapse_panel_flags = ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_DefaultOpen;

		if (SelectedFlag >= 0)
		{
			if (ImGui::CollapsingHeader("Basic Information", collapse_panel_flags))
			{
				static float* position_data = reinterpret_cast<float*>(&SelectedObject.pos);
				ImGui::Text("Position");
				ImGui::SameLine(100);
				if (ImGui::InputFloat3("position", position_data))
				{
					SelectedFlag = EntityInfo::ObjectFlag;
					Modified = true;
				}

				static float* rotation_data = reinterpret_cast<float*>(&SelectedObject.rot);
				ImGui::Text("Rotation");
				ImGui::SameLine(100);
				if (ImGui::InputFloat3("rotation", rotation_data))
				{
					SelectedFlag = EntityInfo::ObjectFlag;
					Modified = true;
				}


				static float* scale_data = reinterpret_cast<float*>(&SelectedObject.scale);
				ImGui::Text("Scale");
				ImGui::SameLine(100);
				if (ImGui::InputFloat3("scale", scale_data))
				{
					SelectedFlag = EntityInfo::ObjectFlag;
					Modified = true;
				}
			}
		}

		if (SelectedObjectFlags & EntityInfo::CameraFlag)
		{
			if (ImGui::CollapsingHeader("Camera Component", collapse_panel_flags))
			{
			}
		}

		if (SelectedObjectFlags & EntityInfo::LightFlag)
		{
			if (ImGui::CollapsingHeader("Light Component", collapse_panel_flags))
			{
			}
		}


		if (SelectedObjectFlags & EntityInfo::EffectFlag)
		{
			if (ImGui::CollapsingHeader("Effect Component", collapse_panel_flags))
			{
				static float* albedo_data = reinterpret_cast<float*>(&SelecctedEffect.material.albedo);
				if (ImGui::ColorEdit3("Albedo", albedo_data))
				{
					SelectedFlag = EntityInfo::EffectFlag;
					Modified = true;
				}

				static float* roughness_data = reinterpret_cast<float*>(&SelecctedEffect.material.roughness);
				if (ImGui::SliderFloat("Roughness", roughness_data, 0.0f, 1.0f))
				{
					SelectedFlag = EntityInfo::EffectFlag;
					Modified = true;
				}

				static float* metalicness_data = reinterpret_cast<float*>(&SelecctedEffect.material.metalic);
				if (ImGui::SliderFloat("Metalic", metalicness_data, 0.0f, 1.0f))
				{
					SelectedFlag = EntityInfo::EffectFlag;
					Modified = true;
				}
			}
		}


		if (SelectedObjectFlags & EntityInfo::MeshFlag)
		{
			if (ImGui::CollapsingHeader("Mesh Component", collapse_panel_flags))
			{
			}
		}

		ImGui::End();
	}
}