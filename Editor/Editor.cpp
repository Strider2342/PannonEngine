#include "Editor.h"

Editor::Editor()
{ }

void Editor::Init(EditorGraphics *graphics)
{
	this->graphics = graphics;

	/*ImGuiIO& io = ImGui::GetIO();
	io.DisplaySize.x = graphics->GetGraphicsOptions()->resolutionX;
	io.DisplaySize.y = graphics->GetGraphicsOptions()->resolutionY;*/

	ImGui_ImplDX11_Init(graphics->GetHWND(), graphics->GetDevice(), graphics->GetDeviceContext());
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