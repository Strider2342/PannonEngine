#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "GameWindow.h"
#include "GameSerializer.h"
#include "Application.h"

#include "imgui\imgui_impl_dx11.h"

extern LRESULT ImGui_ImplDX11_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	ImGui_ImplDX11_WndProcHandler(hWnd, message, wParam, lParam);
	
	switch (message)
	{
		case WM_SIZING:
		{
			PostMessage(hWnd, WM_SIZING, wParam, lParam);
		}
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

#include "EditorScene.h"

int main()
{
	GameWindow window = GameWindow(1706, 960, L"PannonEditor", L"WindowClass", WindowProc);
	GameSerializer serializer = GameSerializer();
	Application application = Application(window.GetHWND());
	
	EditorScene *scene = static_cast<EditorScene *>(serializer.ImportScene("scene1.scn"));

	EditorScene *editor = new EditorScene();
	editor->SetScene(scene);

	//application.AddScene<EditorScene>();
	application.AddScene<EditorScene>(editor);
	application.Run();

	return 0;
}