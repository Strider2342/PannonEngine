#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "GameWindow.h"
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

#include "Scene1.h"

int main()
{
	GameWindow window = GameWindow(1706, 960, L"PannonEditor", L"WindowClass", WindowProc);
	Application application = Application(window.GetHWND());
	
	/*GameScene *scene = new GameScene();
	scene->ImportFromFile("scene2.scn");*/

	application.AddScene<Scene1>();
	application.Run();

	return 0;
}