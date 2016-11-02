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
	ImGui::SetNextWindowPos(ImVec2(1375, 20));
	ImGui::SetNextWindowSize(ImVec2(300, 900));

	char name[128];
	strcpy_s(name, selected->GetName().c_str());

	if (ImGui::Begin("Inspector"))
	{
		ImGui::InputText("", name, IM_ARRAYSIZE(name));

		for (int i = 0; i < selected->GetNumberOfComponents(); i++)
		{
			if (dynamic_cast<Transform *>(selected->GetComponentById(i)) != NULL)
			{
				ImGui::SetNextTreeNodeOpen(true);
				TransformComponent();
			}
			else if (dynamic_cast<Physics *>(selected->GetComponentById(i)) != NULL)
			{
				PhysicsComponent();
			}
			else if (dynamic_cast<MeshRenderer *>(selected->GetComponentById(i)) != NULL)
			{
				MeshRendererComponent();
			}
			else if (dynamic_cast<Camera *>(selected->GetComponentById(i)) != NULL)
			{
				CameraComponent();
			}
			else if (dynamic_cast<Light *>(selected->GetComponentById(i)) != NULL)
			{
				LightComponent();
			}
			else if (dynamic_cast<Script *>(selected->GetComponentById(i)) != NULL)
			{
				ScriptComponent();
			}
			else if (dynamic_cast<SphereCollider *>(selected->GetComponentById(i)) != NULL)
			{
				SphereColliderComponent();
			}
			else if (dynamic_cast<BoxCollider *>(selected->GetComponentById(i)) != NULL)
			{
				BoxColliderComponent();
			}
		}

		ImGui::End();

		selected->SetName(name);
	}
}
void EditorGUI::HierarchyView()
{
	ImGui::SetNextWindowPos(ImVec2(0, 20));
	ImGui::SetNextWindowSize(ImVec2(300, 900));

	if (ImGui::Begin("Hierarchy"))
	{
		static int selected_node = 0;

		for (int i = 0; i < gameObjects->size(); i++)
		{
			ImGuiTreeNodeFlags node_flags = 0;

			bool hasChildren = gameObjects->at(i)->GetTransform()->HasChildren();

			if (!hasChildren)
			{
				node_flags = (selected_node == i) ? ImGuiTreeNodeFlags_Selected : 0;
			}
			else
			{
				node_flags = ((selected_node == i) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
			}

			if (ImGui::TreeNodeEx(&i, node_flags, gameObjects->at(i)->GetName().c_str()))
			{
				ImGui::TreePop();
			}

			if (ImGui::IsItemClicked())
			{
				selected_node = i;
				selected = gameObjects->at(i);
			}
		}

		//std::cout << "Selected: " << selected->GetName() << std::endl;

		ImGui::End();
	}
}
void EditorGUI::MaterialEditor()
{
	ImGui::SetNextWindowSize(ImVec2(400, 600));
	if (ImGui::Begin("Material editor"))
	{
		int mateditor_shader = 0;
		float ambient[3] = { 255.0f, 255.0f, 255.0f };
		float diffuse[3] = { 255.0f, 255.0f, 255.0f };
		float specular[3] = { 255.0f, 255.0f, 255.0f };
		float emissive[3] = { 255.0f, 255.0f, 255.0f };
		float power = 1.0f;

		ImGui::Combo("Shader", &mateditor_shader, "Phong\0Blinn-Phong\0Toon\0\0");

		if (mateditor_shader == 0 || mateditor_shader == 1)
		{
			ImGui::InputFloat3("Ambient", ambient, 2);
			ImGui::InputFloat3("Diffuse", diffuse, 2);
			ImGui::InputFloat3("Specular", specular, 2);
			ImGui::InputFloat3("Emissive", emissive, 2);
			ImGui::InputFloat("Power", &power);
		}

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

void EditorGUI::TransformComponent()
{
	float position[3] = { selected->GetTransform()->GetPosition().x, selected->GetTransform()->GetPosition().y, selected->GetTransform()->GetPosition().z };
	float rotation[3] = { selected->GetTransform()->GetRotation().x, selected->GetTransform()->GetRotation().y, selected->GetTransform()->GetRotation().z };
	float scale[3] = { selected->GetTransform()->GetScale().x, selected->GetTransform()->GetScale().y, selected->GetTransform()->GetScale().z };
	int parent = 0;

	ImGui::SetNextWindowPos(ImVec2(1375, 20));
	ImGui::SetNextWindowSize(ImVec2(300, 900));
	if (ImGui::CollapsingHeader("Transform"))
	{
		ImGui::DragFloat3("Position", position, 0.025f);
		ImGui::DragFloat3("Rotation", rotation, 0.025f);
		ImGui::DragFloat3("Scale", scale, 0.0025f);
		ImGui::Combo("Parent", &parent, "GameObject1\0GameObject2\0GameObject3\0\0");
	}

	selected->GetTransform()->SetPosition(DirectX::XMFLOAT3(position[0], position[1], position[2]));
	selected->GetTransform()->SetRotation(DirectX::XMFLOAT3(rotation[0], rotation[1], rotation[2]));
	selected->GetTransform()->SetScale(DirectX::XMFLOAT3(scale[0], scale[1], scale[2]));
}

void EditorGUI::PhysicsComponent()
{
	if (ImGui::CollapsingHeader("Physics"))
	{

	}
}

void EditorGUI::MeshRendererComponent()
{
	if (ImGui::CollapsingHeader("MeshRenderer"))
	{

	}
}

void EditorGUI::CameraComponent()
{
	float fov = DirectX::XMConvertToDegrees(selected->GetComponent<Camera>()->GetFOV());
	float nearClippingPlane = selected->GetComponent<Camera>()->GetNearClippingPlane();
	float farClippingPlane = selected->GetComponent<Camera>()->GetFarClippingPlane();

	if (ImGui::CollapsingHeader("Camera"))
	{
		ImGui::DragFloat("FOV", &fov, 0.1f);
		ImGui::DragFloat("Near clipping plane", &nearClippingPlane, 0.05f);
		ImGui::DragFloat("Far clipping plane", &farClippingPlane, 0.05f);
	}

	selected->GetComponent<Camera>()->SetFOV(DirectX::XMConvertToRadians(fov));
	selected->GetComponent<Camera>()->SetNearClippingPlane(nearClippingPlane);
	selected->GetComponent<Camera>()->SetFarClippingPlane(farClippingPlane);
}

void EditorGUI::LightComponent()
{
	int light_type = selected->GetComponent<Light>()->GetType();
	bool enabled = selected->GetComponent<Light>()->GetEnabled();
	DirectX::XMFLOAT4 color = selected->GetComponent<Light>()->GetColor();
	float light_color[3] = { color.x, color.y, color.z };
	//static float intensity = selected->GetComponent<Light>()->GetIntensity();
	float constantAttenuation = selected->GetComponent<Light>()->GetConstantAttenuation();
	float linearAttenuation = selected->GetComponent<Light>()->GetLinearAttenuation();
	float quadraticAttenuation = selected->GetComponent<Light>()->GetQuadraticAttenuation();
	float spotAngle = DirectX::XMConvertToDegrees(selected->GetComponent<Light>()->GetSpotAngle());

	if (ImGui::CollapsingHeader("Light"))
	{
		ImGui::Combo("Type", &light_type, "Directional\0Point\0Spot\0\0");
		ImGui::Checkbox("Enabled", &enabled);
		ImGui::ColorEdit3("Color", light_color);
		//ImGui::InputFloat("Intensity", &intensity);
		ImGui::DragFloat("Constant attenuation", &constantAttenuation, 0.05f);
		ImGui::DragFloat("Linear attenuation", &linearAttenuation, 0.05f);
		ImGui::DragFloat("Quadratic attenuation", &quadraticAttenuation, 0.005f);

		if (light_type == 2)
		{
			ImGui::DragFloat("Spot angle", &spotAngle, 0.005f);
		}
	}

	selected->GetComponent<Light>()->SetType(light_type);
	selected->GetComponent<Light>()->SetEnabled(enabled);
	selected->GetComponent<Light>()->SetColor(DirectX::XMFLOAT4(light_color[0], light_color[1], light_color[2], 1.0f));
	selected->GetComponent<Light>()->SetConstantAttenuation(constantAttenuation);
	selected->GetComponent<Light>()->SetLinearAttenuation(linearAttenuation);
	selected->GetComponent<Light>()->SetQuadraticAttenuation(quadraticAttenuation);
	selected->GetComponent<Light>()->SetSpotAngle(DirectX::XMConvertToRadians(spotAngle));
}

void EditorGUI::ScriptComponent()
{
	if (ImGui::CollapsingHeader("Script"))
	{
		
	}
}

void EditorGUI::SphereColliderComponent()
{
	SphereCollider *collider = selected->GetComponent<SphereCollider>();
	float center[3] = { collider->GetCenter().x, collider->GetCenter().y, collider->GetCenter().z};
	float radius = selected->GetComponent<SphereCollider>()->GetRadius();

	if (ImGui::CollapsingHeader("Sphere collider"))
	{
		ImGui::InputFloat3("Center", center, 2);
		ImGui::InputFloat("Radius", &radius, 0.5f, 0.2f, 2);
	}

	selected->GetComponent<SphereCollider>()->SetCenter(DirectX::XMFLOAT3(center[0], center[1], center[2]));
	selected->GetComponent<SphereCollider>()->SetRadius(radius);
}

void EditorGUI::BoxColliderComponent()
{
	BoxCollider *collider = selected->GetComponent<BoxCollider>();
	float center[3] = { collider->GetCenter().x, collider->GetCenter().y, collider->GetCenter().z };
	float size[3] = { collider->GetSize().x, collider->GetSize().y, collider->GetSize().z };

	if (ImGui::CollapsingHeader("Box collider"))
	{
		ImGui::InputFloat3("Center", center, 2);
		ImGui::InputFloat3("Size", size, 2);
	}

	selected->GetComponent<BoxCollider>()->SetCenter(DirectX::XMFLOAT3(center[0], center[1], center[2]));
	selected->GetComponent<BoxCollider>()->SetCenter(DirectX::XMFLOAT3(size[0], size[1], size[2]));
}

void EditorGUI::AssembleGUI()
{
	ImGui_ImplDX11_NewFrame();

	MenuBar();
	Views();
}

void EditorGUI::SetSelected(GameObject *&selected)
{
	this->selected = selected;
}

void EditorGUI::SetGameObjectList(std::vector<GameObject*> *gameObjects)
{
	this->gameObjects = gameObjects;
}

void EditorGUI::Render()
{
	ImGui::Render();
}
