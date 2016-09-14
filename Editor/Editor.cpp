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
	ImGui_ImplDX11_NewFrame();

	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Exit"))
			{
				PostQuitMessage(0);
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Views"))
		{
			if (ImGui::MenuItem("Tweaker"))
			{
				//tweakeropened ^= 1;
			}
			if (ImGui::MenuItem("Debug Console"))
			{
				//consoleopened ^= 1;
			}
			if (ImGui::MenuItem("Texture Resources"))
			{
				//texresourcesopened ^= 1;
			}
			ImGui::Separator();

			ImGui::EndMenu();
		}

		ImGui::SameLine(ImGui::GetWindowWidth() / 2);
		ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

		ImGui::EndMainMenuBar();
	}

	graphics->Begin();
	ImGui::Render();
	graphics->End();
}