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

	gui.SetSelected(selected);
}

void Editor::Load()
{ }

void Editor::Update()
{ }

void Editor::Draw()
{
	gui.AssembleGUI();

	graphics->Begin();
	ImGui::Render();

	graphics->End();
}