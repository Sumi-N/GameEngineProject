#include "ImguiLayer.h"

namespace Tempest
{
	void ImguiLayer::ControlPanel()
	{
		ImGui::Begin("ControlPanel");
		ImGuiTreeNodeFlags_ collapse_panel_flags = ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_DefaultOpen;

		if (SelectingComponent >= 0)
		{
			if (ImGui::CollapsingHeader("Basic Information", collapse_panel_flags))
			{
				static float* position_data = reinterpret_cast<float*>(&SelectedObject.pos);
				ImGui::Text("Position");
				ImGui::SameLine(100);
				if (ImGui::InputFloat3("position", position_data))
				{
					SelectingComponent = EntityInfo::ObjectFlag;
					isObjectModified = true;
				}

				static float* rotation_data = reinterpret_cast<float*>(&SelectedObject.rot);
				ImGui::Text("Rotation");
				ImGui::SameLine(100);
				if (ImGui::InputFloat3("rotation", rotation_data))
				{
					SelectingComponent = EntityInfo::ObjectFlag;
					isObjectModified = true;
				}


				static float* scale_data = reinterpret_cast<float*>(&SelectedObject.scale);
				ImGui::Text("Scale");
				ImGui::SameLine(100);
				if (ImGui::InputFloat3("scale", scale_data))
				{
					SelectingComponent = EntityInfo::ObjectFlag;
					isObjectModified = true;
				}
			}
		}

		if (SelectedObjectInfo & EntityInfo::CameraFlag)
		{
			if (ImGui::CollapsingHeader("Camera Component", collapse_panel_flags))
			{
			}
		}

		if (SelectedObjectInfo & EntityInfo::LightFlag)
		{
			if (ImGui::CollapsingHeader("Light Component", collapse_panel_flags))
			{
			}
		}


		if (SelectedObjectInfo & EntityInfo::EffectFlag)
		{
			if (ImGui::CollapsingHeader("Effect Component", collapse_panel_flags))
			{
				static float* albedo_data = reinterpret_cast<float*>(&SelecctedEffect.material.albedo);
				if (ImGui::ColorEdit3("Albedo", albedo_data))
				{
					SelectingComponent = EntityInfo::EffectFlag;
					isObjectModified = true;
				}

				static float* roughness_data = reinterpret_cast<float*>(&SelecctedEffect.material.roughness);
				if (ImGui::SliderFloat("Roughness", roughness_data, 0.0f, 1.0f))
				{
					SelectingComponent = EntityInfo::EffectFlag;
					isObjectModified = true;
				}

				static float* metalicness_data = reinterpret_cast<float*>(&SelecctedEffect.material.metalic);
				if (ImGui::SliderFloat("Metalic", metalicness_data, 0.0f, 1.0f))
				{
					SelectingComponent = EntityInfo::EffectFlag;
					isObjectModified = true;
				}
			}
		}


		if (SelectedObjectInfo & EntityInfo::MeshFlag)
		{
			if (ImGui::CollapsingHeader("Mesh Component", collapse_panel_flags))
			{
			}
		}

		ImGui::End();
	}
}