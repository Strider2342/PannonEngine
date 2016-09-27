#include "EditorGUI.h"

EditorGUI::EditorGUI()
{ }

void EditorGUI::MenuBar()
{
	if (ImGui::BeginMainMenuBar())
	{
		FileMenu();
		ViewMenu();
		CreateMenu();
		HelpMenu();

		ImGui::SameLine(ImGui::GetWindowWidth() / 2);
		ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

		ImGui::EndMainMenuBar();
	}
}
void EditorGUI::FileMenu()
{
	if (ImGui::BeginMenu("File"))
	{
		if (ImGui::MenuItem("Open project"))
		{

		}
		if (ImGui::MenuItem("Save project"))
		{

		}
		if (ImGui::MenuItem("Save project as"))
		{

		}
		ImGui::Separator();
		if (ImGui::MenuItem("Open scene"))
		{

		}
		if (ImGui::MenuItem("Save scene"))
		{

		}
		if (ImGui::MenuItem("Save scene as"))
		{

		}
		ImGui::Separator();
		if (ImGui::MenuItem("Exit"))
		{
			PostQuitMessage(0);
		}
		ImGui::EndMenu();
	}
}
void EditorGUI::ViewMenu()
{
	if (ImGui::BeginMenu("View"))
	{
		if (ImGui::MenuItem("Material editor"))
		{
			showMaterialEditor ^= 1;
		}
		if (ImGui::MenuItem("Inspector"))
		{
			showInspectorView ^= 1;
		}
		if (ImGui::MenuItem("Hierarchy"))
		{
			showHierarchyView ^= 1;
		}
		if (ImGui::MenuItem("Debug console"))
		{
			showDebugConsole ^= 1;
		}

		ImGui::EndMenu();
	}
}
void EditorGUI::CreateMenu()
{
	if (ImGui::BeginMenu("Create"))
	{
		if (ImGui::MenuItem("Mesh"))
		{
			//
		}
		if (ImGui::MenuItem("Light"))
		{
			//
		}
		if (ImGui::MenuItem("Camera"))
		{
			//
		}
		if (ImGui::MenuItem("Material"))
		{
			//
		}
		if (ImGui::MenuItem("Script"))
		{
			//
		}

		ImGui::EndMenu();
	}
}
void EditorGUI::HelpMenu()
{
	if (ImGui::BeginMenu("Help"))
	{
		if (ImGui::MenuItem("About"))
		{
			//
		}
		if (ImGui::MenuItem("Documentation"))
		{
			//
		}
		if (ImGui::MenuItem("Version"))
		{
			//
		}

		ImGui::EndMenu();
	}
}

void EditorGUI::Views()
{
	if (showInspectorView)
	{
		InspectorView();
	}
	if (showHierarchyView)
	{
		HierarchyView();
	}
	if (showMaterialEditor)
	{
		MaterialEditor();
	}
	if (showDebugConsole)
	{
		DebugConsole();
	}
}
void EditorGUI::InspectorView()
{
	std::cout << "Name: " << selected->GetName() << std::endl;

	float position[3] = { 1.0f, 1.0f, 1.0f };
	float rotation[3] = { 1.0f, 1.0f, 1.0f };
	float scale[3] = { 1.0f, 1.0f, 1.0f };

	ImGui::SetNextWindowPos(ImVec2(1375, 20));
	ImGui::SetNextWindowSize(ImVec2(300, 900));
	if (ImGui::Begin("Inspector"))
	{
		if (ImGui::CollapsingHeader("Transform"))
		{
			ImGui::Text("Name");
			//ImGui::InputText("", (char*)selected->GetName().c_str(), IM_ARRAYSIZE((char*)selected->GetName().c_str()));
			ImGui::Separator();
			ImGui::Text("Position");
			ImGui::InputFloat3("Position", position);
			ImGui::Text("Rotation");
			ImGui::InputFloat3("Rotation", rotation);
			ImGui::Text("Scale");
			ImGui::InputFloat3("Scale", scale);
		}
		if (ImGui::CollapsingHeader("Material"))
		{
			ImGui::Button("Select material");
		}
		if (ImGui::CollapsingHeader("Conponents"))
		{
			ImGui::Button("Add component");
		}
		ImGui::End();
	}
}
void EditorGUI::HierarchyView()
{
	ImGui::SetNextWindowPos(ImVec2(0, 20));
	ImGui::SetNextWindowSize(ImVec2(300, 900));
	if (ImGui::Begin("Hierarchy"))
	{

		ImGui::End();
	}
}
void EditorGUI::MaterialEditor()
{
	ImGui::SetNextWindowSize(ImVec2(400, 600));
	if (ImGui::Begin("Material editor"))
	{

		ImGui::End();
	}
}
void EditorGUI::DebugConsole()
{
	ImGui::SetNextWindowPos(ImVec2(301, 560));
	ImGui::SetNextWindowSize(ImVec2(1073, 360));
	if (ImGui::Begin("Console"))
	{

		ImGui::End();
	}
}
void EditorGUI::GameCanvas()
{
	
}

void EditorGUI::AssembleGUI()
{
	ImGui_ImplDX11_NewFrame();

	MenuBar();
	Views();
}

void EditorGUI::SetSelected(GameObject * selected)
{
	this->selected = selected;
}
