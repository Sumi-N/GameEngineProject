#include "ImguiLayer.h"

namespace Tempest
{
	void ImguiLayer::SceneEditorPanel()
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
					SelectedObjectIndex = i;
					SelectedObject = EntityInfo::GetObjectByIndex(i);
					SelectedObjectInfo = EntityInfo::GetAttachedComponentsInfoByIndex(i);
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
			if (SelectedObjectIndex != -1)
			{
				if (ImGui::GetIO().KeyCtrl)
					selection_mask ^= (1 << SelectedObjectIndex);          // CTRL+click to toggle
				else
					selection_mask = (1 << SelectedObjectIndex);           // Click to single-select
			}
			ImGui::TreePop();
		}

		ImGui::End();
	}
}