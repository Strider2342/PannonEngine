#include "Editor.h"

Editor::Editor()
{ }

void Editor::Init(EditorGraphics *graphics)
{
	this->graphics = graphics;

	ImGuiIO& io = ImGui::GetIO();
	io.DisplaySize.x = 1706;
	io.DisplaySize.y = 960;

	ImGui_ImplDX11_Init(graphics->GetHWND(), graphics->GetDevice(), graphics->GetDeviceContext());

	selected = new GameObject();
	selected->SetName("Probanev");
	selected->GetTransform()->GetPosition() = DirectX::XMFLOAT3(1.0f, 2.0f, 3.0f);
	selected->AddComponent<MeshRenderer>();
	selected->AddComponent<Physics>();

	selected->AddComponent<Camera>();
	selected->GetComponent<Camera>()->SetFOV(75.0f);
	selected->GetComponent<Camera>()->SetNearClippingPlane(0.1f);
	selected->GetComponent<Camera>()->SetFarClippingPlane(1000.0f);

	selected->AddComponent<BoxCollider>();
	selected->AddComponent<SphereCollider>();

	gui.SetSelected(selected);
}

void Editor::Load()
{ }

void Editor::Update()
{
	//std::cout << Input::GetMousePosition().x << " : " << Input::GetMousePosition().y << std::endl;
}

void Editor::Draw()
{
	gui.AssembleGUI();
	graphics->Begin();

	ImGui::Render();

	graphics->End();
}