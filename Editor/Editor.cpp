#include "Editor.h"

Editor::Editor()
{ }

void Editor::Init(EditorGraphics *graphics)
{
	this->graphics = graphics;

	ImGui_ImplDX11_Init(graphics->GetHWND(), graphics->GetDevice(), graphics->GetDeviceContext());

	selected = new GameObject();
	selected->Init(graphics->GetDevice(), graphics->GetDeviceContext());
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